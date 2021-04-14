//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_POPULATION_H
#define THE_ARK_POPULATION_H
#include <vector>

using std::vector;

class Human {
private:
    unsigned int MENTAL_STABILITY; // <- это поле контролирует СС

    unsigned int age;
    unsigned int physical_health;
    unsigned int moral_health; // <- это поле контролирует СС
    unsigned int amount_of_black_accidents; // количество негативных ситуаций, влияющих на человека
                                                // если их больше, чем моральная стабильность, то моральное здоровье человека уменьшается
                                                // <- это поле контролирует СС

    unsigned int type_as_a_worker; // давайте условимся: 2 - ученый, 1 - рабочий; 0 - нет профессии

    unsigned int year_of_education; // 0 - не учится
                                    // <- это поле контролирует СС

    bool is_alive;
    bool is_able_to_work; // <- это поле контролирует СС
    bool is_able_to_study; //

public:
    Human();
    Human(unsigned int mentalStability, unsigned int PhysicalHealth);
    Human(unsigned int common_status_of_the_ark);

    unsigned int getMentalStability() const;
    unsigned int getAge() const;
    unsigned int getPhysicalHealth() const;
    unsigned int getMoralHealth() const;
    unsigned int getTypeAsAWorker() const;
    unsigned int getAmountOfBlackAccidents() const;
    unsigned int getYearOfEducation() const;
    bool isAlive() const;
    bool isAbleToWork() const;
    bool isAbleToStudy() const;

    void setAge(int Age);
    void setPhysicalHealth(unsigned int physicalHealth);
    void setMoralHealth(unsigned int moralHealth);
    void setTypeAsAWorker(unsigned int typeAsAWorker);
    void setIsAlive(bool isAlive);
    void setIsAbleToWork(bool isAbleToWork);
    void setIsAbleToStudy(bool isAbleToStudy);
    void setAmountOfBlackAccidents(unsigned int amountOfBlackAccidents);
    void setYearOfEducation(unsigned int yearOfEducation);

    friend class Population;
};


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