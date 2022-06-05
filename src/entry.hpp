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

#include "entry.hpp"
#include "types.hpp"

namespace CPPOAHT {

    template <typename key_type, typename value_type>
    class Entry {

        public:

            // Destructor's methods

            ~Entry();

            // Entry's possible states

            enum {

                FULL    = 2,
                EMPTY   = 1,
                UNALLOC = 0

            };

            // Entry's data

            key_type*   key;
            value_type* value;
            uint8_t     state = UNALLOC;

            // Get methods

            bool isFull(void);
            bool isEmpty(void);
            bool isUnallocated(void);
            key_type getKey(void);
            value_type getValue(void);

            // Set methods

            void alloc(void);
            void dealloc(void);

            bool assign(key_type key, value_type value);

    };

    /* ---------------------------------------------------------------------- */

    #define ENTFN(_RETURNTYPE) template <typename key_type, typename value_type> _RETURNTYPE Entry<key_type, value_type>

    template <typename key_type, typename value_type>
    Entry<key_type, value_type>::~Entry() {

        //this->dealloc();

    }

    // Get methos

    ENTFN(bool)::isFull(void) {

        if (this->state == FULL) {

            return true;

        } else { return false; }

    }

    ENTFN(bool)::isEmpty(void) {

        if (this->state == EMPTY) {

            return true;

        } else { return false; }

    }

    ENTFN(bool)::isUnallocated(void) {

        if (this->state == UNALLOC) {

            return true;

        } else { return false; }

    }

    ENTFN(key_type)::getKey(void) {

        if (this->state == FULL) {

            return *(this->key);

        } else {

            return (key_type) 0;

        }

    }

    ENTFN(value_type)::getValue(void) {

        if (this->state == FULL) {

            return *(this->value);

        } else {

            return (value_type) 0;

        }

    }

    // Set methos

    ENTFN(void)::alloc(void) {

        if (this->state == UNALLOC) {

            this->key   = new key_type;
            this->value = new value_type;

            this->state = EMPTY;

        }

    }

    ENTFN(void)::dealloc(void) {

        if (this->state != UNALLOC) {

            delete this->key;
            delete this->value;

            this->state = UNALLOC;

        }

    }

    ENTFN(bool)::assign(key_type key, value_type value) {

        if (this->state != UNALLOC) {

            // Key and value assignments

            *(this->key)   = key;
            *(this->value) = value;

            // Entry's state update

            this->state = FULL;

            // Sucess

            return true;

        } else {

            // Fail
            std::cout << "\nDEBUG: ENTRY NO ALLOC" << std::endl;
            return false;

        }

    }

}

#endif // CPPOAHT_ENTRY_H
