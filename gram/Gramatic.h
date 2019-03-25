//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_GRAMATIC_H
#define LAB1_GRAMATIC_H


#include <list>
#include "Terminal.h"
#include "NotTerminal.h"
#include "Equation.h"

class Gramatic {
private:
    std::list <Terminal> terminals;
    std::list <NotTerminal> notTerminals;
    std::list <Equation> rules;
    NotTerminal startSymbol;

public:
    const std::list<Terminal> &getTerminals() const;

    void setTerminals(const std::list<Terminal> &terminals);

    const std::list<NotTerminal> &getNotTerminals() const;

    void setNotTerminals(const std::list<NotTerminal> &notTerminals);

    const std::list<Equation> &getRules() const;

    void setRules(const std::list<Equation> &rules);

    const NotTerminal &getStartSymbol() const;

    void setStartSymbol(const NotTerminal &startSymbol);

    Terminal* getTerminal(std::string termName);

    NotTerminal* getNotTerminal(std::string termName);

    RegExpression solve();

    Equation findEquationForNotTerm (const NotTerminal &startSymbol);
};


#endif //LAB1_GRAMATIC_H
