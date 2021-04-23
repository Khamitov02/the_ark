//
// Created by Amisto on 4/2/2021.
//

#include "MedicalService.h"
#include "TheArk.h"
#include "Population.h"
#include "BiologicalService.h"
#include "SocialService.h"

MedicalService::MedicalService() : retirementAge(65), ChildrenDeath(0.0001), AdultDeath(0.001), OldDeath(0.01),
                                   State(100), n_engineers(50), n_scientists(25), resources(1000) {}

void MedicalService::process_accident(AccidentSeverity as) {

}

void MedicalService::process_year() {
    auto p = &TheArk::get_instance()->getPopulation()->getPeople();
    unsigned int oll_health = 0, IlChild = 0, IlAd = 0, IlOld = 0;
    unsigned int HIlChild = 0, HIlAd = 0, HIlOld = 0;
    for (auto it = p->begin(); it != p->end(); ++it) {
        oll_health += (*it)->getPhysicalHealth();
        if (((*it)->getPhysicalHealth() < 60) &&
            ((*it)->getAge() < TheArk::get_instance()->getSocialService()->borderChildrenToAdults())) {
            if ((*it)->getPhysicalHealth() < 30)
                HIlChild++;
            IlChild++;
        }
        if (((*it)->getPhysicalHealth() < 60) &&
            ((*it)->getAge() >= TheArk::get_instance()->getSocialService()->borderChildrenToAdults()) &&
            ((*it)->getAge() <= borderAdultsToOldmen())) {
            if ((*it)->getPhysicalHealth() < 30)
                HIlAd++;
            IlAd++;
        }
        if (((*it)->getPhysicalHealth() < 60) &&
            ((*it)->getAge() > borderAdultsToOldmen())) {
            if ((*it)->getPhysicalHealth() < 30)
                HIlOld++;
            IlOld++;
        }

    }
    State = 1.0 * oll_health / TheArk::get_instance()->getPopulation()->getTotal();
    ChildrenDeath = 1.0 * HIlChild / TheArk::get_instance()->getPopulation()->getChildren();
    AdultDeath = 1.0 * HIlAd / TheArk::get_instance()->getPopulation()->getAdults();
    OldDeath = 1.0 * HIlOld / TheArk::get_instance()->getPopulation()->getOldmen();
}

unsigned int MedicalService::borderAdultsToOldmen() {
    return retirementAge;
}

double MedicalService::deathRateChildren() {
    return ChildrenDeath;
}

double MedicalService::deathRateAdult() {
    return AdultDeath;
}

double MedicalService::deathRateOldmen() {
    return OldDeath;
}

double MedicalService::getState() {
    return State;
}

void MedicalService::setState(double s) {
    State = s;
}

unsigned int MedicalService::getResourceDemand() {
    return 500;
}

unsigned int MedicalService::getResourcePriority() {
    return 3;
}

unsigned int MedicalService::getStaffDemand() {
    return 10;
}

unsigned int MedicalService::getStaffPriority() {
    return 3;
}

bool MedicalService::changeStaff(int delta) {
    return true;
}

bool MedicalService::changeResources(int delta) {
    return true;
}
