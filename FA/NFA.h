//
// Created by patutinaam on 03.04.19.
//

#ifndef LAB1_NKA_H
#define LAB1_NKA_H

#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "trans.h"
#include "../regexp/RegExpression.h"

class NFA {
public:
    std::vector<int> vertex;
    std::vector <trans> transitions;
    int final_state;

    NFA() {

    }

    int get_vertex_count() {
        return vertex.size();
    }

    void set_vertex(int no_vertex) {
        for (int i = 0; i < no_vertex; i++) {
            vertex.push_back(i);
        }
    }

    void set_transition(int vertex_from, int vertex_to, Terminal trans_symbol) {
        trans new_trans;
        new_trans.vertex_from = vertex_from;
        new_trans.vertex_to = vertex_to;
        new_trans.trans_symbol = trans_symbol;
        transitions.push_back(new_trans);
    }

    void set_final_state(int fs) {
        final_state = fs;
    }

    int get_final_state() {
        return final_state;
    }

    void display() {
        trans new_trans;
        std::cout << "\n";
        for (int i = 0; i < transitions.size(); i++) {
            new_trans = transitions.at(i);
            std::cout << "q" << new_trans.vertex_from << " -> q" << new_trans.vertex_to << " : Symbol - "
                 << new_trans.trans_symbol.getName() << std::endl;
        }
        std::cout << "\nThe final state is q" << get_final_state() << std::endl;
    }

    /**
     * Get the set of reachable state from each specified vertex.
     */
    std::vector<Terminal> find_possible_input_symbols(const std::vector<int> &vertexs) {
        std::vector<Terminal> result;

        for (int i = 0; i < vertexs.size(); i++) {
            int vertex_from = vertexs.at(i);
            for (int j = 0; j < transitions.size(); j++) {
                trans it = transitions.at(j);
                if (it.vertex_from == vertex_from && it.trans_symbol.getName() != "^") {
                    result.push_back(it.trans_symbol);
                }
            }
        }

        return result;
    }

    std::vector<int> eclosure(const std::vector<int> &X) {
        std::vector<int> result;
        std::vector<bool> visited(get_vertex_count(), false);

        for (int i = 0; i < X.size(); i++) {
            eclosure(X.at(i), result, visited);
        }

        sort(result.begin(), result.end());
        std::unique(result.begin(), result.end());
        std::cout << "eclosure{" << join(X, ",") << "}  ->  " << join(result, ",") << std::endl;
        return result;
    }

    void eclosure(int x, std::vector<int> &result, std::vector<bool> &visited) {
        result.push_back(x);

        for (int i = 0; i < transitions.size(); i++) {
            trans it = transitions.at(i);
            if (it.vertex_from == x && it.trans_symbol.getName() == "^") {
                int y = it.vertex_to;
                if (!visited.at(y)) {
                    visited.at(y) = true;
                    eclosure(y, result, visited);
                }
            }
        }
    }

    std::vector<int> move(const std::vector<int> &T, const Terminal trans_symbol) {
        std::vector<int> result;

        for (int j = 0; j < T.size(); j++) {
            int t = T.at(j);

            for (int i = 0; i < transitions.size(); i++) {
                trans it = transitions.at(i);
                if (it.vertex_from == t && it.trans_symbol.getName() == trans_symbol.getName()) {
                    result.push_back(it.vertex_to);
                }
            }
        }

        std::sort(result.begin(), result.end());

        int l1 = result.size();
        std::unique(result.begin(), result.end());
        int l2 = result.size();
        if (l2 < l1) {
            std::cerr << "move(T, a) return non-unique vector" << std::endl;
            exit(1);
        }

        return result;
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

    NFA concat(NFA a, NFA b);

    NFA kleene(NFA a);

    NFA or_selection(std::vector <NFA> selections, int no_of_selections);

    NFA re_to_nfa(RegExpression::Item regExpression);

    NFA re_to_nfa(RegExpression rg);

};

#endif //LAB1_NKA_H
