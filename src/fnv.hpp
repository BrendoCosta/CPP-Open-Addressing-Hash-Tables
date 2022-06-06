/*
    fnv.hpp

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

#ifndef CPPOAHT_FNV_H
#define CPPOAHT_FNV_H

#include <cstdint>
#include "types.hpp"

namespace CPPOAHT {

    namespace FNV {

        const std::uint32_t FNV_PRIME_32         = 0x01000193;
        const std::uint32_t FNV_OFFSET_BASIS_32  = 0x811c9dc5;
        const std::uint64_t FNV_PRIME_64         = 0x00000100000001b3;
        const std::uint64_t FNV_OFFSET_BASIS_64  = 0xcbf29ce484222325;

        /* @author  Brendo Costa <brendocosta@id.uff.br>;
         * @date    2022-04-03
         * @desc    Computes 32-bit FNV-1A hash for a given
                    data stream. Eg. passing a "Hello world!" const char*
                    string to the function returns 2054747410 = 7a78f512; */

        template <typename T>
        std::uint32_t FNV1A32(const T& data) {

            const CPPOAHT::byte_t* buffer = reinterpret_cast<const CPPOAHT::byte_t*>(data);
            std::uint32_t hash = FNV_OFFSET_BASIS_32;

            while (*buffer) {

                hash = hash ^ *buffer;
                hash = hash * FNV_PRIME_32;

                buffer++;

            }

            return hash;

        }

    }

}

#endif // CPPOAHT_FNV_H
