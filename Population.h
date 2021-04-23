//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_POPULATION_H
#define THE_ARK_POPULATION_H
#include <vector>
#include <memory>
#include <list>
#include <array>
#include "Human.h"
using std::shared_ptr;
using std::vector;
using std::list;
using std::array;

class Population {
private:
    unsigned int children;
    unsigned int adults;
    unsigned int oldmen;

    unsigned int borderChildrenToAdults();
    unsigned int borderAdultsToOldmen();

    unsigned int getMedicalStaff();

    double deathRateChildren();
    double deathRateAdults();
    double deathRateOldmen();

    void native_death();
    void check_dead_people(); // пробежались по всем всем листам и попнули умерших

    array<list<shared_ptr<Human>>, 7> classifications_of_humans;
    list<shared_ptr<Human>> people;


public:
    Population();
    unsigned int getChildren() const;
    unsigned int getAdults() const;
    unsigned int getOldmen() const;
    unsigned int getTotal() const;

    list<shared_ptr<Human>>& getPeople();
    array<list<shared_ptr<Human>>, 7>& getAllClassification();

    void init(unsigned int total);
    void processYear(); // итерация по всем категориям населения - кто перешел из категорию в категорию, обработка смертности
};

#endif //THE_ARK_POPULATION_H
