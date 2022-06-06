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

#include "hashtable.hpp"
#include "types.hpp"
#include "entry.hpp"
#include "query.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>

namespace CPPOAHT {

    template <typename key_type, typename value_type>
    class QuadHashTable : public HashTable <key_type, value_type> {

        public:

            QuadHashTable(
                CPPOAHT::index_t (*hashFn)(key_type),
                CPPOAHT::index_t initial_size,
                bool entry_caching = true
            );

            ~QuadHashTable();

        private:

            CPPOAHT::index_t keysCount = 0;
            CPPOAHT::index_t (*qht_hashFunction)(key_type);
            
            std::vector< CPPOAHT::Entry<key_type, value_type> > entries;

            CPPOAHT::index_t qht_probe(
                CPPOAHT::index_t inputPosition, 
                CPPOAHT::index_t iteration
            );
            CPPOAHT::Query<key_type, value_type> qht_insert(key_type key, value_type value);
            void qht_rehash(CPPOAHT::index_t new_size);
            CPPOAHT::Query<key_type, value_type> qht_remove(key_type key);
            CPPOAHT::Query<key_type, value_type> qht_find(key_type key);

            bool qht_entryCache;

        public:

            CPPOAHT::index_t getSize(void);
            CPPOAHT::index_t getKeysCount(void);
            CPPOAHT::float_t getLoadFactor(void);
            CPPOAHT::index_t getResidues(void);

            void insert(key_type key, value_type value);
            void remove(key_type key);
            value_type find(key_type key);

            // Debug

            void display(void);

    };

    // -------------------------------------------------------------------------
    //                           Inits methods
    // -------------------------------------------------------------------------

    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::QuadHashTable(
        CPPOAHT::index_t (*arg_hashFunction)(key_type),
        CPPOAHT::index_t arg_initialSize,
        bool arg_enableEntryCache
    ) {

        if (!CPPOAHT::Utils::isPrime(arg_initialSize))
            arg_initialSize = CPPOAHT::Utils::getNextPrime(arg_initialSize);
        
        this->entries.resize(arg_initialSize);
        this->qht_entryCache = arg_enableEntryCache;
        this->qht_hashFunction = arg_hashFunction;

    }

    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::~QuadHashTable() {

        for (CPPOAHT::index_t i = 0; i < this->getSize(); i++) {

            this->entries[i].dealloc();

        }

        //delete[] this->entries;

    }

    // -------------------------------------------------------------------------
    //                            Public methods
    // -------------------------------------------------------------------------

    #define QHTFN(...) template <typename key_type, typename value_type> __VA_ARGS__ QuadHashTable<key_type, value_type>

    QHTFN(CPPOAHT::index_t)::getSize(void) {

        return this->entries.capacity();

    }

    QHTFN(CPPOAHT::index_t)::getKeysCount(void) {

        return this->keysCount;

    }

    QHTFN(CPPOAHT::float_t)::getLoadFactor(void) {

        return ( this->getKeysCount() / ( (float) this->getSize() ) );

    }

    QHTFN(CPPOAHT::index_t)::getResidues(void) {

        return ( ( this->getSize() + 1 ) / 2 );

    }

    // -------------------------------------------------------------------------
    //                           Private methods
    // -------------------------------------------------------------------------

    /* @author  Brendo Costa <brendocosta@id.uff.br>;
     * @date    2022-04-21
     * @desc    Calculates a quadratic probing position 
                from an input position according to an input 
                iteration number; */

    QHTFN(CPPOAHT::index_t)::qht_probe(CPPOAHT::index_t inputPosition, CPPOAHT::index_t iteration) {

        return ( inputPosition + (iteration * iteration) ) % this->getSize();

    }

    QHTFN(CPPOAHT::Query<key_type, value_type>)::qht_insert(key_type key, value_type value) {

        CPPOAHT::index_t hashPosition    = this->qht_hashFunction(key);
        CPPOAHT::index_t probingPosition = 0;
        CPPOAHT::Query<key_type, value_type> returnQuery;

        for (CPPOAHT::index_t i = 0; i < this->getResidues(); i++) {

            // Position probing

            probingPosition = this->qht_probe(hashPosition, i);

            if (this->entries[probingPosition].isUnallocated()
                || this->entries[probingPosition].isEmpty()) {

                // Key and value memory allocation if necessary

                if (this->entries[probingPosition].isUnallocated()) {

                    this->entries[probingPosition].alloc();

                }

                this->entries[probingPosition].assign(key, value);
                returnQuery.assignStop(probingPosition, i);
                break;

            }

        }

        return returnQuery;

    }

    /* @author  Brendo Costa <brendocosta@id.uff.br>;
     * @date    2022-02-24
     * @desc    Allocates a new entries' array with a given
                size, copy all current array's entries to it
                and reorganize them;
     * @todo    Move the array's memory allocation code
                to a separated boolean method. */

    QHTFN(void)::qht_rehash(CPPOAHT::index_t new_size) {

        /* Allocates a new entries' array following
         * the prime number table's size approach. */

        new_size = CPPOAHT::Utils::getNextPrime(new_size);
        this->entries.resize(new_size);

        /* Finally reorganize all entries to match the
         * new residues / avaliable probing positions of
         * the new table's size */

        for (CPPOAHT::index_t i = 0; i < this->getSize(); i++) {

            if (this->entries[i].isFull()) {

                key_type key = this->entries[i].getKey();
                value_type value = this->entries[i].getValue();
                this->entries[i].dealloc();
                this->qht_insert(key, value);

            }

        }

        return;

    }

    QHTFN(CPPOAHT::Query<key_type, value_type>)::qht_remove(key_type key) {

        CPPOAHT::index_t hashPosition    = this->qht_hashFunction(key);
        CPPOAHT::index_t probingPosition = 0;
        CPPOAHT::Query<key_type, value_type> returnQuery;

        for (CPPOAHT::index_t i = 0; i < this->getResidues(); i++) {

            // Position probing
            probingPosition = this->qht_probe(hashPosition, i);

            if (this->entries[probingPosition].isFull()
                && this->entries[probingPosition].getKey() == key) {

                returnQuery.assignStop(probingPosition, i);
                returnQuery.assignQueryEntry(
                    this->entries[probingPosition].getKey(), 
                    this->entries[probingPosition].getValue()
                );

                // Key and value memory deallocation
                this->entries[probingPosition].dealloc();

                break;

            }

        }

        return returnQuery;

    }

    QHTFN(CPPOAHT::Query<key_type, value_type>)::qht_find(key_type key) {

        CPPOAHT::index_t hashPosition     = this->qht_hashFunction(key);
        CPPOAHT::index_t probingPosition  = 0;
        CPPOAHT::Query<key_type, value_type> returnQuery;
        
        for (CPPOAHT::index_t i = 0; i < this->getResidues(); i++) {

            // Position probing
            probingPosition = this->qht_probe(hashPosition, i);

            if (this->entries[probingPosition].isFull()
                && this->entries[probingPosition].getKey() == key) {

                returnQuery.assignStop(probingPosition, i);

            }

        }

        return returnQuery;

    }

    // -------------------------------------------------------------------------
    //                             Public methods
    // -------------------------------------------------------------------------

    QHTFN(void)::insert(key_type key, value_type value) {

        CPPOAHT::Query<key_type, value_type> query = this->qht_insert(key, value);

        if (query.isValid()) {

            // Update keys' count

            this->keysCount++;

            // Rehash if necessary

            if (this->getLoadFactor() > 0.5) this->qht_rehash(this->getSize() * 2);

        }

        return;

    }

    QHTFN(void)::remove(key_type key) {

        CPPOAHT::Query<key_type, value_type> query = this->qht_remove(key);

        if (query.isValid()) {

            // Update keys' count

            this->keysCount--;

        } else {

            // TODO: error handling

        }

        return;

    }

    QHTFN(value_type)::find(key_type key) {

        CPPOAHT::Query<key_type, value_type> query = this->qht_find(key);

        if (query.isValid()) {
            
            return this->entries[query.getReturnedIndex()].getValue();

        } else {

            // TODO: error handling
            return (value_type) 0;

        }

    }

    QHTFN(void)::display(void) {

        std::cout << "\nIND  STS  KEY  VAL" << std::endl;

        for (CPPOAHT::index_t i = 0; i < this->getSize(); i++) {

            if (this->entries[i].state == CPPOAHT::Entry<key_type, value_type>::FULL) {

                std::cout << std::right << std::setw(2) << i << std::setw(4) << " " << std::left << std::setw(4) << unsigned(this->entries[i].state) << std::setw(7) << *(this->entries[i].key) << *(this->entries[i].value) << std::endl;

            } else {

                std::cout << std::right << std::setw(2) << i << std::setw(4) << " " << std::left << std::setw(4) << unsigned(this->entries[i].state) << std::setw(7) << 0 << "--" << std::endl;

            }
        }

        std::cout << "\nLOAD FACTOR: " << this->getLoadFactor() << std::endl;

        return;

    }

}

#endif // CPPOAHT_QUADRATIC_H
