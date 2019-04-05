#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <zconf.h>
#include "nlohmann/json.hpp"
#include "gram/GramSymbol.h"
#include "gram/Terminal.h"
#include "gram/NotTerminal.h"
#include "gram/Equation.h"
#include "gram/Gramatic.h"
#include "FA/DFA.h"

using json = nlohmann::json;

int main() {
    std::ifstream infile("../inputGramm.json");
    json j = json::parse(infile);
    Gramatic* gm = new Gramatic();
    std::list<NotTerminal> notterms;
    std::list<Terminal> terms;
    for(json::iterator it = j["notTerminal"].begin(); it != j["notTerminal"].end(); ++it) {
        NotTerminal* notTerm = new NotTerminal();
        notTerm->setName(*it);
        notterms.push_back(*notTerm);
    }
    for(json::iterator it = j["terminal"].begin(); it != j["terminal"].end(); ++it) {
        Terminal* term = new Terminal();
        term->setName(*it);
        terms.push_back(*term);
    }
    gm->setNotTerminals(notterms);
    gm->setTerminals(terms);
    std::list<Equation> grammRules;
    for(json::iterator it = j["rules"].begin(); it != j["rules"].end(); ++it) {
        Equation* eq = new Equation();
        NotTerminal* term = new NotTerminal();
        term->setName((*it).at("res"));
        eq->setResNotTerm(*term);
        std::list<std::pair<RegExpression, NotTerminal*>> rules;
        json subj = *it;
        for(json::iterator itRule = subj["rules"].begin(); itRule != subj["rules"].end(); ++itRule) {
            std::string currentRule = (*itRule);
            RegExpression* regExp = new RegExpression();
            std::string lastChopedRule = currentRule;
            currentRule += "ARRR";
            while(lastChopedRule != currentRule) {
                currentRule = lastChopedRule;
                std::list<Terminal>::iterator i;
                for (i = terms.begin(); i != terms.end(); ++i) {
                    if (currentRule.find_first_of((*i).getName()) == 0) {
                        regExp->addSymbol(*i);
                        lastChopedRule = lastChopedRule.erase(0, (*i).getName().length());
                    }
                }
            }
            NotTerminal* notTerm = gm->getNotTerminal(currentRule);
            rules.emplace_back(*regExp, notTerm);
        }
        eq->setRule(rules);
        grammRules.push_back(*eq);
    }
    gm->setRules(grammRules);
    NotTerminal* notTerm = gm->getNotTerminal(j["start"]);
    gm->setStartSymbol(*notTerm);

    RegExpression result = gm->solve();
    std::cout << result.toString();

    NFA required_nfa;
    required_nfa = required_nfa.re_to_nfa(result);
    required_nfa.display();

    std::cout<<"\n\n==> DFA : \n\n";

    DFA required_dfa;
    required_dfa = required_dfa.nfa_to_dfa(required_nfa);
    required_dfa.display();

    return 0;
}