#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define BUFFER_LENGTH 4096
#define ROWS 12
#define COLUMNS 6

enum COL
{
    D = 0,
    DOT,
    A,
    R,
    T,
    INVALID
}; // Update enum for the new transition table

class Buffer
{
public:
    char buff1[BUFFER_LENGTH];
    char buff2[BUFFER_LENGTH];
    char *currentBuffer = buff1;

    int currentChar = 0;
    bool retracting = false;
    char prevCharacter;

    ifstream file;

    Buffer(string fileName)
    {
        file.open(fileName);
        readInBuffer();
    }

    void readInBuffer()
    {
        switchBuffer();
        file.read(currentBuffer, BUFFER_LENGTH);
        if (file.eof() && file.gcount() < BUFFER_LENGTH)
        {
            currentBuffer[file.gcount()] = '\0';
        }
    }

    void switchBuffer()
    {
        currentBuffer = currentBuffer == buff1 ? buff2 : buff1;
        currentChar = 0;
    }

    char getCharFromBuffer()
    {
        if (currentChar == BUFFER_LENGTH)
        {
            readInBuffer();
        }

        if (retracting)
        {
            retracting = false;
            return prevCharacter;
        }

        char returnChar = currentBuffer[currentChar];
        prevCharacter = returnChar;

        currentChar++;
        if (returnChar == '\0')
        {
            return EOF;
        }
        else
        {
            return returnChar;
        }
    }

    void retract()
    {
        retracting = true;
    }

    ~Buffer()
    {
        file.close();
    }
};

void generateToken(char tokenArr[], string type)
{
    string token = "<" + string(tokenArr) + ", " + type + ">";
    cout << token << endl;
}

// Modify getLetter function to getCharacter to handle digits and dots
COL getCharacter(char character)
{
    if (isdigit(character))
    {
        return D;
    }
    else if (character == '.')
    {
        return DOT;
    }
    else
    {
        return INVALID;
    }
}

int main()
{
    // Define the transition table
    string TT[ROWS][COLUMNS] = {
        {"1", "0", "1", "0", "0", "0"},
        {"2", "4", "1", "4", "0", "0"},
        {"3", "4", "1", "4", "0", "0"},
        {"0", "4", "1", "4", "0", "0"},
        {"5", "-1", "1", "-1", "0", "0"},
        {"6", "8", "1", "8", "0", "0"},
        {"7", "8", "1", "8", "0", "0"},
        {"8", "8", "1", "8", "0", "0"},
        {"9", "-1", "1", "-1", "0", "0"},
        {"10", "12", "1", "12", "0", "0"},
        {"11", "12", "1", "12", "0", "0"},
        {"12", "-1", "1", "-1", "0", "0"}};

    int state = 0, li = 0;
    char lex[1024];

    Buffer buff = Buffer("code.txt");
    char character;

    while ((character = buff.getCharFromBuffer()) != EOF)
    {

        // Get the column based on the input character
        COL column = getCharacter(character);

        // Transition to the next state based on the current state and input character
        state = stoi(TT[state][column]);

        // Handle the retract state if necessary
        if (stoi(TT[state][R]))
        {
            lex[li - 1] = '\0';
            buff.retract();
        }

        // If the current state is an accepting state, generate token and reset state
        if (stoi(TT[state][A]))
        {
            lex[li] = '\0';
            li = 0;
            generateToken(lex, TT[state][T]);
            state = 0;
        }

        // If the current state is invalid, break the loop
        if (stoi(TT[state][INVALID]))
        {
            cout << "Invalid input detected." << endl;
            break;
        }

        // Store the input character in the lexeme
        if (column != DOT)
        { // Skip storing the dot in the lexeme
            lex[li++] = character;
        }
    }
}
