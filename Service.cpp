//
// Created by Amisto on 4/2/2021.
//

#include "Service.h"

Service::Service() : n_staff(0), resources(0)
{

}

unsigned int Service::getNStaff() const {
    return n_staff;
}

Service::~Service() {

}

unsigned int Service::getResourceDemand() {
    return (unsigned int) (resources * 0.01 + 10);
}

unsigned int Service::getResourcePriority() {
    return 6;
}

unsigned int Service::getStaffPriority() {
    return 6;
}

bool Service::changeStaff(int delta) {
    return true;
}

bool Service::changeResources(int delta) {
    if (resources > delta) {
        resources -= delta;
        return true;
    }
    else {
        return false;
    }
}
