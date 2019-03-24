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

RegExpression* Equation::findRegExp(NotTerminal notTerminal) {
    std::list<std::pair<RegExpression, NotTerminal*>, std::allocator<std::pair<RegExpression, NotTerminal*>>>::iterator i;
    for(i = rule.begin(); i != rule.end(); ++i) {
        if ((*i).second != NULL && (*i).second->getName() == notTerminal.getName()) {
            return &(*i).first;
        }
    }
    return NULL;
}

void Equation::resolve() {
    RegExpression* regExpression = findRegExp(this->getResNotTerm());
    if (regExpression == NULL) {
        return;
    }
    RegExpression* changedRegExpression = new RegExpression(*(regExpression->addQuantifier(RegExpression::Quantifier::MoreNull)));
    std::list<std::pair<RegExpression, NotTerminal *>, std::allocator<std::pair<RegExpression, NotTerminal *>>>::iterator i;
    std::pair<RegExpression, NotTerminal *> current;
    for (i = rule.begin(); i != rule.end(); ++i) {
        if ((*i).second == NULL || (*i).second->getName() != this->getResNotTerm().getName()) {
            (*i).first.pushFront(*changedRegExpression);
        } else {
            current = *i;
        }
    }
    this->rule.remove(current);
}

void Equation::change(Equation eq) {
    if (haveNotTerm(eq.getResNotTerm())) {
        RegExpression *centralK = findRegExp(eq.getResNotTerm());

        std::list<std::pair<RegExpression, NotTerminal *>, std::allocator<std::pair<RegExpression, NotTerminal *>>>::iterator i;
        std::pair<RegExpression, NotTerminal *> current;
        for (i = rule.begin(); i != rule.end(); ++i) {
            if ((*i).second == NULL || (*i).second->getName() != eq.getResNotTerm().getName()) {
                if ((*i).second == NULL) {
                    RegExpression *regExpressionFirst = eq.findFreeTerm();
                    if (regExpressionFirst != NULL) {
                        if (centralK != NULL) {
                            regExpressionFirst->pushFront(*centralK);
                        }
                        RegExpression *regExpressionOld = this->findFreeTerm();
                        (*i).first = *(regExpressionFirst->addOrRegExpression(*regExpressionOld));
                    }
                } else {
                    RegExpression *regExpressionFirst = eq.findRegExp(*(*i).second);
                    if (regExpressionFirst != NULL) {
                        if (centralK != NULL) {
                            regExpressionFirst->pushFront(*centralK);
                        }
                        RegExpression *regExpressionOld = this->findRegExp(*(*i).second);
                        (*i).first = *(regExpressionFirst->addOrRegExpression(*regExpressionOld));
                    }
                }
            } else {
                current = *i;
            }
        }
        this->rule.remove(current);
    }
}

bool Equation::haveNotTerm(NotTerminal notTerminal) {
    std::list<std::pair<RegExpression, NotTerminal*>, std::allocator<std::pair<RegExpression, NotTerminal*>>>::iterator i;
    for(i = rule.begin(); i != rule.end(); ++i) {
        if ((*i).second->getName() == notTerminal.getName()) {
            return true;
        }
    }
    return false;
}

RegExpression *Equation::findFreeTerm() {
    std::list<std::pair<RegExpression, NotTerminal*>, std::allocator<std::pair<RegExpression, NotTerminal*>>>::iterator i;
    for(i = rule.begin(); i != rule.end(); ++i) {
        if ((*i).second == NULL) {
            return &(*i).first;
        }
    }
    return NULL;
}

