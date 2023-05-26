#pragma once
#include <iostream>
template <typename Key, typename Value>
class HashTable
{
    class Node
    {
    public:
        Key key;
        Value value;
        std::unique_ptr<Node> next;
    };

    rsize_t m_size;
    Node** m_table;

    rsize_t HashFunction(const Key& key) const { return std::hash<Key>()(key) % m_size; }

public:
    HashTable(size_t size = 10) : m_size{size}, m_table{new Node* [size] {}} {}

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    ~HashTable()
    {
        Clear();
        delete[] m_table;
    }

    void Clear()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            while (m_table[i] != nullptr)
            {
                std::unique_ptr<Node> tmp(std::move(m_table[i]->next));
                delete m_table[i];
                m_table[i] = tmp.release();
            }
        }
    }

    void Insert(const Key& key, const Value& value)
    {
        size_t index = HashFunction(key);

        Node*& node = m_table[index];

        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->value = value;
                return;
            }
            node = node->next.get();

        }
        node = new Node{key, value, std::unique_ptr<Node>(nullptr)};
    }

    Value& Search(const Key& key) {

        size_t index = HashFunction(key);

        Node* node = m_table[index];

        while (node != nullptr)
        {
            if (node->key == key)
            {
                return node->value;            
            }
            node = node->next.get();
        }

        throw std::out_of_range("Key wasn`t found int hash table");
    }

    bool Remove(const Key& key) {


        size_t index = HashFunction(key);

        Node*& node = m_table[index];

        if (node == nullptr)
        {
            return false;
        }

        if (node->key == key)
        {

            std::unique_ptr<Node> temp(std::move(node->next));

            delete node;

            node = temp.release();
            return true;

        }

        Node* prev = node;
        Node* cur = node->next.get();

        while (node != nullptr)
        {
            
            if (cur->key == key)
            {
                std::unique_ptr<Node> temp(std::move(cur->next));
                prev->next = std::move(temp);

                delete cur;

                return true;
            }

        }

        return false;
    }
};
