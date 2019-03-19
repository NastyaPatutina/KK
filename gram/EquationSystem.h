//
// Created by patutinaam on 12.03.19.
//

#ifndef LAB1_EQUATIONSYSTEM_H
#define LAB1_EQUATIONSYSTEM_H


#include "Equation.h"
#include "../regexp/RegExpression.h"

class EquationSystem {
private:
    std::list<Equation> system;
public:
    EquationSystem();
    EquationSystem(Equation equation);
    void addEquation (Equation equation);
    RegExpression solve(NotTerminal notTerminal);
};


#endif //LAB1_EQUATIONSYSTEM_H
