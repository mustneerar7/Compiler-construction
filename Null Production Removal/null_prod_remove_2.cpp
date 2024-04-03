#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <tuple>

using namespace std;

class Grammar
{
private:
    struct ProductionRule
    {
        string head;
        list<string> rules;
    };

    list<ProductionRule> productions;
    list<string> alreadyRemoved;

public:
    Grammar() {}

    void LoadFromFile(const string &filename)
    {
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            stringstream lineAsStream(line);
            string head;
            getline(lineAsStream, head, '=');

            ProductionRule pr;
            pr.head = head;

            string rule;
            while (getline(lineAsStream, rule, '|'))
            {
                pr.rules.push_back(rule);
            }

            productions.push_back(pr);
        }
        file.close();
    }

    void PrintGrammar()
    {
        for (const auto &production : productions)
        {
            cout << production.head << "=";
            const list<string> &rules = production.rules;
            for (auto it = rules.begin(); it != rules.end(); ++it)
            {
                cout << *it;
                if (next(it) != rules.end())
                {
                    cout << "|";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void RemoveNullProds()
    {
        bool foundNull = true;
        while (foundNull)
        {
            foundNull = false;
            for (auto it = productions.begin(); it != productions.end(); ++it)
            {
                const string &ruleName = it->head;
                list<string> &rules = it->rules;

                bool alreadyRemovedNull = (find(alreadyRemoved.begin(), alreadyRemoved.end(), ruleName) != alreadyRemoved.end());

                for (auto ruleIt = rules.begin(); ruleIt != rules.end(); ++ruleIt)
                {
                    if (*ruleIt == "$")
                    {
                        if (alreadyRemovedNull)
                        {
                            ruleIt = rules.erase(ruleIt);
                            if (ruleIt == rules.end())
                                break;
                            continue;
                        }

                        foundNull = true;
                        alreadyRemoved.push_back(ruleName);
                        string nullRuleName = ruleName;

                        for (auto &production : productions)
                        {
                            list<string> &rulesForNull = production.rules;
                            for (auto ruleForNullIt = rulesForNull.begin(); ruleForNullIt != rulesForNull.end(); ++ruleForNullIt)
                            {
                                string newRule = "";
                                string currentRule = *ruleForNullIt;

                                bool removed = false;

                                if (currentRule == nullRuleName && *ruleForNullIt != "$")
                                {
                                    rulesForNull.push_back("$");
                                }
                                else
                                {
                                    for (size_t m = 0; m < currentRule.size(); ++m)
                                    {
                                        if (currentRule[m] != nullRuleName[0])
                                        {
                                            newRule += currentRule[m];
                                        }
                                        if (currentRule[m] == nullRuleName[0])
                                        {
                                            removed = true;
                                        }
                                    }

                                    if (removed)
                                    {
                                        bool alreadyHasRule = (find(rulesForNull.begin(), rulesForNull.end(), newRule) != rulesForNull.end());
                                        if (!alreadyHasRule)
                                        {
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

int main()
{
    string filename = "test.txt";
    Grammar grammar;
    grammar.LoadFromFile(filename);

    cout << "Input Grammar:" << endl;
    grammar.PrintGrammar();

    grammar.RemoveNullProds();

    cout << "Output Grammar:" << endl;
    grammar.PrintGrammar();

    return 0;
}
