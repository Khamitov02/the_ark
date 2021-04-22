
// Created by Amisto on 4/2/2021.

#include "EmergencyService.h"

EmergencyService::EmergencyService() : State(100)
{}


//от 0 до 1, чем хуже состояние службы - тем выше вероятность аварии
double EmergencyService::accident_propability()
{
    double s = TheArk::get_instance()->getMedicalService()->getState() / 100;
    return 1 / pow(3, 3 * s);
}

//от 1 до 100 чем хуже состояние чс, тем больше коэффициент - больше ущерб от аварии
double EmergencyService::damage_factor()
{
    if (this->getState() != 0)
        return 100 / (this->getState());
    else return 100;
}

//генерация аварий
void EmergencyService::create_accident(Service* s)
{
    srand(time(0));
    int temp = (20 + rand() % 100);
    double k = temp * (1 - this->accident_propability());
    if (k > 20 && k < 100)
        this->determine_severity(s);
    else return;
}


void EmergencyService::determine_severity(Service* s)
{
    if (this->damage_factor() > 0 && this->damage_factor() < 11)
        s->process_accident(NEGLIGIBLE);

    else if (this->damage_factor() > 10 && this->damage_factor() < 31)
        s->process_accident(LIGHT);

    else if (this->damage_factor() > 30 && this->damage_factor() < 51)
        s->process_accident(MEDIUM);

    else if (this->damage_factor() > 50 && this->damage_factor() < 71)
        s->process_accident(SEVERE);

    else if (this->damage_factor() > 70 && this->damage_factor() < 91)
        s->process_accident(DISASTROUS);

    else if (this->damage_factor() > 90 && this->damage_factor() < 101)
        s->process_accident(CATASTROPHIC);
}


void EmergencyService:: process_year()
{
    for (auto s : TheArk::get_instance()->getServices())
    {
        this->create_accident(s);
    }
}

//для обработки переданных аварий
void EmergencyService::process_accident(AccidentSeverity as)
{
  /*  if (NEGLIGIBLE)
    {

    }*/

}

double EmergencyService::getState()
{
    return State;
}

void EmergencyService::setState(double s)
{
    State = s;
}

//unsigned int EmergencyService::getResourceDemand()
//{}
//unsigned int EmergencyService::getStaffDemand()
//{}

