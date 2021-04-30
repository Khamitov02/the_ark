//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_BIOLOGICALSERVICE_H
#define THE_ARK_BIOLOGICALSERVICE_H

#include "Service.h"

class BiologicalService : public Service {
private:
    int BioState;
public:
    BiologicalService();

    void process_accident(AccidentSeverity as) override;    // каждая служба должна уметь в своих терминах обработать переданную ей аварию
    void process_year() override {};                       // если у службы есть какая-то личная жизнь, она может заниматься ей тут
    double getState() override;                             // каждая служба должна уметь вернуть свое состояние в процентах, посчитав его в своих терминах
    void setState(double s) override;                       // функция для инициализации, каждая служба должна уметь получить состояние в процентах и пересчитать  его в своих терминах
};

struct coord;

int GetTypeId (int x);


class Animal {
public:
    char name;
    int id_biom;
    int heal;
    bool predator;
    bool haveBaby;

    void take_food(int feed);
};
class Pig : public Animal{
public:
    Pig();
};
class Cow : public Animal{
public:
    Cow();
};
class Wolf : public Animal
{
public:
    Wolf();

};
class Biom
{
public:
    double water; // <= 10000, if water 0 -> no animals
    double land; // <= 10000  if land 0 -> no animals
    double forest; // <= 10000, if fprest 0 -> no animals
    int id; //
    int free; //value of free spaces
    bool init; // was init?

    Biom();

    Biom (double water, double forest, int id);

    ~Biom ();

    void InitFree(); // Init function{

};


#endif //THE_ARK_BIOLOGICALSERVICE_H
