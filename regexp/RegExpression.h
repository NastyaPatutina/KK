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

    struct Item {
        Terminal body;
        Quantifier quantifier;
        RegExpression* regExpression=NULL;
        bool isOr = false;
        RegExpression* otherRegExpression=NULL;
    public:
        bool operator==(const RegExpression::Item item) const{
            return body.getName() == item.body.getName() &&
                    quantifier == item.quantifier &&
                    isOr == item.isOr &&
                    quantifier == item.quantifier &&
                    otherRegExpression == item.otherRegExpression ;
        }
    };
    RegExpression();

    RegExpression(Terminal terminal);
    void addSymbol(Terminal terminal);
    void addSymbol(Terminal terminal, Quantifier quantifier);
    std::string toString();
    RegExpression* addQuantifier(RegExpression::Quantifier quantifier);
    RegExpression* addOrRegExpression(RegExpression regExpression);
    void pushBack(RegExpression regExpression);
    void pushFront(RegExpression regExpression);
    bool operator==(const RegExpression regExpression) const;

private:
    std::list<Item> regExpBody;
};


#endif //LAB1_REGEXPRESSION_H
