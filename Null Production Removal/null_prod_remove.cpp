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
    vector<string> alreadyRemoved;

public:
    CFG() {}

    void readGrammar(const string& filename) {
        ifstream file(filename);
        string line;
        
        while (getline(file, line)) {
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
        file.close();
    }

    void printGrammar() {
        for (const auto& production : productions) {
            cout << get<0>(production) << "=";
            
            // Accessing the vector of rules
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

    void removeNull() {
        bool foundNull = true;
        while (foundNull) {
            foundNull = false;
            for (int i = productions.size() - 1; i >= 0; --i) {
                const string& ruleName = get<0>(productions[i]);

                // Accessing the vector of rules
                vector<string>& rules = get<1>(productions[i]);

                bool alreadyRemovedNull = (
                    find(alreadyRemoved.begin(), alreadyRemoved.end(), ruleName) != alreadyRemoved.end()
                );

                for (size_t j = 0; j < rules.size(); ++j) {
                    if (rules[j] == "$") {
                
                        if (alreadyRemovedNull) {
                            rules.erase(rules.begin() + j);
                            continue;
                        }

                        foundNull = true;
                        alreadyRemoved.push_back(ruleName);
                        string nullRuleName = ruleName;

                        for (auto& production : productions) {
                            vector<string>& rulesForNull = get<1>(production);
                            for (size_t k = 0; k < rulesForNull.size(); ++k) {
                                string newRule = "";
                                string currentRule = rulesForNull[k];

                                bool removed = false;

                                if (currentRule == nullRuleName && rulesForNull[k] != "$") {
                                    rulesForNull.push_back("$");
                                }
                                else {
                                    for (size_t m = 0; m < currentRule.size(); ++m) {
                                        if (currentRule[m] != nullRuleName[0]) {
                                            newRule += currentRule[m];
                                        }
                                        if (currentRule[m] == nullRuleName[0]) {
                                            removed = true;
                                        }
                                    }

                                    if (removed) {
                                        bool alreadyHasRule = (find(rulesForNull.begin(), rulesForNull.end(), newRule) != rulesForNull.end());
                                        if (!alreadyHasRule) {
                                            rulesForNull.push_back(newRule);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

int main() {
    string filename = "test.txt";
    CFG grammar;
    grammar.readGrammar(filename);

    cout << "Input CFG:" << endl;
    grammar.printGrammar();

    grammar.removeNull();

    cout << "Output CFG:" << endl;
    grammar.printGrammar();

    return 0;
}
