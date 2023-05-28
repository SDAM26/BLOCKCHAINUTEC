# ifndef INDEX_H
# define INDEX_H

# include <iostream>
# include "src/Blockchain.hpp"
# include "structures/chainhash.h"
# include "structures/b+tree.h"
# include "structures/trie.h"
# include "structures/forwardlist.h"

using namespace std;

enum class Member { sender, receiver };

template <typename T>
class Index
{
    public:
        void create_index(Block<T>* block);
        void remove_index(Block<T>* block);
        void create_index(T* transfer);
        void remove_index(T* transfer);

        T* search(Member member, string key);
        T* max_value();
        T* min_value();

        Index() = default;
        ~Index() = default;

    private:
        BPlusTree<double, T*> amount_index;
        ChainHash<string, T*> sender_index, receiver_index;
        Trie<T*> prefix_sender_index, prefix_receiver_index;
        ForwardList<pair<string, T*>> senders, receivers;
        bool boyer_moore(string text, string pattern);
};

template <typename T>
void Index<T>::create_index(Block<T>* block)
{
    T* pointer;
    for (int i = 0; i < block->size(); ++i) {
        pointer = &block->data[i];
        create_index(pointer);
    }
}

template <typename T>
void Index<T>::remove_index(Block<T>* block)
{
    T* pointer;

    for (int i = 0; i < block->size(); ++i) 
    {
        pointer = &block->data[i];
        remove_index(pointer);
    }
}

template <typename T>
void Index<T>::create_index(T* transfer)
{
    string sender = transfer->get_sender();
    string receiver = transfer->get_receiver();
    double amount = transfer->get_amount();

    // Hash index
    sender_index.insert(sender, transfer);
    receiver_index.insert(receiver, transfer);
    // B+ tree index
    amount_index.insert(amount, transfer);
    // Prefix tree index
    prefix_sender_index.insert(sender, transfer);
    prefix_receiver_index.insert(receiver, transfer);
    // For pattern searching
    senders.push_back({sender, transfer});
    receivers.push_back({receiver, transfer});
}

template <typename T>
void Index<T>::remove_index(T* transfer)
{
    string sender = transfer->get_sender();
    string receiver = transfer->get_receiver();
    double amount = transfer->get_amount();

    // Hash index
    sender_index.remove(sender);
    receiver_index.remove(receiver);
    // B+ tree index
    amount_index.remove(amount);
    // Prefix tree index
    prefix_sender_index.remove(sender);
    prefix_receiver_index.remove(receiver);
    // For pattern searching
    for (int i = 0; i < senders.size(); ++i) {
        auto [name, pointer] = senders[i];
        if (name == sender) {
            senders.remove(i);
            break;
        }
    }
    for (int i = 0; i < receivers.size(); ++i) {
        auto [name, pointer] = receivers[i];
        if (name == receiver) {
            receivers.remove(i);
            break;
        }
    }
}

template <typename T>
T* Index<T>::search(Member member, string key)
{
    return member == Member::sender ? sender_index.find(key) : receiver_index.find(key);
}

template <typename T>
T* Index<T>::max_value()
{
    return amount_index.max();
}

template <typename T>
T* Index<T>::min_value()
{
    return amount_index.min();
}

# endif // INDEX_H