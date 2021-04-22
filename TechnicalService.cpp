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
    return 50;
}

unsigned int TechnicalService::getResourcePriority() {
    return 1;
}

unsigned int TechnicalService::getStaffDemand() {
    return 10;
}

unsigned int TechnicalService::getStaffPriority() {
    return 1;
}

bool TechnicalService::changeStaff(int delta) {
    return true;
}

bool TechnicalService::changeResources(int delta) {
    return true;
}