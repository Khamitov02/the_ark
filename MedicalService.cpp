//
// Created by Amisto on 4/2/2021.
//

#include "MedicalService.h"
#include "TheArk.h"
#include "Population.h"
#include "BiologicalService.h"
#include "SocialService.h"
#include <cmath>

MedicalService::MedicalService() : retirementAge(65), ChildrenDeath(0.0001), AdultDeath(0.001), OldDeath(0.01),
                                   State(100), n_staff(70), resources(1000), Birth(0), NeedResources(1000), HealthYearAgo(100) {}

void MedicalService::process_accident(AccidentSeverity as) {
}

void MedicalService::process_year() {
    srand(time(nullptr));

    retirementAge = static_cast<unsigned int>(round(51 * (2 - TheArk::get_instance()->getSocialService()->getState() *
                                                              State * State / 1000000)));
    n_staff = static_cast<unsigned int>(round(0.035 * TheArk::get_instance()->getPopulation()->getTotal()));
    NeedResources = static_cast<unsigned int>(20 * TheArk::get_instance()->getPopulation()->getTotal());
    double ResourcePercent = double(resources) / NeedResources;
    double StaffPercent = double(TheArk::get_instance()->getPopulation()->getAllClassification()[2].size()) / n_staff;
    Birth = (8 + rand() % 5) * TheArk::get_instance()->getPopulation()->getTotal() / 1000;

    unsigned int oll_health = 0;                                                                                        // общее здоровье всего корабля
    unsigned int HIlChild = 0, HIlAd = 0, HIlOld = 0;                                                                   // количество тяжелобольных
    for (auto &it : TheArk::get_instance()->getPopulation()->getPeople()) {                                             // обходим по всем людям на корабле
        oll_health += it->getPhysicalHealth();                                                                          // считаем общий показатель здоровья
        if (it->getAge() < TheArk::get_instance()->getSocialService()->borderChildrenToAdults()) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {                                     // обработка детей со здоровьем от 30 до 60
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 4 - rand() % 3 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            if (it->getPhysicalHealth() < 30) {                                                                         // обработка тяжелобольных детей со здоровьем <30
                HIlChild++;                                                                                             // считаем количество тяжелобольных детей
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 4 - rand() % 4 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            it->setPhysicalHealth(static_cast<unsigned int>(round(
                    it->getPhysicalHealth() + rand() % 5 - rand() % 5 +
                    (TheArk::get_instance()->getSocialService()->getState() *
                    State - 90000) / 10000)));
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);                                  // необходимый ограничитель
        }
        if ((it->getAge() >= TheArk::get_instance()->getSocialService()->borderChildrenToAdults()) &&
            (it->getAge() <= borderAdultsToOldmen())) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 3 - rand() % 3 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            if (it->getPhysicalHealth() < 30) {
                HIlAd++;
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 3 - rand() % 4 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            it->setPhysicalHealth(static_cast<unsigned int>(
                    round(it->getPhysicalHealth() + rand() % 4 - rand() % 4 +
                    (TheArk::get_instance()->getSocialService()->getState() *
                    State - 90000) / 10000)));
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);
        }
        if (it->getAge() > borderAdultsToOldmen()) {
            if ((it->getPhysicalHealth() < 60) && (it->getPhysicalHealth() > 30)) {
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 2 - rand() % 4 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            if (it->getPhysicalHealth() < 30) {
                HIlOld++;
                it->setPhysicalHealth(static_cast<unsigned int>(round(
                        it->getPhysicalHealth() + rand() % 2 - rand() % 5 +
                        (TheArk::get_instance()->getSocialService()->getState() *
                         State - 90000) / 10000)));
            }
            it->setPhysicalHealth(static_cast<unsigned int>(
                    round(it->getPhysicalHealth() + rand() % 3 - rand() % 4 +
                    (TheArk::get_instance()->getSocialService()->getState() *
                    State - 90000) / 10000)));
            if (it->getPhysicalHealth() > 100) it->setPhysicalHealth(100);
        }
    }

    if (TheArk::get_instance()->getPopulation()->getTotal() != 0) {
        State = 1.0 * oll_health /
                TheArk::get_instance()->getPopulation()->getTotal();                                                    // вычислятся State исходя из среднего здоровья всего корабля
    } else State = 0;

    ChildrenDeath = (1 - (TheArk::get_instance()->getBiologicalService()->getState() / 100.0)) *
                    (1 - ResourcePercent) * (1 - StaffPercent) *
                    (1 - (TheArk::get_instance()->getSocialService()->getState() / 100.0)) *
                    HIlChild / TheArk::get_instance()->getPopulation()->getChildren();                                  // вычислятся веротность смерти из процента тяжелобольных
    AdultDeath = (1 - (TheArk::get_instance()->getBiologicalService()->getState() / 100.0)) *
                 (1 - ResourcePercent) * (1 - StaffPercent) *
                 (1 - (TheArk::get_instance()->getSocialService()->getState() / 100.0)) *
                 HIlAd / TheArk::get_instance()->getPopulation()->getAdults();
    OldDeath = (1 - (TheArk::get_instance()->getBiologicalService()->getState() / 100.0)) *
               (1 - ResourcePercent) * (1 - StaffPercent) *
               (1 - (TheArk::get_instance()->getSocialService()->getState() / 100.0)) *
               HIlOld / TheArk::get_instance()->getPopulation()->getOldmen();

    resources -= (HealthYearAgo - oll_health) / 2;
}

void MedicalService::setState(double s) {
    n_staff = static_cast<unsigned int>(round(0.035 * TheArk::get_instance()->getPopulation()->getTotal()));
    NeedResources = static_cast<unsigned int>(20 * TheArk::get_instance()->getPopulation()->getTotal());
    if (s != double(100)) {
        auto delta = static_cast<unsigned int>(round((100 - s)));
        for (auto &it : TheArk::get_instance()->getPopulation()->getPeople())
            it->setPhysicalHealth((it->getPhysicalHealth() - delta) * (95 + rand() % 10) / 100);
    }
    State = s;
}

unsigned int MedicalService::getStaffDemand() {
    return static_cast<unsigned int>(round(double(n_staff - TheArk::get_instance()->getPopulation()->getAllClassification()[2].size()) * (double(1.8) - (State / 100.0))));
}

unsigned int MedicalService::getResourceDemand() {
    return static_cast<unsigned int>(round((NeedResources - resources) * (double(1.8) - (State / 100.0))));
}

unsigned int MedicalService::getStaffPriority() {
    return static_cast<unsigned int>(round(exp(1.8 * (1 - double(TheArk::get_instance()->getPopulation()->getAllClassification()[2].size())/n_staff))));
}

unsigned int MedicalService::getResourcePriority() {
    return static_cast<unsigned int>(round(exp(1.8 * (1 - double(resources) / NeedResources))));
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

bool MedicalService::changeStaff(int delta) {
    return true;
}

bool MedicalService::changeResources(int delta) {
    resources += delta;
    return true;
}
