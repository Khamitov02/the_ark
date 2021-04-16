//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_BIOLOGICALSERVICE_H
#define THE_ARK_BIOLOGICALSERVICE_H

#include "Service.h"

class BiologicalService : public Service {
private:
    
    double BioState;

public:
    
    BiologicalService();

    void process_accident(AccidentSeverity as) override
    {
        
    };                                // Принимаем параметр тяжести и сразу обрабатываем - пока не реализовано
    void process_year() override {};      // если у службы есть какая-то личная жизнь, она может заниматься ей тут
    double getState() override
    {
        return BioState;
    };                             // передаём состояние в процентах
    void setState(double s) override
    {
        BioState = s;
    };                       // инициализируем состояние
};


#endif //THE_ARK_BIOLOGICALSERVICE_H
