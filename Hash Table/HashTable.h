// Purpose: This file contains the declaration of the HashTable class.
// Created by: Mustneer Ahmad
// Created on: 2/21/2024

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include <string>

class HashTable
{
private:
    LinkedList hashTable[10];

    // Hash function which takes in a string
    // cobines asci values of each character 
    // and returns the sum mod 10
    int hashFunction(const std::string &data)
    {
        int sum = 0;
        for (char c : data)
        {
            sum += c;
        }
        return sum % 10;
    }

public:
    // Insert a new node at hashed index
    void insert(const std::string &data)
    {
        hashTable[hashFunction(data)].insert(data);
    }

    // Print the hash table
    void printTable()
    {
        for (int i = 0; i < 10; i++)
        {
            std::cout << "[" << i << "]: ";
            hashTable[i].printList();
        }
    }

    // Search for a node with the given data
    Node *search(const std::string &data)
    {
        return hashTable[hashFunction(data)].search(data);
    }
};

#endif