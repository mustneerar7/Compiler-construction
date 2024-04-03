// Description: Hash table using Class Implementation
// Created by: Mustneer Ahmad
// Created on: 2/21/2024

#include "HashTable.h"

int main()
{
    HashTable hashTable;

    // Insert some values into the hash table
    hashTable.insert("Never");
    hashTable.insert("Gonna");
    hashTable.insert("Give");
    hashTable.insert("You");
    hashTable.insert("Up");

    // Print the hash table
    hashTable.printTable();

    // Find the node by value
    Node *node = hashTable.search("Give");
    std::cout << node->data << std::endl;

    return 0;
}