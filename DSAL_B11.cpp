#include <iostream>
#include <string>
using namespace std;

class node {
   public:
    string key, value;
    node *left, *right;
    node() {
        key = "";
        value = "";
        left = NULL;
        right = NULL;
    }
    node(string key, string value) {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

class bst {
   public:
    node *root;
    bst(){
         root = NULL;
    }
    bst(string key, string value) { 
        root = new node(key, value); 
    }

    bool insert(string, string);
    string search(string);
    bool update(string, string);
    bool delete_key(string);
    void display(node *cur);
    
};
bool bst::insert(string key, string value) {
    if (root == NULL) {
        root = new node(key, value);
        return 1;
    }

    node *temp, *prev;
    prev = root;
    temp = root;
    while (temp != NULL) {
        prev = temp;
        if (temp->key == key) {
            return 0;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    if (prev->key < key) {
        prev->right = new node(key, value);
    } else {
        prev->left = new node(key, value);
    }
    return 1;
}

string bst::search(string key) {
    node *temp = root;
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return "\0"; 
}

bool bst::update(string key, string value) {
    node *temp;
    temp = root;
    while (temp != NULL) {
        if (temp->key == key) {
            temp->value = value;
            return 1;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return 0;
}

bool bst::delete_key(string key) {
    node **cur = &root;
    while (*cur != nullptr) {
        if ((*cur)->key == key) {
            node *temp = *cur;
            if (temp->left == nullptr)
                *cur = temp->right;
            else if (temp->right == nullptr)
                *cur = temp->left;
            else {
                node *successor = temp->right;
                while (successor->left != nullptr)
                    successor = successor->left;
                temp->key = successor->key;
                temp->value = successor->value;
                cur = &temp->right;
                key = successor->key;
                continue;
            }
            delete temp;
            return true;
        } else if ((*cur)->key < key)
            cur = &((*cur)->right);
        else
            cur = &((*cur)->left);
    }
    return false;
}

void bst::display(node *cur) {
    if (cur == NULL) {
        return;
    }
    display(cur->left);
    cout << cur->key << " : " << cur->value << endl;
    display(cur->right);
}

int main() {
    bst tree;
    int ch;
    string k, v, ans;
    do {
        cout << "--- MAIN MENU ---" << endl;
        cout << "1 -> Insert" << endl;
        cout << "2 -> Search" << endl;
        cout << "3 -> Update" << endl;
        cout << "4 -> Delete" << endl;
        cout << "5 -> Display Ascending" << endl;
        cout << "0 -> Exit" << endl;
        cout << "Choose an option (0-5):\t";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Key (word) to insert:\t";
                cin >> k;
                cout << "Value (meaning):\t";
                cin >> v;
                if (tree.insert(k, v)) {
                    cout << "Element insertion successful." << endl;
                } else {
                    cout << "Element already exists." << endl;
                }
                break;
            case 2:
                cout << "Key (word) to search:\t";
                cin >> k;
                ans = tree.search(k);
                if (ans == "\0") {
                    cout << "Element does not exist." << endl;
                } else {
                    cout << "Value (meaning) is:\t" << ans << endl;
                }
                break;
            case 3:
                cout << "Key (word) to update:\t";
                cin >> k;
                cout << "New value (meaning):\t";
                cin >> v;
                if (tree.update(k, v)) {
                    cout << "Element updated." << endl;
                } else {
                    cout << "Element does not exist." << endl;
                }
                break;
            case 4:
                cout << "Key (word) to delete:\t";
                cin >> k;
                if (tree.delete_key(k)) {
                    cout << "Element deletion successful." << endl;
                } else {
                    cout << "Element does not exist." << endl;
                }
                break;
            case 5:
                cout << "Data in ascending order:\t" << endl;
                tree.display(tree.root);
                break;
            case 0:
                cout << "\n// END OF CODE\n";
                break;
            default:
                cout << "Please choose a valid option (0-5)." << endl;
                break;
        }
    } while (ch != 0);
    return 0;
}
