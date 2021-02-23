#include "bin_tree.h"
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    node* Tree = NULL;
    size_t command_cnt = 0;
    cout << "Введите количество команд: ";
    cin >> command_cnt;

    int key;
    string command;
    for (size_t i = 0; i < command_cnt; ++i) {

        if (i == 0) {
            cout << "Введите значение корня: ";
            cin >> key;
            Tree = create(Tree, key);
        }

        cout << "Введите команду: ";
        cin >> command;
        
        if (command == "ADD") {    
            cin >> key;
            add(Tree, key);
        }
        else if (command == "DEL") {
            cin >> key;
            del(Tree, key);
        }
        else if (command == "SIZE") {
            cout << size(Tree) << endl;
        }
        else if (command == "NEXT") {
            cin >> key;
            cout << next_to(find(Tree, key))->key << endl;
        }
        else if (command == "BACK") {
            cin >> key;
            cout << back_to(find(Tree, key))->key << endl;
        }
        else if (command == "PRINT") {
            preorder(Tree);
            cout << endl;
        }
        else if (command == "IPRINT") {
            postorder(Tree);
            cout << endl;
        }
        else if (command == "MAX") {
            cout << max(Tree)->key << endl;
        }
        else if (command == "MIN") {
            cout << min(Tree)->key << endl;
        }
    }

    return 0;
}