//
// Created by Max Bryam on 28/05/2023.
//

#ifndef BLOCKCHAINUTEC_MENU_H
#define BLOCKCHAINUTEC_MENU_H

# include <iostream>
# include <conio.h>
# include "index.h"

using namespace std;

template <typename T>
class Menu
{
public:
    static Menu* init(Blockchain<T>& chain);
    void display_main();

private:
    inline static Menu* menu = nullptr;
    inline static Blockchain<T>* chain;
    inline static Index<T>* index;

    Menu() = default;
    struct Messi {
        static void display();
    };

    // Menus secundarios :p
    void display_create();
    void display_update();
    void display_delete();
    void display_request();

    // Menus de busqueda :p
    void display_search();
    void display_max();
    void display_min();

    void pause();
};



template <typename T>
Menu<T>* Menu<T>::init(Blockchain<T>& Chain)
{
    if (menu == nullptr) {
        menu = new Menu();
        chain = &Chain;
        index = Chain.index;
    }
    return menu;
}

//Consola del Menu

template <typename T>
void Menu<T>::display_main()
{
    cout << "---------------------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗∗∗∗ Welcome to MessiCoin ∗∗∗∗∗∗∗∗∗∗∗∗\n";
    cout << "---------------------------------------------\n";
    Messi::display();
    cout << "1) Create transfer. 💰\n";
    cout << "2) Update transfer. 🖊️\n";
    cout << "3) Remove transfer. 🧶\n";
    cout << "4) Request data. 📊\n";
    cout << "5) Sign out. ❌\n";

    short option;
    do {
        cout << "Enter an option: ";
        cin >> option;
    } while ( 1 > option or option > 5);

    cout << "\n";

    switch (option)
    {
        case 1:
            display_create();
            break;
        case 2:
            display_update();
            break;
        case 3:
            display_delete();
            break;
        case 4:
            display_request();
            break;
        case 5:
            cout << "Thank you for your preference!\n";
            break;
    }
}

//"CRUD"
template <typename T>
void Menu<T>::display_create()
{
    string sender;
    string receiver;
    double amount;

    cout << "Amount: ";
    cin >> amount;
    cout << "Sender: ";
    cin >> sender;
    cout << "Receiver: ";
    cin >> receiver;

    // Validar datos
    chain->insert(T{amount, sender, receiver});
    DataManager::simulate("assets/10000_transfers.csv", *chain);

    pause();
    display_main();
}

template <typename T>
void Menu<T>::display_update()
{
    int id_block;
    int id_transaction;
    cout << "Id block: ";
    cin >> id_block;
    cout << "Id transaction: ";
    cin >> id_transaction;

    string sender;
    string receiver;
    double amount;
    cout << "New amount: ";
    cin >> amount;
    cout << "New sender: ";
    cin >> sender;
    cout << "New receiver: ";
    cin >> receiver;

    chain->update(T{amount, sender, receiver}, id_block, id_transaction);

    pause();
    display_main();
}

template <typename T>
void Menu<T>::display_delete()
{
    int id_block;
    int id_transaction;
    cout << "Id block: ";
    cin >> id_block;
    cout << "Id transaction: ";
    cin >> id_transaction;

    chain->remove(id_block, id_transaction);

    pause();
    display_main();
}

template <typename T>
void Menu<T>::display_request()
{
    cout << "--------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗ Request data ∗∗∗∗∗∗∗∗∗\n";
    cout << "--------------------------------\n";
    cout << "1) Search [...]\n";
    cout << "2) Max value [...]\n";
    cout << "3) Min value [...]\n";
    cout << "4) Go back to main menu ⬅️\n";

    short option;
    do {
        cout << "Enter an option: ";
        cin >> option;
    } while ( 1 > option or option > 4);

    switch (option)
    {
        case 1:
            display_search();
            break;
        case 2:
            display_max();
            break;
        case 3:
            display_min();
            break;
        case 4:
            display_main();
            break;
    }
}


// Busquedas

template <typename T>
void Menu<T>::display_search()
{
    string name;
    Member member;
    short option;

    cout << "1) Sender\n";
    cout << "2) Receiver\n";
    cout << "Member: ";
    cin >> option;
    member = option == 1 ? Member::sender : Member::receiver;
    cout << "Name: ";
    cin >> name;
    cout << "\n";

    T* transfer = index->search(member, name);
    if (transfer != nullptr) {
        cout << "Id block: " << transfer->id_block << "\n";
        cout << *transfer << "\n";
    } else {
        cout << "Key not found.\n";
    }

    pause();
    display_request();
}

template <typename T>
void Menu<T>::display_max()
{
    T* transfer = index->max_value();

    cout << "Id block: " << transfer->id_block << "\n";
    cout << *transfer << "\n";

    pause();
    display_request();
}

template <typename T>
void Menu<T>::display_min()
{
    T* transfer = index->min_value();

    cout << "Id block: " << transfer->id_block << "\n";
    cout << *transfer << "\n";

    pause();
    display_request();
}

template <typename T>
void Menu<T>::pause()
{
    cout << "Press Enter to continue...";
    getch();
    cout << "\n\n";
}

template <typename T>
void Menu<T>::Messi::display()
{
    cout << "MESSI COIN \n";
;
}


#endif //BLOCKCHAINUTEC_MENU_H
