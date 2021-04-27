//
// Created by Amisto on 4/2/2021.
//

#include "MedicalService.h"
#include "TheArk.h"
#include "Population.h"
#include "BiologicalService.h"
#include "SocialService.h"
#include <cmath>
#include <iostream>

MedicalService::MedicalService() : retirementAge(65), ChildrenDeath(0.0001), AdultDeath(0.001), OldDeath(0.01),
                                   State(100), n_staff(70), resources(1000), Birth(0) {}

void MedicalService::process_accident(AccidentSeverity as) {
}

void MedicalService::process_year() {

    retirementAge = static_cast<unsigned int>(round(51 * (2 - TheArk::get_instance()->getSocialService()->getState() *
                                                              State * State / 1000000)));
    n_staff = static_cast<unsigned int>(round(0.035 * TheArk::get_instance()->getPopulation()->getTotal()));
    resources = 20 * n_staff;
    Birth = 0.012*TheArk::get_instance()->getPopulation()->getTotal();

    unsigned int oll_health = 0;                                                                                        // общее здоровье всего корабля
    unsigned int HIlChild = 0, HIlAd = 0, HIlOld = 0;                                                                   // количество тяжелобольных
    for (auto &it : TheArk::get_instance()->getPopulation()->getPeople()) {                                             // обходим по всем людям на корабле
        oll_health += it->getPhysicalHealth();                                                                          // считаем общий показатель здоровья
        if (it->getAge() < TheArk::get_instance()->getSocialService()->borderChildrenToAdults()) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {                                     // обработка детей со здоровьем от 30 до 60
                it->setPhysicalHealth(static_cast<unsigned int>(round(it->getPhysicalHealth() + rand() % 4 - rand() % 3 +
                                                        (TheArk::get_instance()->getSocialService()->getState() *
                                                         State - 90000) / 10000)));
            }
            if (it->getPhysicalHealth() < 30) {                                                                         // обработка тяжелобольных детей со здоровьем <30
                HIlChild++;                                                                                             // считаем количество тяжелобольных детей
                it->setPhysicalHealth(static_cast<unsigned int>(round(it->getPhysicalHealth() + rand() % 4 - rand() % 4 +
                                            (TheArk::get_instance()->getSocialService()->getState() *
                                             State - 90000) / 10000)));
            }
            it->setPhysicalHealth(static_cast<unsigned int>(it->getPhysicalHealth() + rand() % 5 - rand() % 5 +                       // обратоботка детей со здоровьем >60
                    (TheArk::get_instance()->getSocialService()->getState() *
                     State - 90000) / 10000));
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);                                  // необходимый ограничитель
        }
        if ((it->getAge() >= TheArk::get_instance()->getSocialService()->borderChildrenToAdults()) &&
            (it->getAge() <= borderAdultsToOldmen())) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {
                it->setPhysicalHealth(static_cast<unsigned int>(it->getPhysicalHealth() + rand() % 3 - rand() % 3 +
                                      (TheArk::get_instance()->getSocialService()->getState() *
                                       State - 90000) / 10000));
            }
            if (it->getPhysicalHealth() < 30) {
                HIlAd++;
                it->setPhysicalHealth(static_cast<unsigned int>(it->getPhysicalHealth() + rand() % 3 - rand() % 4 +
                                      (TheArk::get_instance()->getSocialService()->getState() *
                                       State - 90000) / 10000));
            }
            it->setPhysicalHealth(static_cast<unsigned int>(it->getPhysicalHealth() + rand() % 4 - rand() % 4 +
                                  (TheArk::get_instance()->getSocialService()->getState() *
                                   State - 90000) / 10000));
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);
        }
        if (it->getAge() > borderAdultsToOldmen()) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {
                it->setPhysicalHealth(it->getPhysicalHealth() + rand() % 2 - rand() % 4 +
                                      (TheArk::get_instance()->getSocialService()->getState() *
                                       State - 90000) / 10000);
            }
            if (it->getPhysicalHealth() < 30) {
                HIlOld++;
                it->setPhysicalHealth(it->getPhysicalHealth() + rand() % 2 - rand() % 5 +
                                      (TheArk::get_instance()->getSocialService()->getState() *
                                       State - 90000) / 10000);
            }
            it->setPhysicalHealth(it->getPhysicalHealth() + rand() % 3 - rand() % 4 +
                                  (TheArk::get_instance()->getSocialService()->getState() *
                                   State - 90000) / 10000);
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);
        }
    }

    if (TheArk::get_instance()->getPopulation()->getTotal() != 0) {
        State = 1.0 * oll_health /
                TheArk::get_instance()->getPopulation()->getTotal();                                        // вычислятся State исходя из среднего здоровья всего корабля
    } else State = 0;

    ChildrenDeath = 0.0001 * TheArk::get_instance()->getSocialService()->getState() * HIlChild /
                    TheArk::get_instance()->getPopulation()->getChildren();                             // вычислятся веротность смерти из процента тяжелобольных
    AdultDeath = 0.005 * TheArk::get_instance()->getSocialService()->getState() * HIlAd /
                 TheArk::get_instance()->getPopulation()->getAdults();
    OldDeath = 0.001 * TheArk::get_instance()->getSocialService()->getState() * HIlOld /
               TheArk::get_instance()->getPopulation()->getOldmen();

}

void MedicalService::setState(double s) {
    n_staff = 0.035 * TheArk::get_instance()->getPopulation()->getTotal();
    if (s != double(100)) {
        unsigned int delta = (100 - s);
        for (auto &it : TheArk::get_instance()->getPopulation()->getPeople())
            it->setPhysicalHealth((it->getPhysicalHealth() - delta) * (95 + rand() % 10) / 100);
    }
    State = s;
}

unsigned int MedicalService::getStaffDemand() {
    return round((n_staff - TheArk::get_instance()->getPopulation()->getAllClassification()[2].size()) * (double(1.8) - State));
}

unsigned int MedicalService::getStaffPriority() {
    return round(2 * exp(1 - n_staff));
}

unsigned int MedicalService::borderAdultsToOldmen() const {
    return retirementAge;
}

double MedicalService::deathRateChildren() const {
    return ChildrenDeath;
}

double MedicalService::deathRateAdult() const {
    return AdultDeath;
}

double MedicalService::deathRateOldmen() const {
    return OldDeath;
}

double MedicalService::BirthRate() const {
    return Birth;
}

double MedicalService::getState() {
    return State;
}

unsigned int MedicalService::getResourceDemand() {
    return 500;
}

unsigned int MedicalService::getResourcePriority() {
    return 3;
}

bool MedicalService::changeStaff(int delta) {
    return true;
}

bool MedicalService::changeResources(int delta) {
    return true;
}
