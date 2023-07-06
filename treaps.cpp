#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

struct TreapNode {
    string key;
    int priority;
    int frequency; 
    TreapNode* left;
    TreapNode* right;
};

TreapNode* createNode(string key) {
    TreapNode* newNode = new TreapNode();
    newNode->key = key;
    newNode->priority = rand();
    newNode->frequency = 1;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->left;
    TreapNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->right;
    TreapNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

TreapNode* insert(TreapNode* root, string key) {
    if (root == nullptr) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);

        if (root->left->priority > root->priority) {
            root = rotateRight(root);
        }
    } else if (key > root->key) {
        root->right = insert(root->right, key);

        if (root->right->priority > root->priority) {
            root = rotateLeft(root);
        }
    } else {
        // If the word is already present, increment the frequency
        root->frequency++;
    }

    return root;
}

int search(TreapNode* root, string key) {
    if (root == nullptr) {
        return 0;
    }

    if (key < root->key) {
        return search(root->left, key);
    } else if (key > root->key) {
        return search(root->right, key);
    } else {
        return root->frequency;
    }
}

string removePunctuations(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += tolower(s[i]);
        }
    }
    return result;
}

int main() {
    // Seed the random number generator for Treap's priorities
    srand(time(0));

    string filename;
    cout << "Enter the name of the text file: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
cout << "Failed to open the file!" << endl;
return 1;
}
// Create an empty Treap
TreapNode* root = nullptr;

string line;
while (getline(file, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
        word = removePunctuations(word);

        if (!word.empty()) {
            root = insert(root, word);
        }
    }
}

file.close();

string searchWord;
cout << "Enter a word to search for: ";
cin >> searchWord;

searchWord = removePunctuations(searchWord);

int frequency = search(root, searchWord);
cout << "Frequency of occurrence of \"" << searchWord << "\": " << frequency << endl;
return 0;
}

/*This code assumes that the text file contains only space-separated words, and it removes all punctuations and delimiters from the words before inserting them into the Treap.*/