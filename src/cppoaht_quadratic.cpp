/*
    cppoaht_quadratic.cpp
    
    * This header provides the lib's quadratic probing hash table implementation.
    
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

#include <cstdio>
#include <iostream>
#include "src/include/cppoaht_quadratic.h"

//#define qht_alias(_T) template <typename key_type, typename value_type> _T QuadHashTable<key_type, value_type>
//qht_alias(void)::insert(key_type key, value_type value) { ... }

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    template <typename hash_function_type>
    QuadHashTable<key_type, value_type>::QuadHashTable(hash_function_type (*hashFn)(key_type, value_type), int initialSize) {
        
        // TODO
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::tableInsert(key_type key, value_type value) { 
        
        return;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void QuadHashTable<key_type, value_type>::insert(key_type key, value_type value) { 
        
        return;
        
    }
    
    /* --- */
    
}