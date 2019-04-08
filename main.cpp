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

Gramatic* fill_gramm(json j) {
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
    std::list<Equation*> grammRules;
    for(json::iterator it = j["rules"].begin(); it != j["rules"].end(); ++it) {
        Equation* eq = new Equation();
        NotTerminal* term = new NotTerminal();
        term->setName((*it).at("res"));
        eq->setResNotTerm(*term);
        std::list<std::pair<RegExpression*, NotTerminal*>> rules;
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
            rules.emplace_back(regExp, notTerm);
        }
        eq->setRule(rules);
        grammRules.push_back(eq);
    }
    gm->setRules(grammRules);
    NotTerminal* notTerm = gm->getNotTerminal(j["start"]);
    gm->setStartSymbol(*notTerm);
    return gm;
}

void testing(std::list<std::string> list){
    std::list<std::string>::iterator i;
    for (i = list.begin(); i != list.end(); ++i) {
        std::ifstream infile("../" + *i + ".json");
        json j = json::parse(infile);
        Gramatic *gm = fill_gramm(j);

        std::cout << "\n\n==> RegExpression: \n\n";

        RegExpression result = gm->solve();
        std::cout << result.toString() << std::endl;

        std::cout << "\n\n==> NFA: \n\n";

        NFA required_nfa;
        required_nfa = required_nfa.re_to_nfa(result);
        required_nfa.display();
        required_nfa.write_to_file("../NFA" + *i +".dot");

        std::cout << "\n\n==> DFA: \n\n";

        DFA required_dfa;
        required_dfa = required_dfa.nfa_to_dfa(required_nfa);
        required_dfa.display();
        required_dfa.write_to_file("../DFA" + *i +".dot");
        std::string comm = "dot -Tpdf ../DFA" + *i +".dot -o ../DFA" + *i +".pdf";
        system(comm.c_str());
        comm = "dot -Tpdf ../NFA" + *i +".dot -o ../NFA" + *i +".pdf";
        system(comm.c_str());
    }
}
int main(int argc, char *argv[]) {
    std::string file_name = "../inputGramm.json";
    if (argc==2){
        if (strcmp(argv[1], "--test") == 0){
            std::list<std::string> test_names {"inputGramm", "inputGramm2", "inputGramm3", "inputGramm4"};
            testing(test_names);
            return 0;
        } else {
            file_name = argv[1];
        }
    }
    std::ifstream infile(file_name);
    json j = json::parse(infile);
    Gramatic* gm = fill_gramm(j);

    std::cout<<"\n\n==> RegExpression: \n\n";

    RegExpression result = gm->solve();
    std::cout << result.toString() << std::endl;

    std::cout<<"\n\n==> NFA: \n\n";

    NFA required_nfa;
    required_nfa = required_nfa.re_to_nfa(result);
    required_nfa.display();
    required_nfa.write_to_file("../NFA.dot");

    std::cout<<"\n\n==> DFA: \n\n";

    DFA required_dfa;
    required_dfa = required_dfa.nfa_to_dfa(required_nfa);
    required_dfa.display();
    required_dfa.write_to_file("../DFA.dot");

    return 0;
}