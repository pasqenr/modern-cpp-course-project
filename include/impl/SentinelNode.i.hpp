/**
 * @copyright Copyright 2018 SimpleList
 *
 * <blockquote>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * </blockquote>
 *
 * @author Enrico Pasquali                                                  <br>
 *         Univerity of Verona, Dept. of Computer Science                   <br>
 *         enrico.pasquali@studenti.univr.it
 * @date June, 2018
 * @version v0.1
 *
 * @file
 */

#pragma once

#include <iostream>

namespace simple_list {

    template<typename T>
    SentinelNode<T>::SentinelNode(SENTINEL_TYPE type)
            : _type(type) {
    }

    template<typename T>
    void SentinelNode<T>::set(Node <T> &obj) {
        switch (_type) {
            case HEAD:
                this->next(obj);
                break;

            case TAIL:
                this->prev(obj);
                break;

            case NOT_SET:
                std::cerr << "\nError: this node needs to be set to HEAD or TAIL";
                break;
        }
    }

    template<typename T>
    SentinelNode <T> &SentinelNode<T>::operator=(const SentinelNode <T> &obj) {
        if (this == &obj) {
            return *this;
        }

        return *this;
    }
} // namespace simple_list
