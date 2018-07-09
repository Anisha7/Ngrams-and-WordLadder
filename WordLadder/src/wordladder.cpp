// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include "console.h"
#include "stack.h"
#include <fstream> // standard library pkg for files
#include "filelib.h" // contains helpful methods

using namespace std;
void ladder(string file, string word1, string word2) {
    // queue of stacks, initially containing stack with word1
    Queue<Stack> Q;
    Stack<string> S;
    S.push(word1);
    Q.enqueue(S);

    // track if w2 is found
    bool found = false;

    // set up for file open
    ifstream stream(file);
    string w;
    // test if file is opened
    if (!stream) {
        cout << "Unable to open that file.  Try again." << endl;
    }


    while (!Q.isEmpty() | found == true) {
        // get each word from the dictionary
        while(!stream.eof()) {
            w = stream >> w;

            string stackword;

            if (isNeighbor(stackword, content)) {
                // create a new stack s2 whose contents are the same as s,
                // but with w added on top, and add s2 to the queue.
            }

            if (content == word2) {
                // print stack
                found = true;
            }
        }
    }

    return;
}

void exit(){
    cout << "Have a nice day.";
    return;
}

bool valid(string word, string file){
    ifstream stream(file);
    string content;
    // test if file is opened
    if (!stream) {
        cout << "Unable to open that file.  Try again." << endl;
    }

    if (word == "Enter" | word == "enter") {
        return true;
    }

    while(!stream.eof()) {
        content = stream >> content;
        if (word == content) {
            return true;
        }
    }

    // close stream
    stream.close();
    return false;
}

string prompt1(){
    string word1;
    // ask for word one
    cout << "Word 1 (or Enter to quit): ";
    cin >> word1;
    return word1;
}

string prompt2(){
    string word2;
    // ask for word two
    cout << "Word 2 (or Enter to quit): ";
    cin >> word2;
    return word2;

}

void run(string file){

    string word1;
    string word2;
    bool quit = false;
    bool valid1;
    bool valid2;

    while (!quit) {
        cout << "" << endl;

        // reprompt if invalid word
        valid1 = false;
        while (!valid1 & !quit) {
            word1 = prompt1();
            valid1 = valid(word1, file);
        }
        // if quit
        if (word1 == "Enter" | word1 == "enter") {
            quit = true;
        }

        // reprompt if invalid word
        valid2 = false;
        while (!valid2 & !quit) {
            word2 = prompt2();
            valid2 = valid(word2, file);
        }

        // if quit
        if (word2 == "Enter" | word2 == "enter") {
            quit = true;
        }

        // else
        cout << "A ladder from data back to code:" << endl;
        ladder(file, word1, word2);
    }
    exit();
    return;

}


int main() {
    // TODO: Finish the program!

    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl;
    cout << "" << endl;

    // ask for dictionary file name
    string file;
    cout << "Dictionary file name: ";
    cin >> file;

    run(file);

    return 0;
}
