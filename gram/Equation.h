//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_EQUATION_H
#define LAB1_EQUATION_H


#include <stack>
#include <string>
#include <list>
#include "GramSymbol.h"
#include "NotTerminal.h"
#include "../regexp/RegExpression.h"

class Equation {
private:
    NotTerminal resNotTerm;
    std::list<std::pair<RegExpression, NotTerminal*>> rule;
public:
    const NotTerminal &getResNotTerm() const;

    void setResNotTerm(const NotTerminal &resNotTerm);

    const std::list<std::pair<RegExpression, NotTerminal*>> &getRule() const;

    void setRule(const std::list<std::pair<RegExpression, NotTerminal*>> &rule);

    std::string toString();

    void fromString(std::string equation);

    RegExpression* findRegExp (NotTerminal notTerminal);

    RegExpression* findFreeTerm();

    bool haveNotTerm (NotTerminal notTerminal);

    void resolve();

    void change(Equation eq);

    void changeTermToRegExp(Equation eq);
};


#endif //LAB1_EQUATION_H
