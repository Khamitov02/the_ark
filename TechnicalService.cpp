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

// идет "корректировка" состояния корабля в зависимости от степени аварии
void TechnicalService::process_accident(AccidentSeverity as)
{
    protectionState -= as * 6.8; //подумать коэф
    engineState -= as * (100 - protectionState) * 0.3;
    totalState = 0.5 * (0.8 * protectionState + 1.2 * engineState);
    if (protectionState < 15)
        emergencyRepair();
    // kill some people
    staff -= as * staff / 20;
}

// считает и возвращает состояние службы в зависимости от количества работающих людей и
double TechnicalService::getState() {
    return serviceState;
}

void TechnicalService::emergencyRepair()
{
    double repairing = double(staff) / maxStaff * double(resources) / maxResources * 50;
    protectionState += repairing;
    resources -= int(repairing / 100) * maxResources;
    // убить много людей, так как экстренная и масштабная починка
    staff = int(0.9 * staff);
}

void TechnicalService::process_year()
{
    // обновление состояния службы
    serviceState = 50 * (double(staff) / maxStaff + double(resources) / maxResources);
    if (serviceState > 100)
        serviceState = 100;

    // починка корабля
    double repairing = double(staff) / maxStaff * double(resources) / maxResources * 10;
    if (protectionState < 90)
    {
        protectionState += repairing;
        resources -= int(repairing / 100) * maxResources;
        // можно убить пару людей в зависимости от масштаба ремонта
    }
    if (protectionState > 60 && engineState < 90)
    {
        engineState += repairing;
        resources -= int(repairing / 100) * maxResources;
    }
    // износ корабля
    protectionState -= (101 - protectionState) * 0.05;
    engineState -= (100 - protectionState) * 0.05;
}

double TechnicalService::efficiencyConsumablesToComponents() {
    return double(staff) / maxStaff * 0.9;
}

double TechnicalService::efficiencyJunkToConsumables() {
    return double(staff) / maxStaff * 0.7;
}

double TechnicalService::efficiencyJunkToRefuse() {
    return double(staff) / maxStaff * 0.5;
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
    staff += delta;
    return true;
}

bool TechnicalService::changeResources(int delta) {
    resources += delta;
    return true;
}