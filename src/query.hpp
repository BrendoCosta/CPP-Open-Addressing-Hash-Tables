/*
    index.hpp

    TODO.

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

#ifndef CPPOAHT_INDEX_H
#define CPPOAHT_INDEX_H

#include <chrono>
#include "types.hpp"
#include "entry.hpp"

namespace CPPOAHT {

    template <typename key_type, typename value_type>
    class Query {

        private:

            enum QueryState {

                QUERY_STATE_STOPPED,
                QUERY_STATE_RUNNING,
                QUERY_STATE_FINISHED

            };

            QueryState state = QUERY_STATE_STOPPED;
            CPPOAHT::Entry<key_type, value_type> storedEntry;
            CPPOAHT::index_t index = 0;
            CPPOAHT::index_t iterationsCount = 0;
            std::chrono::time_point<std::chrono::steady_clock> startTime;
            std::chrono::time_point<std::chrono::steady_clock> endTime;

        public:

            Query();
            ~Query();

            bool isValid(void);
            bool assignStart(void);
            bool assignStop(CPPOAHT::index_t finalIndex, CPPOAHT::index_t finalIteration);
            void assignQueryEntry(key_type key, value_type value);
            CPPOAHT::Entry<key_type, value_type> getQueryEntry(void);
            CPPOAHT::float_t getInsertionTime(void);
            CPPOAHT::index_t getReturnedIndex(void);
            CPPOAHT::index_t getIterationsCount(void);

    };

    template <typename key_type, typename value_type>
    CPPOAHT::Query<key_type, value_type>::Query() {

        this->assignStart();

    }

    template <typename key_type, typename value_type>
    CPPOAHT::Query<key_type, value_type>::~Query() {

        if ( this->storedEntry.isFull() ) this->storedEntry.dealloc();

    }

    template <typename key_type, typename value_type>
    bool CPPOAHT::Query<key_type, value_type>::assignStart(void) {

        if (this->state == QUERY_STATE_STOPPED) {

            this->state = QUERY_STATE_RUNNING;
            this->startTime = std::chrono::steady_clock::now();

            return true;

        } else { return false; }

    }

    template <typename key_type, typename value_type>
    bool CPPOAHT::Query<key_type, value_type>::assignStop(
        CPPOAHT::index_t finalIndex, 
        CPPOAHT::index_t finalIteration
    ){

        if (this->state == QUERY_STATE_RUNNING) {

            this->state = QUERY_STATE_FINISHED;
            this->endTime = std::chrono::steady_clock::now();
            this->index = finalIndex;
            this->iterationsCount = finalIteration + 1;

            return true;

        } else { return false; }

    }

    template <typename key_type, typename value_type>
    bool CPPOAHT::Query<key_type, value_type>::isValid(void) {

        if (this->state == QUERY_STATE_FINISHED) {

            return true;

        } else { return false; }

    }

    template <typename key_type, typename value_type>
    CPPOAHT::float_t CPPOAHT::Query<key_type, value_type>::getInsertionTime(void) {

        if (this->isValid()) {
            
            std::chrono::duration<CPPOAHT::float_t, std::milli> elapsedTime;
            elapsedTime = this->endTime - this->startTime;
            return elapsedTime.count();

        } else { return 0; }
    
    }

    template <typename key_type, typename value_type>
    CPPOAHT::index_t CPPOAHT::Query<key_type, value_type>::getReturnedIndex(void) {

        return this->index;
    
    }

    template <typename key_type, typename value_type>
    CPPOAHT::index_t CPPOAHT::Query<key_type, value_type>::getIterationsCount(void) {

        return this->iterationsCount;
    
    }

    template <typename key_type, typename value_type>
    void CPPOAHT::Query<key_type, value_type>::assignQueryEntry(key_type key, value_type value) {

        if ( this->storedEntry.isUnallocated() ) this->storedEntry.alloc();
        this->storedEntry.assign(key, value);
        std::cout << "\nDEBUG K: " << key << " V: " << value << std::endl;

    }

    template <typename key_type, typename value_type>
    CPPOAHT::Entry<key_type, value_type> CPPOAHT::Query<key_type, value_type>::getQueryEntry(void) {

        return this->storedEntry;

    }

}

#endif // CPPOAHT_INDEX_H
