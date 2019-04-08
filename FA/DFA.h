//
// Created by patutinaam on 03.04.19.
//

#ifndef LAB1_DFA_H
#define LAB1_DFA_H


#include <vector>
#include <iostream>
#include "trans.h"
#include "NFA.h"

class DFA {
public:

    std::vector<trans> transitions;
    std::vector<std::vector<int> > entries;
    std::vector<bool> marked;
    std::vector<int> final_states;

    int add_entry(std::vector<int> entry) {
        entries.push_back(entry);
        marked.push_back(false);
        return entries.size() - 1;
    }

    int next_unmarked_entry_idx() {
        for (int i = 0; i < marked.size(); i++) {
            if (!marked.at(i)) {
                return i;
            }
        }

        return -1;
    }

    void mark_entry(int idx) {
        marked.at(idx) = true;
    }

    std::vector<int> entry_at(int i) {
        return entries.at(i);
    }

    int find_entry(std::vector<int> entry) {
        for (int i = 0; i < entries.size(); i++) {
            std::vector<int> it = entries.at(i);
            if (it == entry) {
                return i;
            }
        }

        return -1;
    }

    void set_final_state(int nfa_fs) {
        for (int i = 0; i < entries.size(); i++) {
            std::vector<int> entry = entries.at(i);

            for (int j = 0; j < entry.size(); j++) {
                int vertex = entry.at(j);
                if (vertex == nfa_fs) {
                    final_states.push_back(i);
                }
            }
        }

    }

    std::string join(std::vector<int> v, std::string delim) {
        std::stringstream ss;
        for(int i = 0; i < v.size(); ++i) {
            if(i != 0)
                ss << ",";
            ss << v[i];
        }
        return ss.str();
    }

    void set_transition(int vertex_from, int vertex_to, Terminal trans_symbol) {
        trans new_trans;
        new_trans.vertex_from = vertex_from;
        new_trans.vertex_to = vertex_to;
        new_trans.trans_symbol = trans_symbol;
        transitions.push_back(new_trans);
    }


    void display() {
        trans new_trans;
        std::cout << "\n";
        for (int i = 0; i < transitions.size(); i++) {
            new_trans = transitions.at(i);
            std::cout << "q" << new_trans.vertex_from << " " << join(entries.at(new_trans.vertex_from), ",")
                      << ") -> q" << new_trans.vertex_to << " (" << join(entries.at(new_trans.vertex_to), ",")
                      << ") [label=" << new_trans.trans_symbol.getName() << "]" <<std::endl;
        }
        std::cout << "\nThe final state is q : " << join(final_states, ",") << std::endl;
    }

    void write_to_file(std::string name="DFA.txt") {
        std::ofstream stream;
        stream.open (name);
        trans new_trans;
        stream << "digraph G {";
        for (int i = 0; i < transitions.size(); i++) {
            new_trans = transitions.at(i);
            stream << "<q" << new_trans.vertex_from << " (" << join(entries.at(new_trans.vertex_from), ",")
                      << ")> -> <q" << new_trans.vertex_to << " (" << join(entries.at(new_trans.vertex_to), ",")
                      << ")> [label=<" << new_trans.trans_symbol.getName() << ">]" <<std::endl;
        }
        stream << "}";
        stream.close();
    }

    DFA nfa_to_dfa(NFA nfa);

};


#endif //LAB1_DFA_H
