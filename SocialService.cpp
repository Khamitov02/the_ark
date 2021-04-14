//
// Created by Amisto on 4/2/2021.
//

#include "SocialService.h"

SocialService::SocialService()
{
    this->efficiency_percentage = 15;
    this->staff.resize(0);
    this->n_years_of_education = 5; // <- все изначально учатся 5 лет
    this->n_staff_we_want = 50; // <- на всякий случай, вдруг что поломается
    this->update_n_staff_we_want();
    this->suicide_counter = 0;
}

void SocialService::process_accident(AccidentSeverity as)
{/*no problems*/}

unsigned int SocialService::borderChildrenToAdults()
{
    return 18;
}

double SocialService::getState() {
    return 100;
}

void SocialService::setState(double s) {/*nothing to do*/}

void SocialService::update_n_staff_we_want() {
    this->n_staff_we_want = (TheArk::get_instance()->getPopulation()->people.size() / (2 * this->efficiency_percentage)) + 10;
}

unsigned int SocialService::getResourceDemand() {
    return 0; // наша служба не нуждается в ресурсах на начальном этапе придумывания
}

unsigned int SocialService::getResourcePriority() {return 6;} // последний приоритет

unsigned int SocialService::getStaffDemand(){
    return this->n_staff_we_want;
}

unsigned int SocialService::getStaffPriority(){
    unsigned int labor_shortage_rate = 6 - (this->clients.size() / (this->staff.size() * this->efficiency_percentage));
    if (labor_shortage_rate <= 0) labor_shortage_rate = 1;
    return labor_shortage_rate;
}

bool SocialService::changeStaff (int delta) {/*сделаем, если потребуется*/
    return true;}

bool SocialService::changeResources(int delta){/*сделаем, если потребуется*/
    return true;}

void SocialService::update_people(){
    for (auto person : TheArk::get_instance()->getPopulation()->people)
    {
        this->update_person(person);
    }
}

// самый главный самый жырный метод
void SocialService::process_year() {
    this->update_people();
    // так же тут будет обработка действий службы и тд и тп
}

void SocialService::update_person(Human &person) {

    // логика "если плохих событий не меньше, чем ментальная стабильность - то минус ментальное здоровье"
    if (person.getMentalStability() <= person.getAmountOfBlackAccidents())
        person.setMoralHealth( (unsigned int)(person.getMoralHealth()/(1.2)) );

    // логика "влияние ментального здоровья на жизнедеятельность"
    if (person.getMoralHealth() < 30) {
        if (person.getMoralHealth() < 20)
            if (person.isAbleToWork())
                person.setIsAbleToWork(false);
        if (person.isAbleToStudy())
            person.setIsAbleToStudy(false);
        if (person.getMoralHealth() < 3)
            person.setIsAlive(false);
    }
    else {
        if (person.getTypeAsAWorker()){
            if (person.getYearOfEducation()) {
                person.setIsAbleToWork(false);
                person.setIsAbleToStudy(true);
            } else {
                person.setIsAbleToWork(true);
                person.setIsAbleToStudy(false);
            }
        }
    }

    // логика "сособен ли обучаться"
    if (!person.isAbleToStudy())
        if (person.getAge() >= this->borderChildrenToAdults())
            person.setIsAbleToStudy(true);

    // логика "обработка обучения": если может, человек начинает учиться
    if (person.isAbleToStudy())
        person.setYearOfEducation(person.getYearOfEducation() + 1);
    if (person.getYearOfEducation() > 5) {
        person.setYearOfEducation(0);
        person.setIsAbleToWork(true);
        person.setIsAbleToStudy(false);
    }

    // логика добавления в клиенты службы
    if (person.getMoralHealth() < 70)
        clients.push(&person); // <- добавил поинтер в очередь
        // пока думаю, как обрабатывать повторы
}