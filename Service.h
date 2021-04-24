//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_SERVICE_H
#define THE_ARK_SERVICE_H

#include <list>
#include "Population.h"
#include "Enums.cpp"
using std::list;

class Service {
private:
    unsigned int n_staff; // количество рабочих всего

    unsigned int resources; // количество задействованных ресурсов
    // сюда можно добавить руководителя службы
public:
    Service();

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

#endif //THE_ARK_SERVICE_H
