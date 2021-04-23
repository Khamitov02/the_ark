//
// Created by Amisto on 4/2/2021.
//

#include "Population.h"
#include "TheArk.h"
#include "MedicalService.h"
#include "SocialService.h"
#include <cstdlib>

Population::Population() : children(0), adults(0), oldmen(0){}

unsigned int Population::getChildren() const {
    return this->children;
}

unsigned int Population::getAdults() const {
    return this->adults;
}

unsigned int Population::getOldmen() const {
    return this->oldmen;
}

unsigned int Population::getTotal() const {
    return this->people.size();
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

list<shared_ptr<Human>>& Population::getPeople()
{
    return this->people;
}
array<list<shared_ptr<Human>>, 7>& Population::getAllClassification()
{
     return this->classifications_of_humans;
}

void Population::processYear() {

    //this->native_death();
    this->check_dead_people();

    // далее идет обработка по возрасту
    unsigned int n_of_adults = 0;
    unsigned int n_of_oldmen = 0;
    unsigned int n_of_children = 0;
    unsigned int HisAge = 0;
    for (auto it = people.begin(); it != people.begin(); it++) {
        HisAge = (*it)->getAge();
        if (HisAge < this->borderChildrenToAdults()){
            n_of_children++;
            if ((rand()%((unsigned int)(1 / this->deathRateChildren()))) < 1)
                (*it)->setIsAlive(false);
        }
        if ((HisAge >= this->borderChildrenToAdults()) && (HisAge < borderAdultsToOldmen())){
            n_of_adults++;
            if ((rand()%((unsigned int)(1 / this->deathRateAdults()))) < 1)
                (*it)->setIsAlive(false);
        }
        if (HisAge >= this->borderAdultsToOldmen() && HisAge <= 100){
            n_of_oldmen++;
            if ((rand()%((unsigned int)(1 / this->deathRateOldmen()))) < 1)
                (*it)->setIsAlive(false);
        }
        if(HisAge > 100 || (*it)->isAlive() == false){
            people.erase(it);
        }
        (*it)->setAge(HisAge + 1);

    }
    this->children = n_of_children;
    this->adults = n_of_adults;
    this->oldmen = n_of_oldmen;
    // конец обработки по возрасту

    // тут ещё безусловно нужно написать рождаемость, иначе все подохнут
    // дальше идет просмотр обучающихся и обработка тех, кто отучился. Их пихаем в службы по запросам
    // распределение остальных людей по соответвующим категориям

    //конец обработки
}

void Population::native_death() {
    for (shared_ptr<Human>& person : this->people)
    {
        if (person->getAge() < this->borderChildrenToAdults())
        {
            if ((rand()%((unsigned int)(1 / this->deathRateChildren()))) < 1)
                person->setIsAlive(false);
        }

        if (person->getAge() > this->borderChildrenToAdults() && person->getAge() < this->borderAdultsToOldmen())
        {
            if ((rand()%((unsigned int)(1 / this->deathRateAdults()))) < 1)
                person->setIsAlive(false);
        }

        if (person->getAge() > this->borderAdultsToOldmen())
        {
            if ((rand()%((unsigned int)(1 / this->deathRateOldmen()))) < 1)
                person->setIsAlive(false);
        }

        if (person->getAge() > 100){
            person->setIsAlive(false);
        }
    }
}

void Population::check_dead_people() {
    /*for (auto it = this->people.begin(); it != this->people.end(); it++)
    {
        if (!(*it)->isAlive())
        {
            this->people.erase(it);
        }
    }*/
    for (list<shared_ptr<Human>>& classification: this->classifications_of_humans)
    {
        for (auto it = classification.begin(); it != classification.end(); it++)
        {
            if ((*it)->isAlive() == false || (*it)->getAge() >= this->borderAdultsToOldmen() )
            {
                //(*it)->setTypeAsWorker();
                classification.erase(it);
            }
        }
    }
}

void Population::init(unsigned int total) {
    children = (unsigned int)(0.1 * total);
    oldmen = (unsigned int)(0.2 * total);
    adults = total - children - oldmen;

    for(int i = 0; i < children; i++){          // заполняем детьми
        auto* person = new Human();
        person->setAge((rand()% this->borderChildrenToAdults()));
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }
    for(int i = 0; i < oldmen; i++) {            // заполняем стариками
        auto *person = new Human;
        person->setAge((this->borderAdultsToOldmen() + rand() % (100 - this->borderAdultsToOldmen() + 1)));
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }
    for(int i = 0; i < adults; i++){        // заполняем взрослыми всех остальных людей
        auto* person = new Human;
        person->setAge((this->borderChildrenToAdults()+ rand()% (this->borderAdultsToOldmen() - this->borderChildrenToAdults() + 1)));
        auto ptr = shared_ptr<Human>(person);
        people.push_back(ptr);
    }
    // далее идет сортировка по необходимым классификациям

   /* for(int i = 0; i <= classifications_of_humans.size(); i++){
        switch(i){
            case 1:
                classifications_of_humans[i]. = TheArk::get_instance()->getMedicalService()->getNStaff();

        }
    }*/
}


