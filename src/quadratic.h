/*
    cppoaht_quadratic.h

    This header provides the lib's quadratic probing hash table interface.

    ------------------------------------------------------------------------------

    MIT License

    Copyright (c) 2021 Brendo Costa

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

#ifndef CPPOAHT_QUADRATIC_H
#define CPPOAHT_QUADRATIC_H

#include "types.h"
#include "entry.h"
#include "utils.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iomanip>

namespace CPPOAHT {

    template <typename key_type, typename value_type>
    class QuadHashTable {

        public:

            QuadHashTable(
                CPPOAHT::uindexmax_t (*hashFn)(key_type),
                CPPOAHT::uindexmax_t initial_size,
                bool entry_caching = true
            );

            ~QuadHashTable();

        private:

            CPPOAHT::uindexmax_t size       = 0;
            CPPOAHT::uindexmax_t keys_count = 0;
            CPPOAHT::uindexmax_t residues   = 0;

            bool entry_caching;

            CPPOAHT::uindexmax_t (*hashFunction)(key_type);

            CPPOAHT::Entry<key_type, value_type>* entries;

            void _insert(key_type key, value_type value);

            void _rehash(CPPOAHT::uindexmax_t new_size);

            void _remove(key_type key);

            void _find(key_type key);

            void _update_residues(CPPOAHT::uindexmax_t new_size);

        public:

            float loadFactor(void);

            void insert(key_type key, value_type value);

            void remove(key_type key);

            void find(key_type key);

            // Debug

            void display(void);

    };

    // -------------------------------------------------------------------------
    //                           Inits methods
    // -------------------------------------------------------------------------

    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::QuadHashTable(
        CPPOAHT::uindexmax_t (*hashFn)(key_type),
        CPPOAHT::uindexmax_t initial_size,
        bool entry_caching
    ) {

        // Prime numbers table size approach

        if (!isPrime(initial_size))

            initial_size = nextPrime(initial_size);

        // Entries's and indexes memory allocation

        this->entries = new CPPOAHT::Entry<key_type, value_type>[initial_size];

        // Table's size and residues assignments

        this->size = initial_size;
        this->_update_residues(initial_size);

        // Caching assignments

        this->entry_caching = entry_caching;

        // Hash function assignments

        this->hashFunction = hashFn;

    }

    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::~QuadHashTable() {

        for (CPPOAHT::uindexmax_t i = 0; i < this->size; i++) {

            delete this->entries[i].key;

            delete this->entries[i].value;

        }

        delete[] this->entries;

    }

    // -------------------------------------------------------------------------
    //                            Class's methods
    // -------------------------------------------------------------------------

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_insert(key_type key, value_type value) {

        CPPOAHT::uindexmax_t hashPosition = hashFunction(key);
        CPPOAHT::uindexmax_t probingPosition;

        for (CPPOAHT::uindexmax_t i = 0; i < this->residues; i++) {

            // Position probing

            probingPosition = (hashPosition + (i * i)) % this->size;

            if (this->entries[probingPosition].state == CPPOAHT::Entry<key_type, value_type>::UNALLOC
                || this->entries[probingPosition].state == CPPOAHT::Entry<key_type, value_type>::EMPTY) {

                // Key and value memory allocation if necessary

                if (this->entries[probingPosition].state == CPPOAHT::Entry<key_type, value_type>::UNALLOC) {

                    this->entries[probingPosition].key   = new key_type;
                    this->entries[probingPosition].value = new value_type;

                }

                // Key and value assignments

                *(this->entries[probingPosition].key)   = key;
                *(this->entries[probingPosition].value) = value;

                // Entry's state update

                this->entries[probingPosition].state = CPPOAHT::Entry<key_type, value_type>::FULL;

                // Table's key count update

                this->keys_count += 1;

                return;

            }

        }

        return;

    }

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_rehash(CPPOAHT::uindexmax_t new_size) {

        std::cout << "\nREHASH!" << std::endl;

        // New entries array allocation

        CPPOAHT::Entry<key_type, value_type> *newEntries;
        newEntries = new CPPOAHT::Entry<key_type, value_type>[new_size];

        // Copying

        std::copy(
            this->entries,
            this->entries + this->size,
            newEntries
        );

        // Control variables update

        this->keys_count = 0;
        this->size = new_size;
        this->_update_residues(new_size);

        this->entries = newEntries;

        for (CPPOAHT::uindexmax_t i = 0; i < this->size; i++) {

            if (this->entries[i].state
                == CPPOAHT::Entry<key_type, value_type>::FULL) {

                this->entries[i].state = CPPOAHT::Entry<key_type, value_type>::UNALLOC;

                this->_insert(*(this->entries[i].key), *(this->entries[i].value));

            }

        }

        std::cout << "\nFIM DO REHASH!" << std::endl;

    }

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_remove(key_type key) {

        CPPOAHT::uindexmax_t position = hashFunction(key);

        for (CPPOAHT::uindexmax_t i = 0; i < this->residues; i++) {

            // Position probing

            position = ( position + (i * i) ) % this->size;

            // Key and value memory deallocation

            if (this->entries[position].state == CPPOAHT::Entry<key_type, value_type>::FULL
                && *(this->entries[position].key) == key) {

                delete this->entries[position].key;
                delete this->entries[position].value;

                // Entry's state update

                this->entries[position].state = CPPOAHT::Entry<key_type, value_type>::UNALLOC;

                // Table's key count update

                this->keys_count -= 1;

                return;

            }

        }

        return;

    }

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_update_residues(CPPOAHT::uindexmax_t new_size) {

        this->residues = ( ( new_size + 1 ) / 2 );

    }

    // -------------------------------------------------------------------------
    //                             Public methods
    // -------------------------------------------------------------------------

    template <typename key_type, typename value_type>
    float QuadHashTable<key_type, value_type>::loadFactor(void) {

        return ( this->keys_count / ( (float) this->size) );

    }

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::insert(key_type key, value_type value) {

        this->_insert(key, value);

        if (this->loadFactor() > 0.5) {

            CPPOAHT::uindexmax_t new_size = nextPrime(this->size * 2);

            this->_update_residues(new_size);

            this->_rehash(new_size);


        }

        return;

    }

    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::display(void) {

        std::cout << "\nIND  STS  KEY  VAL" << std::endl;

        for (CPPOAHT::uindexmax_t i = 0; i < this->size; i++) {

            if (this->entries[i].state == CPPOAHT::Entry<key_type, value_type>::FULL) {

                std::cout << std::right << std::setw(2) << i << std::setw(4) << " " << std::left << std::setw(4) << unsigned(this->entries[i].state) << std::setw(7) << *(this->entries[i].key) << *(this->entries[i].value) << std::endl;

            } else {

                std::cout << std::right << std::setw(2) << i << std::setw(4) << " " << std::left << std::setw(4) << unsigned(this->entries[i].state) << std::setw(7) << 0 << 0 << std::endl;

            }
        }

        std::cout << "\nLOAD FACTOR: " << this->loadFactor() << std::endl;

        return;

    }

}

#endif // CPPOAHT_QUADRATIC_H