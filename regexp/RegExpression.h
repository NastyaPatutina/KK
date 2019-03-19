//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_REGEXPRESSION_H
#define LAB1_REGEXPRESSION_H

#include "../gram/Terminal.h"
#include <list>


class RegExpression {
public:
    enum Quantifier {
        Non = 0,
        MoreNull = 1,
        MoreOne = 2
    };

    RegExpression();

    RegExpression(Terminal terminal);
    void addSymbol(Terminal terminal);
    void addSymbol(Terminal terminal, Quantifier quantifier);
    std::string toString();

private:
    std::list<std::pair<Terminal, Quantifier>> regExpBody;
};


#endif //LAB1_REGEXPRESSION_H
