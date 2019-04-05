//
// Created by patutinaam on 11.03.19.
//

#include "RegExpression.h"

RegExpression::RegExpression(Terminal terminal) {
    Item item;
    item.body = terminal;
    item.quantifier = Quantifier::Non;
    this->regExpBody.push_back(item);
}

void RegExpression::addSymbol(Terminal terminal, RegExpression::Quantifier quantifier) {
    Item item;
    item.body = terminal;
    item.quantifier = quantifier;
    this->regExpBody.push_back(item);
}

RegExpression* RegExpression::addQuantifier(RegExpression::Quantifier quantifier) {
    RegExpression* regExpression = new RegExpression();
    Item item;
    item.regExpression = new RegExpression(*this);
    item.quantifier = quantifier;
    regExpression->regExpBody.push_back(item);
    return regExpression;
}

void RegExpression::addSymbol(Terminal terminal) {
    Item item;
    item.body = terminal;
    item.quantifier = Quantifier::Non;
    this->regExpBody.push_back(item);

}

std::string RegExpression::toString() {
    std::string res = "";
    std::list<Item>::iterator i;
    for (i = this->regExpBody.begin(); i != this->regExpBody.end(); ++i) {
        res += (*i).toString();
    }
    return res;
}

RegExpression::RegExpression() {}

void RegExpression::pushBack(RegExpression regExpression) {
    this->regExpBody.insert(this->regExpBody.end(), regExpression.regExpBody.begin(), regExpression.regExpBody.end());
}

void RegExpression::pushFront(RegExpression regExpression) {
    this->regExpBody.insert(this->regExpBody.begin(), regExpression.regExpBody.begin(), regExpression.regExpBody.end());
}

bool RegExpression::operator==(const RegExpression regExpression) const {
    return this->regExpBody == regExpression.regExpBody;
}

RegExpression *RegExpression::addOrRegExpression(RegExpression regExpression) {
    RegExpression* newRegExpression = new RegExpression();
    Item item;
    item.regExpression = new RegExpression(*this);
    item.otherRegExpression = new RegExpression(regExpression);
    item.isOr = true;
    item.quantifier = Quantifier::Non;
    newRegExpression->regExpBody.push_back(item);
    return newRegExpression;
}

std::list<RegExpression::Item> RegExpression::getRegExpBody() {
    return this->regExpBody;
}
