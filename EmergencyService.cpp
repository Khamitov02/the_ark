//
// Created by Amisto on 4/2/2021.


//Каждая служба должна уметь в своих терминах обрабатывать аварийные ситуации по запросу от ЧС.
//Например, ЧС говорит, что авария средней тяжести произошла в БС.БС должна уметь в своих терминах получить соответствующий урон


//Могут ли на самой ЧС случаться аварии? Что влияет на состояние ЧС? А что влияет на состояние других служб, кроме аварий?
//Как реализовать то, что разные службы могут вызывать аварии ДРУГ У ДРУГА?

// какие нужны ресурсы, если нужны?  оружие! инструменты!

//что значит прекращать аварию? как прекращать? - не прекращать, они сами 

//службы чинят сами себя - мы им только передаем аварии
//
//да, на чс могут случаться аварии 
//
//человек 100, ресурсы, случаются ли аварии - это определяет состояние - задается снаружи, пользовательский ввод или интерфейс (сколько их) --- // на что они тратятся?
//
//
//восполнять - делать запрос - дадут

//
//что такое 60 - сама решает, что это такое

#include "EmergencyService.h"

EmergencyService::EmergencyService() : State(100)
{}


//интерфейс и вероятность аварий? Чем хуже состояние службы - тем выше вероятность аварии (рассчитывать эту зависимость)
//Чем хуже состояние ЧС - тем выше тяжесть аварии

//от 0 до 1
double EmergencyService::accident_propability()
{
    double s = TheArk::get_instance()->getMedicalService()->getState() / 100;
    return 1 / pow(3, 3 * s);
    //обратнопропорцинонально состоянию самой службы
}

//от 1 до 100
unsigned int EmergencyService::damage_factor()
{
    if (this->getState() != 0)
        return 100 / (this->getState());
    else return 100;
    //чем лучше состояние чс, тем меньше коэф -> меньше ущерб
}


//для создания своих

void EmergencyService::create_accident(Service* s)
{
    srand(time(0));
    int temp = (20 + rand() % 100);
    double k = temp * (1 - this->accident_propability());
    if (k > 20 && k < 100)
        this->determine_severity(s);
    else return;
}

//хочется иметь массив указателей/ссылок на службы и передавать в функции; в цикле вызывать для каждой из 6
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

//для обработки переданных
void EmergencyService::process_accident(AccidentSeverity as)
{
    if (NEGLIGIBLE)
    {

    }

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

