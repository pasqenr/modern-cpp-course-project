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

/**
 * @brief A double linked list that keeps the elements ordered.
 * @tparam T Type of the list.
 */
    template<typename T>
    class OrderedList : public List<T> {
    public:
        /**
         * @brief Default ctor
         */
        explicit OrderedList() = default;

        /**
         * @brief Default dtor.
         */
        ~OrderedList() override = default;

        void add(Node<T> &node) override;

        /**
         * @brief Remove the first node with value equal to value.
         * @param[in] value The value to search.
         * @return The node with the value searched.
         */
        Node<T> &remove_value(T value);

        Node<T> &remove_front() override;

    protected:
    private:
        /**
         * @brief Auxiliary add function that compares the current node cur and the
         * node to insert.
         * @param[in] cur The current node.
         * @param[in] node The node to insert.
         */
        void add_aux(Node<T> &cur, Node<T> &node);

        /**
         * @brief Auxiliary remove_value function that compares the current node cur
         * and the value to find.
         * @param[in] cur The current node.
         * @param[in] value The value to compare.
         * @return The removed node.
         */
        Node<T> &remove_value_aux(Node<T> &cur, T value);
    };

} // namespace simple_list

#include "impl/OrderedList.i.hpp"
