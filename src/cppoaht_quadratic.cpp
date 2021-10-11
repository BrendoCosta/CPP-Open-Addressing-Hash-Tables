/*
    cppoaht_quadratic.cpp
    
    This header provides the lib's quadratic probing hash table implementation.
    
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

#include "src/include/cppoaht_quadratic.h"

#include "src/include/cppoaht_utils.h"
#include "src/cppoaht_utils.cpp"

#include <cstdio>
#include <iostream>
#include <iomanip>

//#define qht_alias(_T) template <typename key_type, typename value_type> _T QuadHashTable<key_type, value_type>
//qht_alias(void)::insert(key_type key, value_type value) { ... }

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::QuadHashTable( uintmax_t (*hashFn)(key_type),
                                                        uintmax_t initial_size,
                                                        bool enable_key_caching,
                                                        bool enable_table_caching
                                                      ) {
        
        // Only prime numbers table size approach
        
        if (!isPrime(initial_size))
            
            initial_size = nextPrime(initial_size);
        
        // Entries's memory allocation                                                   
                                                          
        this->entries = new CPPOAHT::Entry<key_type, value_type>*[initial_size];
        
        for (uintmax_t i = 0; i < initial_size; i++) {
            
            this->entries[i] = new CPPOAHT::Entry<key_type, value_type>(enable_key_caching);
            
            this->entries[i]->set_state(CPPOAHT::Entry<key_type, value_type>::EMPTY);
            
        }
        
        // Table's size and residues assignments
        
        this->size = initial_size;
        this->_update_residues(initial_size);
        
        // Caching assignments
        
        this->key_caching = enable_key_caching;
        this->table_caching = enable_table_caching;
        
        // Hash function assignments
        
        this->hashFunction = hashFn;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    QuadHashTable<key_type, value_type>::~QuadHashTable() { 
        
        for (uintmax_t i = 0; i < size; i++) {
            
            this->entries[i]->~Entry();
            
        }
        
        delete[] this->entries;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_insert(key_type key, value_type value) { 
        
        uintmax_t position = hashFunction(key);
        
        for (uintmax_t i = 0; i < this->residues; i++) {
            
            position = ( position + (i * i) ) % this->size;
            
            if ( entries[position]->get_state() == CPPOAHT::Entry<key_type, value_type>::EMPTY ||
                 entries[position]->get_state() == CPPOAHT::Entry<key_type, value_type>::DELETED) {
                
                // Key and value assignments
                
                entries[position]->set_value(value);

                if (entries[position]->caching)
                    
                    entries[position]->set_key(key);
                
                // Entry's state update
                
                entries[position]->set_state(CPPOAHT::Entry<key_type, value_type>::FULL);
                
                // Table's key count update
                
                this->keys += 1;
                
                return;
                
            }
            
        }
        
        return;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::_update_residues(uintmax_t size) { 
        
        this->residues = ( (size + 1) / 2 );
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::insert(key_type key, value_type value) { 
        
        this->_insert(key, value);
        
        return;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::display(void) { 
        
        std::cout << "\nIND  STS  KEY  VAL" << std::endl;
        
        for (uintmax_t i = 0; i < this->size; i++) {
            
            std::cout << std::right << std::setw(2) << i << std::setw(4) << " " << std::left << std::setw(4) << entries[i]->get_state() << std::setw(7) << entries[i]->get_key() << entries[i]->get_value() << std::endl;
            
        }
        
        std::cout << "\nLOAD FACTOR: " << "ND" << std::endl;
        
        //this->_insert(key, value);
        
        return;
        
    }
    
}