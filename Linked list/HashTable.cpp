#include <iostream>
#include <string>

using namespace std;

struct Node
{
    string data;
    Node* next;
};

int hashFunction(string key){
    return key[0] % 26;
}

void insert(Node* hashTable[], string data){
    int key = hashFunction(data);

    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;

    if(hashTable[key] == NULL){
        hashTable[key] = newNode;
    } else {
        Node* temp = hashTable[key];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printHashTable(Node* hashTable[]){
    for(int i = 0; i < 26; i++){
        Node* temp = hashTable[i];
        cout << i << " -> ";
        while(temp != NULL){
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

int main(){

    string message;
    
    Node* hashTable[26];
    for(int i = 0; i < 26; i++){
        hashTable[i] = NULL;
    }

    cout << "Enter a string: ";
    getline(cin, message);

    int position = 0;

    for(int i = 0; i < message.length(); i++){
        if(message[i] == ' '){
            string word = message.substr(position, i - position);
            insert(hashTable, word);
            position = i + 1;
        }
    }
    string lastWord = message.substr(position);
    insert(hashTable, lastWord);

    printHashTable(hashTable);

    return 0;
}
