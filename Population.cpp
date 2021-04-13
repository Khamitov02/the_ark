//
// Created by Amisto on 4/2/2021.
//

#include "Population.h"
#include "TheArk.h"
#include "MedicalService.h"
#include "SocialService.h"
#include <cstdlib>
Population::Population() : children(0), adults(0), oldmen(0), number_of_people(0){}

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
    for(it = people.begin(); it != people.end(); it++){
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
    this->number_of_people = total;
    people.reserve(number_of_people);

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
    number_of_people = people.size();
}


/////////////////////////////////////////////////Human////////////////////////////////////////////////////////////
unsigned int Human::getMentalStability() const {
    return MENTAL_STABILITY;
}

unsigned int Human::getAge() const {
    return age;
}

unsigned int Human::getLevelOfAnger() const {
    return level_of_anger;
}

unsigned int Human::getPhysicalHealth() const {
    return physical_health;
}

unsigned int Human::getMoralHealth() const {
    return moral_health;
}

unsigned int Human::getTypeAsAWorker() const {
    return type_as_a_worker;
}

bool Human::isAlive() const {
    return is_alive;
}

bool Human::isAbleToWork() const {
    return is_able_to_work;
}


void Human::setAge(int age) {
    this->age = age;
}

void Human::setLevelOfAnger(unsigned int levelOfAnger) {
    this->level_of_anger = levelOfAnger;
}

void Human::setPhysicalHealth(unsigned int physicalHealth) {
    this->physical_health = physicalHealth;
}

void Human::setMoralHealth(unsigned int moralHealth) {
    this->moral_health = moralHealth;
}

void Human::setTypeAsAWorker(unsigned int typeAsAWorker) {
    this->type_as_a_worker = typeAsAWorker;
}

void Human::setIsAlive(bool isAlive) {
    this->is_alive = isAlive;
}

void Human::setIsAbleToWork(bool isAbleToWork) {
    is_able_to_work = isAbleToWork;
}
Human::Human(): Human(10,0){}
Human::Human(unsigned int mentalStability, unsigned int common_status_of_the_ark):
        MENTAL_STABILITY(mentalStability),
        age(0),
        level_of_anger(0),
        moral_health(100),
        amount_of_black_accidents(0),
        type_as_a_worker(0),
        is_alive(true),
        is_able_to_work(false)
{
    //
}


