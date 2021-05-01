#ifndef THE_ARK_NAVIGATIONSERVICE_H
#define THE_ARK_NAVIGATIONSERVICE_H

#include "Service.h"
#include "Human.h"
#include <vector>
#include "TheArk.h"
class NavigationService : public Service {

    double serviceState;           // состояние службы
    unsigned int resources;        // текущее количество ресурсов
    unsigned int staff;       // текущее количество персонала
    unsigned int maxStaff;        // нужное количество персонала
    unsigned int maxResources;     // нужное количество ресурсов
public:
    NavigationService();

    unsigned int getNStaff() const;

    // интерфейс для служб - какие методы они обязаны перекрыть
    virtual void process_accident(AccidentSeverity as) = 0; // каждая служба должна уметь в своих терминах обработать переданную ей аварию
    virtual void process_year() = 0;                        // если у службы есть какая-то личная жизнь, она может заниматься ей тут
    virtual double getState() = 0;                          // каждая служба должна уметь вернуть свое состояние в процентах, посчитав его в своих терминах
    virtual void setState(double s) = 0;                    // функция для инициализации, каждая служба должна уметь получить состояние в процентах и пересчитать  его в своих терминах

    // стандартное взаимодействие служб с остальным кодом, можно перекрывать, можно нет
    virtual unsigned int getResourceDemand();           // сколько ресурсов требуется
    virtual unsigned int getResourcePriority();         // с каким приоритетом служба будет требовать ресурсы
    virtual unsigned int getStaffPriority();            // с каким приоритетом слуюба будет требовать людей
    virtual unsigned int getStaffDemand() {return 0;};          // сколько людей требуется
    virtual bool changeStaff (int delta);               // сколько людей добавили или забрали (в т.ч. смертность)
    virtual bool changeResources(int delta);            // сколько ресурсов добавили или забрали (в т.ч. износ)

    virtual ~Service();
};

};
