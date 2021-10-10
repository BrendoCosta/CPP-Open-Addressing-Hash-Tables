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

#include "src/include/cppoaht_types.h"
#include "src/include/cppoaht_entry.h"

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    class QuadHashTable {
        
        private:
            
            uintmax_t _size;
            uintmax_t _keys;
            uintmax_t _residues;
            
            CPPOAHT::Types::default_int_type (*_hashFunction)(key_type, value_type);
            
            CPPOAHT::Entry<key_type, value_type>** _entries;
            
            void _insert(key_type key, value_type value);
            
            void _rehash(key_type key, value_type value);
            
            void _remove(key_type key);
            
            void _find(key_type key);

        public:
            
            template <typename hash_function_type>
            QuadHashTable(  hash_function_type (*hashFn)(key_type, value_type),
                            uintmax_t initial_size,
                            bool enable_key_caching = true,
                            bool enable_table_caching = true
                         );
                         
            ~QuadHashTable();
            
            template <typename hash_function_type>
            void setHashFuncTypeFunction(hash_function_type (*hashFn)(key_type, value_type));
            
            void insert(key_type key, value_type value);
            
            void remove(key_type key);
            
            void find(key_type key);
            
            value_type iterate(void);
            
    };

}

#endif // CPPOAHT_QUADRATIC_H