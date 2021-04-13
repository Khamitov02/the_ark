//
// Created by Amisto on 4/2/2021.
//

#include "SocialService.h"

SocialService::SocialService()
{
    this->efficiency_percentage = 15;
    this->staff.resize(0);
    this->clients.resize(0);
}

void SocialService::process_accident(AccidentSeverity as)
{/*no problems*/}

unsigned int SocialService::borderChildrenToAdults()
{
    return 18;
}

double SocialService::getState() {
    return 100;
}

void SocialService::setState(double s) {/*nothing to do*/}

void SocialService::update_n_staff_we_want() {
    this->n_staff_we_want = (TheArk::get_instance()->getPopulation()->people.size() / (2 * this->efficiency_percentage)) + 10;
}

unsigned int SocialService::getResourceDemand() {
    return 0; // наша служба не нуждается в ресурсах на начальном этапе придумывания
}

unsigned int SocialService::getResourcePriority() {return 6;} // последний приоритет

unsigned int SocialService::getStaffDemand(){
    return this->n_staff_we_want;
}

unsigned int SocialService::getStaffPriority(){
    unsigned int labor_shortage_rate = 6 - (this->clients.size() / (this->staff.size() * this->efficiency_percentage));
    if (labor_shortage_rate <= 0) labor_shortage_rate = 1;
    return labor_shortage_rate;
}

bool SocialService::changeStaff (int delta) {/*сделаем, если потребуется*/
    return true;}

bool SocialService::changeResources(int delta){/*сделаем, если потребуется*/
    return true;}

void SocialService::update_people() {/*Currently nothing to do*/}





