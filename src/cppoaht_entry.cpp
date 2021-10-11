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
        
        if (enable_key_caching)
            
            this->caching = true;
        
        else
            
            this->caching = false;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    Entry<key_type, value_type>::~Entry() {
        
        delete this->key;
        
        delete this->value;
        
    }
    
    // Getting's functions
    
    template <typename key_type, typename value_type>
    key_type Entry<key_type, value_type>::get_key(void) { 
        
        if (this->get_state() == FULL && this->caching)
            
            return *(this->key);
            
        else
            
            return 0;
        
    }
    
    template <typename key_type, typename value_type>
    value_type Entry<key_type, value_type>::get_value(void) { 
        
        if (this->get_state() == FULL && this->caching)
            
            return *(this->value);
            
        else
            
            return 0;
        
    }
    
    template <typename key_type, typename value_type>
    uint8_t Entry<key_type, value_type>::get_state(void) { 
        
        return this->state;
        
    }
    
    // Setting's functions
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_key(key_type new_key) { 
        
        // We are going to store the key only if the key caching is enabled
        
        if (this->caching) {
            
            // Memory allocation for key's value if necessary
            
            if (this->state == EMPTY) this->key = new key_type;
            
            // Update entry's key value
        
            *(this->key) = new_key;
            
        }
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_value(value_type new_value) { 
        
        // Memory allocation for value if necessary
        
        if (this->state == EMPTY) this->value = new value_type;
        
        // Update entry's value
        
        *(this->value) = new_value;
        
    }
    
    /* --- */
    
    template <typename key_type, typename value_type>
    void Entry<key_type, value_type>::set_state(uint8_t new_state) { 
        
        this->state = new_state;
        
    }
    
    /* --- */
    
}