/*
    cppoaht_entry.h
    
    TODO
    
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

#ifndef CPPOAHT_ENTRY_H
#define CPPOAHT_ENTRY_H

#include "src/include/cppoaht_types.h"

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    class Entry {
        
        public:
            
            enum { FULL = 2, EMPTY = 1, DELETED = 0 };
            
            key_type* key;
            value_type* value;
            uint8_t state = EMPTY;
            bool caching;
            
            // Getting's functions
            
            key_type get_key(void);
            value_type get_value(void);
            uint8_t get_state(void);
            
            // Setting's functions
            
            void set_key(key_type new_key);
            void set_value(value_type new_value);
            void set_state(uint8_t new_state);
            
            // Constructor and Destructor methods
            
            Entry(bool enable_key_caching = true);
            
            ~Entry();
    };

}

#endif // CPPOAHT_ENTRY_H