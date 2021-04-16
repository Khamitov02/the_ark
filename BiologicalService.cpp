//
// Created by Amisto on 4/2/2021.
//

#include "BiologicalService.h"

BiologicalService::BiologicalService()
{

}

void BiologicalService::process_accident(AccidentSeverity as)
{
// Принимаем параметр тяжести и сразу обрабатываем - пока не реализовано
}

double BiologicalService::getState() {
    return BioState;  // передаём состояние в процентах
}

void BiologicalService::setState(double s) {
      BioState = s;   // инициализируем состояние
}
