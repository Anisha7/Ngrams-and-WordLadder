// Arshin Jain (arshin@stanford) and Anisha Jain (Anishax@Stanford)

// Notes:
// Checks for enter key press: input.empty()

// Sys libs
#include <iostream>
#include <typeinfo>

// Stanford C++ Lib
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "map.h"
#include "vector.h"

using namespace std;

// Main Function
int main() {

    // -- Properties --
    string input = ""; // fileName
    string n = ""; // value of N
    string temp = "";
    int num = 1;
    ifstream stream;
      openFile(stream);

    // -- Intro --
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << "" << endl; // Empty line

    // --- One time Inputs --

    // File Input
    cout << "Input file name? " << endl;
    input = getLine();

    // Value of n
    cout << "Value of n? " << endl;
    n = getLine();

    if (!stringIsInteger(n)) {
        n = stringToInteger(temp);
    }

    // Pressing '0' exits program
    while (num != 0) {

        cout << "# of random words to generate (0 to quit)?" << endl;
        temp = getLine();

        if (!stringIsInteger(n)) {
            n = stringToInteger(temp);
        }

    }

    cout << "Exiting." << endl;

    return 0;
}

void openFile(ifstream &stream)
{
    string fileName;
    while(true)
    {
        fileName = getLine("Enter input file name: ");
        stream.open(fileName.c_str());
        if(stream.fail())
        {
            stream.clear();
            cout<<"Unable to open file named "<<'\"'<<fileName<<'\"'<<". Try again."<<endl;
        } else break;
    }
}

//Reads text and put strings and vextors in map.
void readText(ifstream &stream, int markov, Map<string, Vector<char>> &all)
{
    char c;
    string word;
    while(stream.get(c))
    {
        word += c;
        if(word.length()==markov)
        {
            stream.get(c);
            char v = c;
            stream.putback(c);
            if(!all.containsKey(word))
            {
                Vector<char> value;
                value.add(v);
                all.put(word, value);
            } else
            {
                Vector<char> value = all.get(word);
                value.add(v);
                all.put(word, value);
            }
            word = word.substr(1);
        }
    }
}
