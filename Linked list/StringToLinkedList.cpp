#include <iostream>
#include <string>

using namespace std;

struct Node
{
    string data;
    Node* next;
};

void insert(Node* head, string data){
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;

    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head){
    Node* temp = head;
    while(temp->next != NULL){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << temp->data << endl;
}

int main(){

    string message;
    
    Node* head = new Node();

    cout << "Enter a string: ";
    getline(cin, message);

    int position = 0;

    for(int i = 0; i < message.length(); i++){
        if(message[i] == ' '){
            string word = message.substr(position, i - position);
            insert(head, word);
            position = i + 1;
        }
    }
    string lastWord = message.substr(position);
    insert(head, lastWord);

    printList(head);

    return 0;
}