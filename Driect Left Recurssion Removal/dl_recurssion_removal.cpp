#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

class CFG {
private:
    vector<tuple<string, vector<string>>> productions;

    void readGrammarFromFile(const string& filename) {
        ifstream file;
        string line;
        file.open(filename);

        while (!file.eof()) {
            getline(file, line);

            stringstream lineAsStream(line);

            string head;
            getline(lineAsStream, head, '=');

            vector<string> tempRules;
            string rule;
            while (getline(lineAsStream, rule, '|')) {
                tempRules.push_back(rule);
            }

            productions.push_back(make_tuple(head, tempRules));
        }
    }

    void printGrammar() {
        for (const auto& production : productions) {
            cout << get<0>(production) << "=";

            const vector<string>& rules = get<1>(production);
            for (size_t j = 0; j < rules.size(); ++j) {
                cout << rules[j];
                if (j != rules.size() - 1) {
                    cout << "|";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void removeDirectRecursion() {
        vector<tuple<string, vector<string>>> newProductions;

        for (const auto& production : productions) {
            const string& ruleName = get<0>(production);
            const vector<string>& rules = get<1>(production);

            vector<string> alphaRules;
            vector<string> betaRules;

            for (const auto& rule : rules) {
                if (ruleName[0] == rule[0]) {
                    // Current Rule has left recursion
                    alphaRules.push_back(rule.substr(1, rule.size() - 1) + ruleName + "'");
                } else {
                    betaRules.push_back(rule + ruleName + "'");
                }
            }

            newProductions.push_back(make_tuple(ruleName, betaRules));
            if (!alphaRules.empty()) {
                alphaRules.push_back("$");
                newProductions.push_back(make_tuple(ruleName + "'", alphaRules));
            }
        }

        productions = newProductions;
    }

public:
    CFG() = default;

    void processGrammar(const string& filename) {
        readGrammarFromFile(filename);
        cout << "Input Grammar: " << endl;
        printGrammar();
        removeDirectRecursion();
        cout << "Output Grammar: " << endl;
        printGrammar();
    }
};

int main() {
    string filename = "rules.txt";
    CFG grammarProcessor;
    grammarProcessor.processGrammar(filename);
    return 0;
}
