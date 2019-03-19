//
// Created by patutinaam on 12.03.19.
//

#include "EquationSystem.h"

EquationSystem::EquationSystem() {
    this->system = std::initializer_list<Equation>();
}

EquationSystem::EquationSystem(Equation equation) {
    this->system.push_back(equation);
}

void EquationSystem::addEquation(Equation equation) {
    this->system.push_back(equation);
}

RegExpression EquationSystem::solve(NotTerminal notTerminal) {
    return RegExpression(Terminal());
}
