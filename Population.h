//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_POPULATION_H
#define THE_ARK_POPULATION_H
#include <vector>

using std::vector;

class Human {
private:
    unsigned int MENTAL_STABILITY;

    unsigned int age;

    unsigned int level_of_anger;

    unsigned int physical_health;
    unsigned int moral_health;
    unsigned int amount_of_black_accidents; // количество негативных ситуаций, влияющих на человека
    // если их больше, чем моральная стабильность, то моральное здоровье человека уменьшается

    unsigned int type_as_a_worker;

    bool is_alive;
    bool is_able_to_work;

public:
    Human();
    Human(unsigned int mentalStability,  unsigned int common_status_of_the_ark);

    unsigned int getMentalStability() const;

    unsigned int getAge() const;

    void setAge(int age);

    unsigned int getLevelOfAnger() const;

    unsigned int getPhysicalHealth() const;

    unsigned int getMoralHealth() const;

    unsigned int getTypeAsAWorker() const;

    bool isAlive() const;

    bool isAbleToWork() const;

    void setLevelOfAnger(unsigned int levelOfAnger);

    void setPhysicalHealth(unsigned int physicalHealth);

    void setMoralHealth(unsigned int moralHealth);

    void setTypeAsAWorker(unsigned int typeAsAWorker);

    void setIsAlive(bool isAlive);

    void setIsAbleToWork(bool isAbleToWork);
    friend class Population;
};


class Population {
private:
    unsigned int children;
    unsigned int adults;
    unsigned int oldmen;
    unsigned int number_of_people; // количество людей на корабле
    unsigned int borderChildrenToAdults();
    unsigned int borderAdultsToOldmen();
    double deathRateChildren();
    double deathRateAdults();
    double deathRateOldmen();
public:
    Population();
    vector<Human> people;

    unsigned int get_number_of_people() const;

    unsigned int getChildren() const;
    unsigned int getAdults() const;
    unsigned int getOldmen() const;
    unsigned int getTotal() const;

    void init(unsigned int total);
    void processYear(); // итерация по всем категориям населения - кто перешел из категорию в категорию, обработка смертности
};

#endif //THE_ARK_POPULATION_H