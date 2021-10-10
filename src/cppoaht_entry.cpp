/*
    cppoaht_entry.cpp
    
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

#include "src/include/cppoaht_types.h"
#include "src/include/cppoaht_entry.h"

namespace CPPOAHT {
    
    template <typename key_type, typename value_type>
    Entry<key_type, value_type>::Entry(bool enable_key_caching) {
        
        if (enable_key_caching) {
            
            _caching = true;
            
        } else {
            
            _caching = false;
            
        }
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    Entry<key_type, value_type>::~Entry() {
        
        delete _key;
        
        delete _value;
        
    }
    
    // Getting's functions
    
    template <typename key_type, typename value_type>
    key_type Entry<key_type, value_type>::get_key(void) { 
        
        if (_caching) {
            
            return *_key;
            
        } else {
            
            // TODO
            
        }
        
    }
    
    template <typename key_type, typename value_type>
    value_type Entry<key_type, value_type>::get_value(void) { 
        
        return *_value;
        
    }
    
    template <typename key_type, typename value_type>
    uint8_t Entry<key_type, value_type>::get_state(void) { 
        
        return _state;
        
    }
    
    // Setting's functions
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_key(key_type new_key) { 
        
        // We are going to store the key only if the key caching is enabled
        
        if (_caching) {
            
            // Memory allocation for key's value if necessary
            
            if (_state == EMPTY) _key = new key_type;
            
            // Update entry's key value
        
            *_key = new_key;
            
        }
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_value(value_type new_value) { 
        
        // Memory allocation for value if necessary
        
        if (_state == EMPTY) _value = new value_type;
        
        // Update entry's value
        
        *_value = new_value;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_state(uint8_t new_state) { 
        
        _state = new_state;
        
    }
    
    /* --- */
    
}