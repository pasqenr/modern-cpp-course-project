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

#include "SentinelNode.hpp"
#include <iostream>

namespace simple_list {
    template<typename T>
    class SentinelNode;

/**
 * @brief A node with pointer to the next and previous node.
 * @tparam T The type of the node.
 */
    template<typename T>
    class Node {
    public:
        /**
         * @brief Create a node with value set to zero.
         */
        explicit Node();

        /**
         * @brief Create a node with value.
         * @param[in] value The value of the node.
         */
        explicit Node(T value);

        /**
         * @brief Default copy constructor
         * @param[in] obj The other object.
         */
        Node(const Node &obj) = default;

        /**
         * @brief Writes the node value to the stream.
         * @tparam R The type of the node.
         * @param[in] stream The stream.
         * @param[in] node The node to output.
         * @return The modified stream.
         */
        template<typename R>
        friend std::ostream &operator<<(std::ostream &stream, const Node<R> &node);

        /**
         * @brief Compare the address of the Node b with the current.
         * @param[in] b The other node.
         * @return True if the nodes have the same address, false otherwise.
         */
        bool operator==(const Node<T> &b) const;

        /**
         * @brief Compare the address of the SentinelNode b with the current.
         * @param[in] b The other node.
         * @return True if the nodes have the same address, false otherwise.
         */
        bool operator==(const SentinelNode<T> &b) const;

        /**
         * @brief Compare the address of the Node b with the current.
         * @param[in] b The other node.
         * @return True if the nodes have different address, false otherwise.
         */
        bool operator!=(const Node<T> &b) const;

        /**
         * @brief Compare the value of the current node and b.
         * @param[in] b The other node.
         * @return True if the value of the current node is less than the value of
         * node b.
         */
        bool operator<(const Node<T> &b) const;

        /**
         * @brief Compare the value of the current node and b.
         * @param[in] b The other node.
         * @return True if the value of the current node is less or equal than the
         * value of node b.
         */
        bool operator<=(const Node<T> &b) const;

        /**
         * @brief Compare the value of the current node and b.
         * @param[in] b The other node.
         * @return True if the value of the current node is greater than the value
         * of node b.
         */
        bool operator>(const Node<T> &b) const;

        /**
         * @brief Compare the value of the current node and b.
         * @param[in] b The other node.
         * @return True if the value of the current node is greater or equal than
         * the value of node b.
         */
        bool operator>=(const Node<T> &b) const;

        /**
         * @brief Copy the content of obj to the current Node.
         * @param obj The other node.
         * @return The current node with the values of obj.
         */
        Node<T> &operator=(const Node<T> &obj);

        /**
         * @brief Return the value of the node.
         * @return The value of the node.
         */
        T value() const;

        /**
         * Set the value of the node to val.
         * @param[in] val The new value.
         */
        void value(T val);

        /**
         * @brief Unset the pointers to the next and previous node.
         */
        void clear();

        /**
         * @brief Unset the pointer to the previous node.
         */
        void clear_prev();

        /**
         * @brief Unset the pointer to the next node.
         */
        void clear_next();

        /**
         * @brief Check if the node has a next node.
         * @return True if the node has a valid next node, false otherwise.
         */
        bool has_next() const;

        /**
         * @brief Check if the node has a previous node.
         * @return True if the node has a valid previous node, false otherwise.
         */
        bool has_prev() const;

        /**
         * @brief Return the next node. If the next node is invalid an error occurs.
         * @return The next node.
         */
        Node<T> &next();

        /**
         * @brief Set the next Node to node.
         * @param[in] node The node to set.
         */
        void next(Node<T> &node);

        /**
         * @brief Add node between the current and the next node.
         * @param[in] node The node to insert.
         */
        void append_next(Node<T> &node);

        /**
         * @brief Return the previous node. If the previous node is invalid an error
         * occurs.
         * @return The previous node.
         */
        Node<T> &prev();

        /**
         * @brief Set the previous Node to node.
         * @param[in] node The node to set.
         */
        void prev(Node<T> &node);

        /**
         * @brief Add node between the current and the previous node.
         * @param[in] node The node to insert.
         */
        void append_prev(Node<T> &node);

    protected:
        T _value{0}; /**<  The value of the node. */
        Node<T> *_next{nullptr}; /**<  The next node. */
        Node<T> *_prev{nullptr}; /**<  The previous node. */
        bool _has_next{false}; /**<  True if the next node is valid. */
        bool _has_prev{false}; /**<  True if the previous node is valid. */

    private:
        /**
         * @brief Check if a node is assigned to himself. If so a warning occurs.
         * @param[in] node The other node.
         */
        void check_self_assignment(const Node<T> &node);
    };

} // namespace simple_list

namespace sl = simple_list;

#include "impl/Node.i.hpp"
