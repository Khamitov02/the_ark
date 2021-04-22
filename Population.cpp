//
// Created by Amisto on 4/2/2021.
//

#include "Population.h"
#include "TheArk.h"
#include "MedicalService.h"
#include "SocialService.h"
#include <cstdlib>
Population::Population() : children(0), adults(0), oldmen(0){}

unsigned int Population::get_number_of_people() const{
    return people.size();
}

unsigned int Population::getChildren() const {
    return children;
}

unsigned int Population::getAdults() const {
    return adults;
}

unsigned int Population::getOldmen() const {
    return oldmen;
}

unsigned int Population::getTotal() const {
    return children + adults + oldmen;
}

void Population::processYear() {
    int HisAge;
    adults = 0;
    oldmen = 0;
    children = 0;
    std :: list<shared_ptr<Human>> :: iterator it;
    for (it = people.begin(); it != people.end(); ++it) {
        HisAge = (*it)->age;
        if (HisAge < borderChildrenToAdults()) children++;
        if (HisAge >= borderChildrenToAdults() && HisAge < borderAdultsToOldmen()) adults++;
        if (HisAge >= borderAdultsToOldmen() && HisAge <= 100) oldmen++;
        (*it)->age++;
        if (HisAge > 100 || (*it)->isAlive() == false){
            people.erase(it);
        }
    }
}

unsigned int Population::borderChildrenToAdults()
{
    return TheArk::get_instance()->getSocialService()->borderChildrenToAdults();
}

unsigned int Population::borderAdultsToOldmen()
{
    return TheArk::get_instance()->getMedicalService()->borderAdultsToOldmen();
}

double Population::deathRateChildren()
{
    return TheArk::get_instance()->getMedicalService()->deathRateChildren();
}

double Population::deathRateAdults()
{
    return TheArk::get_instance()->getMedicalService()->deathRateAdult();
}

double Population::deathRateOldmen()
{
    return TheArk::get_instance()->getMedicalService()->deathRateOldmen();
}


void Population::init(unsigned int total) {
    children = 0.1 * total;
    oldmen = 0.2 * total;
    adults = total - children - oldmen;


    for(int i = 0; i < children; i++){          // заполняем детьми
        Human* person = new Human;
        person->setAge(rand()% borderChildrenToAdults());
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }
    for(int i = 0; i < oldmen; i++){            // заполняем стариками
        Human* person = new Human;
        person->setAge(borderAdultsToOldmen()+ rand()% (100 - borderAdultsToOldmen() + 1));
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }


    for(int i = 0; i < adults; i++){        // заполняем взрослыми всех остальных людей
        Human* person = new Human;
        person->setAge(borderChildrenToAdults()+ rand()% (borderAdultsToOldmen() - borderChildrenToAdults() + 1));
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }
}




