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

namespace simple_list {

    template<typename T>
    constexpr int32_t List<T>::size() const { return _size; }

    template<typename T>
    constexpr bool List<T>::empty() const {
        return _size == 0;
    }

    template<typename T>
    SentinelNode <T> &List<T>::head() { return _head; }

    template<typename T>
    SentinelNode <T> &List<T>::tail() { return _tail; }

    template<typename T>
    Node <T> &List<T>::first() { return this->head().next(); }

    template<typename T>
    Node <T> &List<T>::last() { return this->tail().prev(); }

    template<typename T>
    void List<T>::apply(void (*lambda)(Node <T> &node)) {
        if (this->empty()) {
            return;
        }

        apply_aux(first(), lambda);
    }

    template<typename T>
    void List<T>::apply_aux(Node <T> &node, void (*lambda)(Node <T> &node)) {
        if (!node.has_next()) {
            lambda(node);
            return;
        }

        auto &next = node.next();
        lambda(node);

        apply_aux(next, lambda);
    }

} // namespace simple_list
