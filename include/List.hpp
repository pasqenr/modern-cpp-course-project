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

#include "Node.hpp"
#include "SentinelNode.hpp"

namespace simple_list {

/**
 * @brief A generic double linked list implementation.
 * @tparam T Type of the list.
 */
    template<typename T>
    class List {
    public:
        /**
         * @brief Default dtor.
         */
        virtual ~List<T>() = default;

        /**
         * @brief Return the number of elements stored in the list
         * @return Number of elements in the list.
         */
        constexpr int32_t size() const;

        /**
         * @brief Check if the list is empty, that is, have zero elements in it.
         * @return true if the list is empty, false otherwise.
         */
        constexpr bool empty() const;

        /**
         * @brief Return the first element of the list. If the list is empty an
         * error occurs.
         * @return The first element of the list.
         */
        Node<T> &first();

        /**
         * @brief Return the last element of the list. If the list is empty an error
         * occurs.
         * @return The last element of the list.
         */
        Node<T> &last();

        /**
         * @brief Add a node to the list.
         * @param[in] node The node to insert.
         */
        virtual void add(Node<T> &node) = 0;

        /**
         * @brief Remove the first node of the list;
         * @return The removed node.
         */
        virtual Node<T> &remove_front() = 0;

        /**
         * @brief Apply the function lambda to all nodes in the list.
         * @param[in] lambda A function with a Node<T>& param and returns void.
         */
        void apply(void (*lambda)(Node<T> &node));

    protected:
        /**
         * @brief Return the head of the list.
         * @return The head of the list.
         */
        SentinelNode<T> &head();

        /**
         * @brief Return the tail of the list.
         * @return The tail of the list.
         */
        SentinelNode<T> &tail();

        int32_t _size{0}; /**<  Number of elements */
        SentinelNode<T> _head{
                sl::SentinelNode<T>::SENTINEL_TYPE::HEAD
        }; /**<  Head of the list */
        SentinelNode<T> _tail{
                sl::SentinelNode<T>::SENTINEL_TYPE::TAIL
        }; /**<  Tail of the list */

    private:
        /**
         * Auxiliary apply that applies lambda to a node.
         * @param[in] node The node where to apply lambda.
         * @param[in] lambda The function to apply to node.
         */
        void apply_aux(Node<T> &node, void (*lambda)(Node<T> &node));
    };

} // namespace simple_list

#include "impl/List.i.hpp"
