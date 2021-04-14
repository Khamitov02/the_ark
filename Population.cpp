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
    std :: vector<Human> :: iterator it;
    for(it = people.begin(); it != people.end(); ++it){
        it->age++;
        HisAge = it->age;
        if(HisAge < borderChildrenToAdults() )      children++;
        if(HisAge >= borderChildrenToAdults() && HisAge < borderAdultsToOldmen())      adults++;
        if(HisAge >= borderAdultsToOldmen() && HisAge <= 100)      oldmen++;
        if(HisAge > 100)    people.erase(it);
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
    people.reserve(total);

    for(int i = 0; i < children; i++){
        Human person;
        person.setAge(rand()% borderChildrenToAdults());
        people.push_back(person);
    }
    for(int i = 0; i < adults; i++){
        Human person;
        person.setAge(borderChildrenToAdults()+ rand()% (borderAdultsToOldmen() - borderChildrenToAdults() + 1));
        people.push_back(person);
    }
    for(int i = 0; i < oldmen; i++){
        Human person;
        person.setAge(borderAdultsToOldmen()+ rand()% (100 - borderAdultsToOldmen() + 1));
        people.push_back(person);
    }
}




