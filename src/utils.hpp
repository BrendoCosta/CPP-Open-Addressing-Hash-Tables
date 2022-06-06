/*
    cppoaht_utils.h

    This header provides some useful functions's interfaces.

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

#ifndef CPPOAHT_UTILS_H
#define CPPOAHT_UTILS_H

#include <cmath>

namespace CPPOAHT {

    class Utils {

        public:

            template <typename type>
            static bool isInteger(type number);

            template <typename type>
            static bool isPrime(type number);

            template <typename type>
            static type getNextPrime(type number);


    };

    /* ---------------------------------------------------------------------- */

    template <typename type>
    bool Utils::isInteger(type number) {

        return std::floor(number) == number;

    }

    template <typename type>
    bool Utils::isPrime(type number) {

        if (number == 2) return true;

        if (number == 1 || number % 2 == 0) return false;

        for (type i = 3; (i * i) < number + 1; i += 2) {

            if (number % i == 0) return false;

        }

        return true;

    }

    /* --- */

    template <typename type>
    type Utils::getNextPrime(type number) {

        if (number <= 1) {

                return 2;

        } else {

            while (!isPrime(number)) {

                number++;

            }

            return number;

        }

    }

}

#endif // CPPOAHT_UTILS_H
