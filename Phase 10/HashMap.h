/* 
 * File:   HashMap.h
 * Author: Thomas Kleist
 *
 * Created on December 2, 2024, 11:01 PM
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <list>
#include <iterator>
#include <stdexcept>
#include <string>

// Template class for HashMap
template <typename ValueType>
class HashMap {
private:
    // Hash table with separate chaining
    std::list<std::pair<std::string, ValueType>> table[10];
    int tableSize = 10;

        // Hash function to map keys to table indices
    size_t hashFunction(const std::string& key) const {
        unsigned int b    = 378551;
        unsigned int a    = 63689;
        unsigned int hash = 0;

        for(std::size_t i = 0; i < key.length(); i++)
        {
           hash = hash * a + key[i];
           a    = a * b;
        }

        return hash % tableSize;
    }

public:
    // Constructor to initialize HashMap with a specific size
    HashMap() {
    }

    // Insert a key-value pair into the map
    void insert(const std::string& key, const ValueType& value) {
        size_t index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;  // Update existing key-value pair
                return;
            }
        }
        table[index].emplace_back(key, value);  // Insert new key-value pair
    }

    // Retrieve a value by its key
    ValueType get(const std::string& key) const {
        size_t index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("Key not found.");
    }
};

#endif /* HASHMAP_H */

