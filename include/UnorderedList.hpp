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

#include "List.hpp"

namespace simple_list {

    template<typename T>
    class Node;

    template<typename T>
    class List;

/**
 * @brief A double linked list.
 * @tparam T The type of the list.
 */
    template<typename T>
    class UnorderedList : public List<T> {
    public:
        /**
         * @brief Default ctor
         */
        explicit UnorderedList() = default;

        ~UnorderedList() override;

        /**
         * @brief Create a new list with the values stored in array.
         * @param[in] array The array of values.
         * @param[in] size Size of the array.
         * @return The new list.
         */
        static UnorderedList<T> *create_from_array(T *array, size_t size);

        void add(Node<T> &node) override;

        /**
         * @brief Add a node to the back of the list.
         * @param[in] node The node to insert.
         */
        void add_back(Node<T> &node);

        /**
         * @brief Add a node to the front of the list.
         * @param[in] node The node to insert.
         */
        void add_front(Node<T> &node);

        /**
         * @brief Remove the last element of the list
         * @return The remove node.
         */
        Node<T> &remove_back();

        Node<T> &remove_front() override;

        /**
         * @brief Remove the node in position index.
         * @param[in] index The position of the node in the list. Starts from zero.
         * @return The removed node.
         */
        Node<T> &remove(int32_t index);

    protected:
    private:
        /**
         * @brief Auxiliary remove function to compare index and the current
         * position.
         * @param[in] index The current index.
         * @param[in] node The node at current index.
         * @return The removed node.
         */
        Node<T> &remove_aux(int32_t index, Node<T> &node);

        bool _allocated{false}; /**<  It's true if the list has been created with
                               create_from_array. */
    };

} // namespace simple_list

#include "impl/UnorderedList.i.hpp"
