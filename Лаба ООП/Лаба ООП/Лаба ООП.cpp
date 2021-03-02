#include "bin_tree.h"

int main() {
    setlocale(LC_ALL, "Russian");

    node* root = NULL;
    size_t command_cnt = 0;
    cout << "Введите количество команд: ";
    cin >> command_cnt;

    int key;
    string command;

    for (size_t i = 0; i < command_cnt; ++i) {
        cout << "Введите команду: ";
        cin >> command;
        
        if (root == NULL) {
            if (command == "CREATE") {
                cin >> key;
                root = create(root, key);
            }
            else if (command == "READ_FROM") {
                string path;
                cin >> path;
                root = read_from(root, path);
            }
        }
        else {
            if (command == "ADD") {
                cin >> key;
                root = add(root, key);
            }
            else if (command == "DEL") {
                cin >> key;
                root = del(root, key);
            }
            else if (command == "WRITE_TO") {
                string path;
                cin >> path;
                if (!write_to(root, path)) {
                    cout << "Ошибка при чтении файла" << endl;
                }
            }
            else if (command == "SIZE") {
                cout << size(root) << endl;
            }
            else if (command == "PRINT") {
                preorder(root, cout);
                cout << endl;
            }
            else if (command == "IPRINT") {
                postorder(root, cout);
                cout << endl;
            }
            else if (command == "MAX") {
                cout << max(root)->key << endl;
            }
            else if (command == "MIN") {
                cout << min(root)->key << endl;
            }
        }

        }
        

    return 0;
}