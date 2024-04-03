#include <LinkedList.h>

int main() {
    string message;
    LinkedList list;

    cout << "Enter a string: ";
    getline(cin, message);

    int position = 0;

    for (int i = 0; i < message.length(); i++) {
        if (message[i] == ' ') {
            string word = message.substr(position, i - position);
            list.insert(word);
            position = i + 1;
        }
    }
    string lastWord = message.substr(position);
    list.insert(lastWord);

    list.printList();

    return 0;
}