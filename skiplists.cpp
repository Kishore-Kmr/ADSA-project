#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

class Node {
public:
    string word;
    Node** next;
    Node(string word, int level) {
        this->word = word;
        next = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            next[i] = nullptr;
        }
    }
};

class SkipList {
private:
    int max_level;
    float p;
    int level;
    Node* header;

public:
    SkipList(int max_level, float p) {
        this->max_level = max_level;
        this->p = p;
        level = 0;
        header = new Node("", max_level);
    }

    int random_level() {
        float r = (float)rand() / RAND_MAX;
        int lvl = 0;
        while (r < p && lvl < max_level) {
            lvl++;
            r = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    void insert(string word) {
        Node* update[max_level + 1];
        Node* x = header;
        for (int i = level; i >= 0; i--) {
            while (x->next[i] != nullptr && x->next[i]->word < word) {
                x = x->next[i];
            }
            update[i] = x;
        }
        x = x->next[0];
        if (x == nullptr || x->word != word) {
            int lvl = random_level();
            if (lvl > level) {
                for (int i = level + 1; i <= lvl; i++) {
                    update[i] = header;
                }
                level = lvl;
            }
            x = new Node(word, lvl);
            for (int i = 0; i <= lvl; i++) {
                x->next[i] = update[i]->next[i];
                update[i]->next[i] = x;
            }
        }
    }

    bool search(string word) {
        Node* x = header;
        for (int i = level; i >= 0; i--) {
            while (x->next[i] != nullptr && x->next[i]->word < word) {
                x = x->next[i];
            }
        }
        x = x->next[0];
        return (x != nullptr && x->word == word);
    }
};

int main() {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return 0;
    }

    SkipList skipList(16, 0.5);

    string word;
    while (file >> word) {
        skipList.insert(word);
    }

    file.close();

    cout << "Enter the word to search: ";
    cin >> word;

    if (skipList.search(word)) {
        cout << "Word found." << endl;
    } else {
        cout << "Word not found." << endl;
}

return 0;
}
//In this code, we create a skip list data structure to store the words from the input text file. The `insert` function is used to insert words into the skip list, and the `search` function is used to search for a word in the skip list. The skip list is implemented with a randomized height for each node, and the maximum height is determined by the `max_level` parameter. The probability `p` is used to control the height of each node, and it determines the trade-off between space and search time. In this example, we use a maximum level of 16 and a probability of 0.5, but you can adjust these values based on your specific use case.

