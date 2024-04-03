/* 
Purpose: This file contains the implementation of lexical analysis.
Created by: Mustneer Ahmad
Created on: 3/6/2024
*/

#include <iostream>
#include <fstream>
#include "HashTable.h"

#define BUFFER_LENGTH 4096

using namespace std;

/* Function to check if the first character of a string is valid */
bool isValidFirstChar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) &&
           c != '-' && c != '.' && c != '?' && c != '!' &&
           c != ':' && c != ';' && c != '$' && c != '&' &&
           c != '*' && c != '+';
}

// Function to check if a string is valid
bool isValidString(const char *str)
{
    while (*str != '\0')
    {
        if (*str == '-' || *str == '.' || *str == '?' || *str == '!' ||
            *str == ':' || *str == ';' || *str == '$' || *str == '&' ||
            *str == '*' || *str == '+')
        {
            return false;
        }
        ++str;
    }
    return true;
}

int main()
{
    char buff[BUFFER_LENGTH];
    HashTable hashTable;
    ifstream file;

    file.open("mycode.txt");
    if (!file.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    while (file.getline(buff, BUFFER_LENGTH))
    {
        cout << buff << endl;

        if (isValidFirstChar(buff[0]) && isValidString(buff))
        {
            cout << "Valid" << endl;

            hashTable.insert(buff);
            cout << "Added to hash table\n"
                 << endl;
        }
        else
        {
            cout << "Invalid\nSkipping...\n"
                 << endl;
        }
    }

    file.close();

    /** 
     * Adding values to hash table
    */
    cout << "Table:" << endl;
    hashTable.printTable();

    return 0;
}
