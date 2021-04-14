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


//-----------------------Human-------------------------//

Human::Human(): Human(10, 100){}

Human::Human(unsigned int mentalStability, unsigned int PhysicalHealth)
{
    this->MENTAL_STABILITY = mentalStability;
    this->age = 0;

    this->amount_of_black_accidents = 0;
    this->type_as_a_worker = -1;
    this->is_alive = true;
    this->is_able_to_work = false;
    this->is_able_to_study = false;

    this->physical_health = PhysicalHealth;
    this->moral_health = 100;
    this->year_of_education = -1;

}

Human::Human(unsigned int common_status_of_the_ark):
    Human(10, 100){
    this->physical_health *= (common_status_of_the_ark / 100);
}
unsigned int Human::getMentalStability() const {
    return MENTAL_STABILITY;
}

unsigned int Human::getAge() const {
    return age;
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

unsigned int Human::getAmountOfBlackAccidents() const {
    return amount_of_black_accidents;
}

unsigned int Human::getYearOfEducation() const {
    return year_of_education;
}

bool Human::isAlive() const {
    return is_alive;
}

bool Human::isAbleToWork() const {
    return is_able_to_work;
}

void Human::setAmountOfBlackAccidents(unsigned int amountOfBlackAccidents) {
    amount_of_black_accidents = amountOfBlackAccidents;
}


void Human::setYearOfEducation(unsigned int yearOfEducation) {
    year_of_education = yearOfEducation;
}

void Human::setAge(int Age) {
    this->age = Age;
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



bool Human::isAbleToStudy() const {
    return this->is_able_to_study;
}

void Human::setIsAbleToStudy(bool isAbleToStudy) {
    this->is_able_to_study = isAbleToStudy;
}




