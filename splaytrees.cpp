#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

class SplayTreeNode {
public:
    string key;
    int frequency;
    SplayTreeNode* left;
    SplayTreeNode* right;
    SplayTreeNode(string key) {
        this->key = key;
        frequency = 1;
        left = nullptr;
        right = nullptr;
    }
};

class SplayTree {
private:
    SplayTreeNode* root;

    SplayTreeNode* zigRotation(SplayTreeNode* node) {
        SplayTreeNode* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    SplayTreeNode* zagRotation(SplayTreeNode* node) {
        SplayTreeNode* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    SplayTreeNode* splay(SplayTreeNode* root, string key) {
        if (root == nullptr || root->key == key)
            return root;

        // Key lies in left subtree
        if (key < root->key) {
            if (root->left == nullptr)
                return root;
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = zigRotation(root);
            }
            else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = zagRotation(root->left);
            }
            if (root->left == nullptr)
                return root;
            else
                return zigRotation(root);
        }
        else {
            if (root->right == nullptr)
                return root;
            if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = zigRotation(root->right);
            }
            else if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = zagRotation(root);
            }
            if (root->right == nullptr)
                return root;
            else
                return zagRotation(root);
        }
    }

    SplayTreeNode* insert(SplayTreeNode* root, string key) {
        if (root == nullptr)
            return new SplayTreeNode(key);

        root = splay(root, key);

        if (root->key == key) {
            root->frequency++;
            return root;
        }

        SplayTreeNode* newNode = new SplayTreeNode(key);
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
            }
else {
newNode->left = root;
newNode->right = root->right;
root->right = nullptr;
}
    return newNode;
}

int search(SplayTreeNode* root, string key) {
    if (root == nullptr)
        return 0;

    root = splay(root, key);

    if (root->key == key)
        return root->frequency;
    else
        return 0;
}
public:
SplayTree() {
root = nullptr;
}
void insert(string key) {
    root = insert(root, key);
}

int search(string key) {
    return search(root, key);
}
};

int main() {
SplayTree splayTree;
string filename;
cout << "Enter the name of the input text file: ";
cin >> filename;

ifstream inputFile(filename);
if (!inputFile.is_open()) {
    cout << "Failed to open input file." << endl;
    return 0;
}

// Tokenize input text file into words and insert into splay tree
string line;
while (getline(inputFile, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
        // Remove punctuations and delimiters from the word
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        splayTree.insert(word);
    }
}

inputFile.close();

string searchWord;
cout << "Enter the word to search for: ";
cin >> searchWord;
transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
int frequency = splayTree.search(searchWord);
if (frequency > 0)
    cout << "Frequency of occurrence of \"" << searchWord << "\" in the text file: " << frequency << endl;
else
    cout << "Word \"" << searchWord << "\" not found in the text file." << endl;

return 0;
}
