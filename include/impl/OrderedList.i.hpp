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
    void OrderedList<T>::add(Node <T> &node) {
        if (!this->head().has_next()) {
            this->head().set(node);

            if (!this->tail().has_prev()) {
                this->tail().set(node);
            }

            this->_size++;

            return;
        }

        add_aux(this->first(), node);
    }

    template<typename T>
    Node <T> &OrderedList<T>::remove_value(T value) {
        if (this->empty()) {
            std::cerr << "Error: list is empty\n";
        }

        if (value < 0) {
            std::cerr << "Error: invalid range\n";
        }

        if (this->first().value() == value) {
            return remove_front();
        }

        return remove_value_aux(this->first().next(), value);
    }

    template<typename T>
    Node <T> &OrderedList<T>::remove_front() {
        if (this->empty()) {
            std::cerr << "Error: list is empty\n";
        }

        Node<T> &k = this->first();

        if (k.has_next()) {
            this->head().set(k.next());
            k.next().clear_prev();
        } else {
            this->_head = this->_tail;
            this->head().clear();
            this->tail().clear();
        }

        k.clear();
        this->_size--;

        return k;
    }

    template<typename T>
    void OrderedList<T>::add_aux(Node <T> &cur, Node <T> &node) {
        if (node < cur) {
            if (cur == this->first()) {
                node.next(cur);
                cur.prev(node);
                this->head().set(node);

                this->_size++;
                return;
            }

            auto &prev = cur.prev();
            node.next(cur);
            cur.prev(node);
            node.prev(prev);
            node.prev().next(node);

            this->_size++;
            return;
        }

        if (cur == this->last()) {
            cur.next(node);
            node.clear_next();
            this->tail().clear();
            this->tail().set(node);
            node.prev(cur);

            this->_size++;
            return;
        }

        add_aux(cur.next(), node);
    }

    template<typename T>
    Node <T> &OrderedList<T>::remove_value_aux(Node <T> &cur, T value) {
        if (cur == this->tail()) {
            std::cerr << "Error: value not found";
        }

        if (cur.value() == value) {
            if (cur == this->last()) {
                this->tail().set(cur.prev());
                cur.prev().clear_next();
            } else {
                Node<T> &prev = cur.prev();
                Node<T> &next = cur.next();
                prev.next(cur.next());
                next.prev(prev);
            }

            cur.clear();
            this->_size--;

            if (this->empty()) {
                this->_head = this->_tail;
                this->head().clear();
                this->tail().clear();
            }

            return cur;
        }

        return remove_value_aux(cur.next(), value);
    }

} // namespace simple_list
