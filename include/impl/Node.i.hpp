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
    Node<T>::Node()
            : _value(0), _next(), _prev() {
    }

    template<typename T>
    Node<T>::Node(T value)
            : _value(value) {
    }

    template<typename R>
    std::ostream &operator<<(std::ostream &stream, const Node <R> &node) {
        stream << node.value();
        return stream;
    }

    template<typename T>
    bool Node<T>::operator==(const Node <T> &b) const {
        return this == &b;
    }

    template<typename T>
    bool Node<T>::operator==(const SentinelNode <T> &b) const {
        return this == &b;
    }

    template<typename T>
    bool Node<T>::operator!=(const Node <T> &b) const {
        return this != &b;
    }

    template<typename T>
    bool Node<T>::operator<(const Node <T> &b) const {
        return this->_value < b._value;
    }

    template<typename T>
    bool Node<T>::operator<=(const Node <T> &b) const {
        return this->_value <= b._value;
    }

    template<typename T>
    bool Node<T>::operator>(const Node <T> &b) const {
        return this->_value > b._value;
    }

    template<typename T>
    bool Node<T>::operator>=(const Node <T> &b) const {
        return this->_value >= b._value;
    }

    template<typename T>
    T Node<T>::value() const { return _value; }

    template<typename T>
    void Node<T>::value(T val) { _value = val; }

    template<typename T>
    void Node<T>::clear() {
        clear_prev();
        clear_next();
    }

    template<typename T>
    void Node<T>::clear_prev() { _has_prev = false; }

    template<typename T>
    bool Node<T>::has_next() const { return _has_next; }

    template<typename T>
    bool Node<T>::has_prev() const { return _has_prev; }

    template<typename T>
    void Node<T>::clear_next() { _has_next = false; }

    template<typename T>
    Node <T> &Node<T>::next() {
        if (!has_next()) {
            std::cerr << "Error: node doesn't have next\n";
            // throw std::runtime_error("Error: node doesn't have next");
        }

        return *_next;
    }

    template<typename T>
    void Node<T>::next(Node <T> &node) {
        this->check_self_assignment(node);

        _has_next = true;
        _next = &node;
    }

    template<typename T>
    void Node<T>::append_next(Node <T> &node) {
        this->check_self_assignment(node);

        _has_next = true;
        auto &k = next();
        next(node);
        node.next(k);
    }

    template<typename T>
    Node <T> &Node<T>::prev() {
        if (!has_prev()) {
            std::cerr << "Error: node doesn't have prev\n";
            // throw std::runtime_error("Error: node doesn't have prev");
        }

        return *_prev;
    }

    template<typename T>
    void Node<T>::prev(Node <T> &node) {
        this->check_self_assignment(node);

        _has_prev = true;
        _prev = &node;
    }

    template<typename T>
    void Node<T>::append_prev(Node <T> &node) {
        this->check_self_assignment(node);

        _has_prev = true;
        auto &k = prev();
        prev(node);
        node.prev(k);
    }

    template<typename T>
    void Node<T>::check_self_assignment(const Node <T> &node) {
        if (this == &node) {
            std::cerr << "Warning: node self assignment.\n";
            //// throw std::invalid_argument("Node self assignment.");
        }
    }

    template<typename T>
    Node <T> &Node<T>::operator=(const Node <T> &obj) {
        if (this == &obj) {
            return *this;
        }

        this->_value = obj._value;
        this->_next = obj._next;
        this->_prev = obj._prev;
        this->_has_next = obj._has_next;
        this->_has_prev = obj._has_prev;

        return *this;
    }
} // namespace simple_list
