//
// Created by patutinaam on 11.03.19.
//

#include "RegExpression.h"

RegExpression::RegExpression(Terminal terminal) {
    this->regExpBody.emplace_back(terminal,Quantifier::Non);
}

void RegExpression::addSymbol(Terminal terminal, RegExpression::Quantifier quantifier) {
    this->regExpBody.emplace_back(terminal, quantifier);
}

void RegExpression::addSymbol(Terminal terminal) {
    this->regExpBody.emplace_back(terminal,Quantifier::Non);

}

std::string RegExpression::toString() {
    return "";
}

RegExpression::RegExpression() {}
