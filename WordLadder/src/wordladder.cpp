// Anisha Jain (anishax) and Arshin Jain (arshinx)

#include <iostream>
#include "console.h"
#include "stack.h"
#include "queue.h"
#include <fstream> // standard library pkg for files
#include "filelib.h" // contains helpful methods
#include "strlib.h"
#include "simpio.h"

using namespace std;

bool inDict(string word, string file) {
    ifstream stream(file);
    string content;
    // test if file is opened
    if (!stream) {
        cout << "Unable to open that file.  Try again." << endl;
    }

    while(!stream.eof()) {
        stream >> content;
        if (word == content) {
            return true;
        }
    }
    // close stream
    stream.close();
    return false;
}

// checks if the word is valid
bool valid(string word1, string word2, string file){

    if (word1 == word2) {
        cout << "The two words must be different." << endl;
        return false;
    }

    if (word1.length() != word2.length()) {
        cout << "The two words must be the same length." << endl;
        return false;
    }

    if (!inDict(word1, file) | !inDict(word2, file)) {
        cout << "The two words must be found in the dictionary" << endl;
        return false;
    }


    return true;
}

// copies a stack, non-destructively
Stack<string> copy(Stack<string> S) {
    Stack<string> temp;
    Stack<string> res;

    // copied in reverse order in temp
    while (!S.isEmpty()) {
        temp.push(S.pop());
    }

    // copied in right order back in S and res
    while (!temp.isEmpty()) {
        string t = temp.pop();
        S.push(t);
        res.push(t);
    }

    return res;
}

// copies a stack, destructively
void copyS(Stack<string> S, Stack<string> res) {
    Stack<string> temp;

    // copied in reverse order in temp
    while (!S.isEmpty()) {
        temp.push(S.pop());
    }

    // copied in right order back in S and res
    while (!temp.isEmpty()) {
        string t = S.pop();
        S.push(t);
        res.push(t);
    }

    return;
}

// check if words differ by one letter
bool diffbyone(string stackword, string w) {
    int n = stackword.length();
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (w[i] != stackword[i]) {
            count += 1;
        }
        if (count > 1) {
            return false;
        }
    }

    if (count == 1) {
        return true;
    }

    return false;
}

// checks if the words are neighbors
bool isNeighbor(string stackword, string w, string file) {
    if (stackword.length() != w.length()) {
        //cout << "length unequal" << endl;
        return false;
    }

    if (!diffbyone(stackword, w)) {
        //cout << "not diff by one " << endl;
        return false;
    }

    if (!inDict(w, file)) {
        //cout << "invalid" << endl;
        return false;
    }

    return true;
}
// gets neighbors of a word
Stack<string> getNeighbors(string file, string word, string goal) {
    Stack<string> res;

    int strlen = word.length();

    for (int i = 0; i < strlen; i++) {
        for (int j = 0; j < strlen; j++) {
            string n;
            n = word.substr(0, i) + goal[j] + word.substr(i + 1,strlen-1);

            // check if its a neighbor & in dictionary
            if (isNeighbor(word, n, file)) {
                res.push(n);
            }
        }
    }

    return res;
}

// gets neighbors of a word
Stack<string> getNeighbors1(string file, string word) {
    Stack<string> res;

    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int strlen = word.length();

    for (int i = 0; i < strlen; i++) {
        for (int j = 0; j < 26; j++) {
            string n;
            n = word.substr(0, i) + alpha[j] + word.substr(i + 1,strlen-1);

            // check if its a neighbor & in dictionary
            if (isNeighbor(word, n, file)) {
                res.push(n);
            }
        }
    }

    return res;
}

bool findInStack(Stack<string> seen, string w) {
    Stack<string> cp = copy(seen);

    while(!cp.isEmpty()) {

        if (cp.pop() == w) {
            return true;
        }
    }
    return false;
}

// prints a stack
void printstack(Stack<string> S) {
    Stack<string> cp = copy(S);
    while (!cp.isEmpty()) {
        cout << cp.pop() << " ";
    }
    cout << endl;
    return;
}

Stack<string> stackRev(Stack<string> S) {
    Stack<string> rev;
    Stack<string> temp;

    while (!S.isEmpty()) {
        string t = S.pop();
        rev.push(t);
        temp.push(t);
    }

    while (!temp.isEmpty()) {
        S.push(temp.pop());
    }

    return rev;
}

// gets path from word1 to word 2
void ladder(string file, string word1, string word2) {
    // stack S containing word1
    // cout << "in ladder" << endl;
    Stack<string> S;
    S.push(word1);

    // queue containting stack S
    Queue<Stack<string>> Q;
    Q.enqueue(S);

    bool found = false;
    Stack<string> seen;

    // Q is not empty and word is not found
    while ((!Q.isEmpty()) & (!found)) {
        // gets all valid neighbors of word1
        //cout << "in outer while loop" << endl;

        // get word from stack
        Stack<string> s2 = Q.dequeue();
        string w = s2.pop();
        s2.push(w);

        //cout << "w: " << w << endl;

        Stack<string> neighbors = getNeighbors(file, w, word2);

        while ((!neighbors.isEmpty()) & (!found)) {
            neighbors = stackRev(neighbors);
            string nb = neighbors.pop();

            if (!findInStack(seen, nb)) {
                // debugging
                //cout << "neighbor: " << nb << endl;
                s2.push(nb);
                Q.enqueue(s2);
                // debugging
                //cout << "added s2 to queue Q" << endl;
            }

            if (nb == word2) {
                found = true;
            }
            seen.push(nb);
        }
        seen.push(w);
        //cout << "exit inner while loop" << endl;
    }
    //cout << "exit outer while loop" << endl;

    if (found) {
        // print path
        Stack<string> pstack = Q.dequeue();
        while (!Q.isEmpty()) {
            pstack = Q.dequeue();
        }
        printstack(pstack);
    }

    return;
}


void exit(){
    cout << "Have a nice day.";
    return;
}

// TO DO: add getline such that if user presses enter, if word1.empty() gives true
// else, it should give false and exit out of the function
// exit part is already written (just needs to work with run while loop)
string prompt1(){
    string word1;
    // ask for word one
    cout << "Word 1 (or Enter to quit): ";
    //word1 = getLine();
    //getLine(word1);
    cin >> word1;
    return word1;
}

// TO DO: add getline such that if user presses enter, if word2.empty() gives true
// else, it should give false and exit out of the function
// exit part is already written (just needs to work with run while loop)
string prompt2(){
    string word2;
    // ask for word two
    cout << "Word 2 (or Enter to quit): ";
    //word2 = getLine();

    cin >> word2;
    return word2;

}


void run(string file) {
    string word1 = "a";
    string word2 = "a";
    bool quit = false;

    while (quit != true) {
        bool validCheck = false;
        while (validCheck != true) {
            //cout << "Valid check " << endl;
            word1 = prompt1();

            // if quit
            if (word1.empty()) {
                quit = true;
                validCheck = true;
                break;
            }

            word2 = prompt2();
            // if quit
            if (word2.empty()) {
                quit = true;
                validCheck = true;
                break;
            }

            if (valid(word1, word2, file)) {
                validCheck = true;
            }

        }

        if (quit != true) {
            cout << "A ladder from data back to code:" << endl;
            ladder(file, word1, word2);
            cout << endl;
        }

    }
    exit();

    return;
}



bool validfile(string file) {
    bool res;
    ifstream boom(file);

    if (!boom) {
        res = false;
    } else {
        res = true;
    }
    boom.close();
    return res;
}

int main() {
    // TODO: Finish the program!

    cout << "Welcome to CS 106B/X Word Ladder!" <<  endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl;
    cout << "" << endl;

    string file;
    // ask for dictionary file name
    cout << "Dictionary file name: ";
    cin >> file;
    cout << endl;

    bool isValidFile = validfile(file);

    while (!isValidFile) {
        cout << "Unable to open that file.  Try again." << endl;
        cout << "Dictionary file name: ";
        cin >> file;
        cout << file;
        isValidFile = validfile(file);
    }

    run(file);

    return 0;
}
