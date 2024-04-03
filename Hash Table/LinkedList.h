// Purpose: Class implementation for LinkedList class.
// Created by: Mustneer Ahmad
// Created on: 2/21/2024

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

// Node class to represent each element in the linked list
class Node
{
public:
    std::string data;
    Node *next;

    Node()
    {
        data = "";
        next = nullptr;
    }

    Node(const std::string& newData)
    {
        data = newData;
        next = nullptr;
    }
};

// LinkedList class to represent the linked list
class LinkedList
{
private:
    Node *head;

public:
    // Constructor
    LinkedList()
    {
        head = nullptr;
    }

    // Insert a new node at the end of the list
    void insert(const std::string& data)
    {
        Node *newNode = new Node(data);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Print the list
    void printList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Search for a node with a given value
    Node *search(const std::string& data)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->data == data)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

#endif
