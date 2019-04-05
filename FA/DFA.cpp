//
// Created by patutinaam on 03.04.19.
//

#include "DFA.h"

DFA DFA::nfa_to_dfa(NFA nfa) {
    DFA dfa;

    const std::vector<int> start(1, 0);
    const std::vector<int> s0 = nfa.eclosure(start);

    int vertex_from = dfa.add_entry(s0);

    while (vertex_from != -1) {
        const std::vector<int> T = dfa.entry_at(vertex_from);
        dfa.mark_entry(vertex_from);

        const std::vector<Terminal> symbols = nfa.find_possible_input_symbols(T);
        for (int i = 0; i < symbols.size(); i++) {
            //TODO: add a eclosure cache : { state => eclosure }
            const std::vector<int> U = nfa.eclosure(nfa.move(T, symbols.at(i)));

            int vertex_to = dfa.find_entry(U);
            if (vertex_to == -1) { // U not already in S'
                vertex_to = dfa.add_entry(U);
            }

            dfa.set_transition(vertex_from, vertex_to, symbols.at(i));
        }

        vertex_from = dfa.next_unmarked_entry_idx();
    }

    // The finish states of the DFA are those which contain any
    // of the finish states of the NFA.
    dfa.set_final_state(nfa.get_final_state());

    return dfa;
};
