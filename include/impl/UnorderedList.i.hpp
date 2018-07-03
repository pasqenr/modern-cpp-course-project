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
    UnorderedList<T>::~UnorderedList() {
        if (this->_allocated) {
            this->apply([](Node<T> &node) { delete &node; });
        }
    }

    template<typename T>
    UnorderedList <T> *UnorderedList<T>::create_from_array(T *array, size_t size) {
        auto *list = new UnorderedList<T>;

        for (size_t i = 0; i < size; i++) {
            T value = array[i];
            auto *node = new sl::Node<T>(value);
            list->add_back(*node);
        }

        list->_allocated = true;

        return list;
    }

    template<typename T>
    void UnorderedList<T>::add(Node <T> &node) {
        this->add_back(node);
    }

    template<typename T>
    void UnorderedList<T>::add_back(Node <T> &node) {
        if (!List<T>::tail().has_prev()) {
            this->tail().set(node);

            if (!List<T>::head().has_next()) {
                this->head().set(node);
            }
        } else {
            List<T>::last().next(node);
            node.prev(List<T>::last());
            this->tail().set(node);
        }

        this->_size++;
    }

    template<typename T>
    void UnorderedList<T>::add_front(Node <T> &node) {
        if (!List<T>::head().has_next()) {
            this->head().set(node);

            if (!List<T>::tail().has_prev()) {
                this->tail().set(node);
            }
        } else {
            List<T>::first().prev(node);
            node.next(List<T>::first());
            this->head().set(node);
        }

        this->_size++;
    }

    template<typename T>
    Node <T> &UnorderedList<T>::remove_back() {
        if (this->empty()) {
            std::cerr << "Error: empty list\n";
        }

        auto &node = this->last();

        if (node.has_prev()) {
            this->tail().set(node.prev());
        } else {
            this->_tail = this->_head;
        }

        node.clear();
        this->_size--;

        return node;
    }

    template<typename T>
    Node <T> &UnorderedList<T>::remove_front() {
        if (this->empty()) {
            std::cerr << "Error: empty list";
        }

        auto &node = List<T>::first();

        if (node.has_next()) {
            this->head().set(node.next());;
        } else {
            this->_head = this->_tail;
        }

        node.clear();
        this->_size--;

        return node;
    }

    template<typename T>
    Node <T> &UnorderedList<T>::remove(int32_t index) {
        if (index < 0) {
            std::cerr << "Error: negative index";
        }

        if (this->empty()) {
            std::cerr << "Error: empty list";
        }

        if (index > this->size()) {
            std::cerr << "Error: index out of range";
        }

        return remove_aux(index, List<T>::first());
    }

    template<typename T>
    Node <T> &UnorderedList<T>::remove_aux(int32_t index, Node <T> &node) {
        if (index != 0) {
            return remove_aux(index - 1, node.next());
        }

        if (node.has_next()) {
            auto &next = node.next();
            auto &prev = node.prev();

            prev.next(next);
            next.prev(prev);
        } else {
            if (node.has_prev()) {
                node.prev().clear_next();
                this->tail().set(node.prev());
            } else {
                this->_head = this->_tail;
            }
        }

        node.clear();
        this->_size--;

        return node;
    }

} // namespace simple_list
