//
// Created by Amisto on 4/2/2021.
//

#include "TechnicalService.h"

TechnicalService::TechnicalService()
{
    totalState = 100;
    engineState = 100;
    protectionState = 100;
    serviceState = 100;
}

void TechnicalService::process_accident(AccidentSeverity as)
{
    protectionState -= as * 7.8;
    engineState -= as * (100 - protectionState) * 0.3;
    totalState = 0.5 * (0.8 * protectionState + 1.2 * engineState);
}

double TechnicalService::getState() {
    serviceState = 50 * (double(staff.size()) / 250 + resources);
    if (serviceState > 100)
        return 100;
    else
        return serviceState;
}

double TechnicalService::efficiencyConsumablesToComponents() {
    return 10;
}

double TechnicalService::efficiencyJunkToConsumables() {
    return 70;
}

double TechnicalService::efficiencyJunkToRefuse() {
    return 60;
}

void TechnicalService::setState(double s)
{
    serviceState = s;
}

unsigned int TechnicalService::getResourceDemand() {

}

unsigned int TechnicalService::getResourcePriority() {}

unsigned int TechnicalService::getStaffDemand() {}

unsigned int TechnicalService::getStaffPriority() {}

bool TechnicalService::changeStaff(int delta) {}

bool TechnicalService::changeResources(int delta) {}