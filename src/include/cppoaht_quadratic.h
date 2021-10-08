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

#ifndef CPPOAHT_QUADRATIC
#define CPPOAHT_QUADRATIC

#include "src/include/cppoaht_types.h"

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    class QuadHashTable {
        
        private:
            
            enum { FULL = 1, EMPTY = 0, DELETED = -1 };
            
            CPPOAHT::Types::int_type size;
            CPPOAHT::Types::int_type keys;
            CPPOAHT::Types::int_type residues;
            
            int (*hashFunction)(key_type, value_type);
            
            //Entry <key_type, value_type> *entries;
            
            void tableInsert(key_type key, value_type value);
            
            void tableRehash(key_type key, value_type value);
            
            void tableRemove(key_type key);
            
            void tableFind(key_type key);

        public:
            
            template <typename hash_function_type>
            QuadHashTable(hash_function_type (*hashFn)(key_type, value_type), int initialSize);
            
            template <typename hash_function_type>
            void setHashFuncTypeFunction(hash_function_type (*hashFn)(key_type, value_type));
            
            void insert(key_type key, value_type value);
            
            void remove(key_type key);
            
            void find(key_type key);
            
            value_type iterate(void);
            
    };

}

#endif // CPPOAHT_QUADRATIC