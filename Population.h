//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_POPULATION_H
#define THE_ARK_POPULATION_H
#include <vector>
#include <list>
#include <array>
#include "Human.h"

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

    double deathRateChildren();
    double deathRateAdults();
    double deathRateOldmen();
public:
    array<list<Human>, 7> people;

    Population();
    unsigned int get_number_of_people() const;
    unsigned int getChildren() const;
    unsigned int getAdults() const;
    unsigned int getOldmen() const;
    unsigned int getTotal() const;

    void init(unsigned int total);
    void processYear(); // итерация по всем категориям населения - кто перешел из категорию в категорию, обработка смертности
};

#endif //THE_ARK_POPULATION_H