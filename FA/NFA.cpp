//
// Created by patutinaam on 03.04.19.
//

#include "NFA.h"
#include "../regexp/RegExpression.h"

NFA NFA::re_to_nfa(RegExpression::Item regExpression) {
    NFA res;
    if (regExpression.isOr){
        std::vector<NFA> selections;
        selections.push_back(re_to_nfa(*regExpression.otherRegExpression));
        selections.push_back(re_to_nfa(*regExpression.regExpression));
        return or_selection(selections, 2);
    }
    if (regExpression.quantifier == RegExpression::Quantifier::MoreNull) {
        if (regExpression.regExpression != NULL)
            return kleene(re_to_nfa(*regExpression.regExpression));
        NFA *new_sym = new NFA();
        new_sym->set_vertex(2);
        new_sym->set_transition(0, 1, regExpression.body);
        new_sym->set_final_state(1);
        return kleene(*new_sym);
    }
    if (regExpression.quantifier == RegExpression::Quantifier::MoreOne) {
//TODO
    }

    NFA *new_sym = new NFA();
    new_sym->set_vertex(2);
    new_sym->set_transition(0, 1, regExpression.body);
    new_sym->set_final_state(1);
    return *new_sym;
}

NFA NFA::re_to_nfa(RegExpression regExpression) {
    NFA res = re_to_nfa(regExpression.getRegExpBody().front());
    std::list<RegExpression::Item>::iterator i;
    std::list<RegExpression::Item> listy = regExpression.getRegExpBody();
    for (i = std::next(listy.begin()); i != listy.end(); ++i) {
        res = concat(res, re_to_nfa(*i));
    }
    return res;
}

NFA NFA::or_selection(std::vector <NFA> selections, int no_of_selections) {
    NFA result;
    int vertex_count = 2;
    int i, j;
    NFA med;
    trans new_trans;

    for(i = 0; i < no_of_selections; i++) {
        vertex_count += selections.at(i).get_vertex_count();
    }

    result.set_vertex(vertex_count);

    int adder_track = 1;

    for(i = 0; i < no_of_selections; i++) {
        Terminal* tr = new Terminal();
        tr->setName("^");
        result.set_transition(0, adder_track, *tr);
        med = selections.at(i);
        for(j = 0; j < med.transitions.size(); j++) {
            new_trans = med.transitions.at(j);
            result.set_transition(new_trans.vertex_from + adder_track, new_trans.vertex_to + adder_track, new_trans.trans_symbol);
        }
        adder_track += med.get_vertex_count();

        result.set_transition(adder_track - 1, vertex_count - 1, *tr);
    }

    result.set_final_state(vertex_count - 1);

    return result;
}

NFA NFA::kleene(NFA a) {
    NFA result;
    int i;
    trans new_trans;
    Terminal* tr = new Terminal();
    tr->setName("^");

    result.set_vertex(a.get_vertex_count() + 2);
    result.set_transition(0, 1, *tr);

    for(i = 0; i < a.transitions.size(); i++) {
        new_trans = a.transitions.at(i);
        result.set_transition(new_trans.vertex_from + 1, new_trans.vertex_to + 1, new_trans.trans_symbol);
    }

    result.set_transition(a.get_vertex_count(), a.get_vertex_count() + 1, *tr);
    result.set_transition(a.get_vertex_count(), 1, *tr);
    result.set_transition(0, a.get_vertex_count() + 1, *tr);

    result.set_final_state(a.get_vertex_count() + 1);

    return result;
}

NFA NFA::concat(NFA a, NFA b) {
    NFA result;
    Terminal* tr = new Terminal();
    tr->setName("^");

    result.set_vertex(a.get_vertex_count() + b.get_vertex_count());
    int i;
    trans new_trans;

    for(i = 0; i < a.transitions.size(); i++) {
        new_trans = a.transitions.at(i);
        result.set_transition(new_trans.vertex_from, new_trans.vertex_to, new_trans.trans_symbol);
    }

    result.set_transition(a.get_final_state(), a.get_vertex_count(), *tr);

    for(i = 0; i < b.transitions.size(); i++) {
        new_trans = b.transitions.at(i);
        result.set_transition(new_trans.vertex_from + a.get_vertex_count(), new_trans.vertex_to + a.get_vertex_count(), new_trans.trans_symbol);
    }

    result.set_final_state(a.get_vertex_count() + b.get_vertex_count() - 1);

    return result;
}
