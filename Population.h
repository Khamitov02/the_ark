//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_POPULATION_H
#define THE_ARK_POPULATION_H
#include <vector>
#include "Human.h"

using std::vector;

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
    vector<Human> people;

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