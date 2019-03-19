//
// Created by patutinaam on 11.03.19.
//

#include "Gramatic.h"

const std::list<Terminal> &Gramatic::getTerminals() const {
    return terminals;
}

void Gramatic::setTerminals(const std::list<Terminal> &terminals) {
    Gramatic::terminals = terminals;
}

const std::list<NotTerminal> &Gramatic::getNotTerminals() const {
    return notTerminals;
}

void Gramatic::setNotTerminals(const std::list<NotTerminal> &notTerminals) {
    Gramatic::notTerminals = notTerminals;
}

const std::list<Equation> &Gramatic::getRules() const {
    return rules;
}

void Gramatic::setRules(const std::list<Equation> &rules) {
    Gramatic::rules = rules;
}

const NotTerminal &Gramatic::getStartSymbol() const {
    return startSymbol;
}

void Gramatic::setStartSymbol(const NotTerminal &startSymbol) {
    Gramatic::startSymbol = startSymbol;
}

Terminal* Gramatic::getTerminal(std::string termName) {
    if (termName == "") {
        return NULL;
    }

    std::list<Terminal>::iterator i;
    for(i = terminals.begin(); i != terminals.end(); ++i) {
        if (i->getName() == termName)
            return &(*i);
    }
    return NULL;
}

NotTerminal* Gramatic::getNotTerminal(std::string notTermName) {
    if (notTermName == "") {
        return NULL;
    }

    std::list<NotTerminal>::iterator i;
    for(i = notTerminals.begin(); i != notTerminals.end(); ++i) {
        if (i->getName() == notTermName)
            return &(*i);
    }
    return NULL;
}
