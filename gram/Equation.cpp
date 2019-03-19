//
// Created by patutinaam on 11.03.19.
//

#include "Equation.h"
#include "../regexp/RegExpression.h"

std::string Equation::toString() {
    std::string ruleStr;
    std::list<std::pair<RegExpression, NotTerminal*>, std::allocator<std::pair<RegExpression, NotTerminal*>>>::iterator i;
    for(i = rule.begin(); i != rule.end(); ++i) {
            ruleStr += (*i).first.toString() + (*i).second->getName();
    }
    return resNotTerm.getName() + " -> " + ruleStr;
}

void Equation::fromString(std::string equation) {
    unsigned long posNotTerm = equation.find_first_of("->");
    std::string notTermName = equation.erase(0, posNotTerm);
    resNotTerm.setName(notTermName);
}

const NotTerminal &Equation::getResNotTerm() const {
    return resNotTerm;
}

void Equation::setResNotTerm(const NotTerminal &resNotTerm) {
    Equation::resNotTerm = resNotTerm;
}

const std::list<std::pair<RegExpression, NotTerminal*>> &Equation::getRule() const {
    return rule;
}

void Equation::setRule(const std::list<std::pair<RegExpression, NotTerminal*>> &rule) {
    Equation::rule = rule;
}
