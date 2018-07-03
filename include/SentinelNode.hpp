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

namespace simple_list {
    template<typename T>
    class Node;

/**
 * @brief A special node to mark the head and the tail of the list.
 * @tparam T The type of the node.
 */
    template<typename T>
    class SentinelNode : public Node<T> {

    public:
        /**
         * @brief Possible types for the sentinel node.
         */
        enum SENTINEL_TYPE {
            NOT_SET,
            HEAD,
            TAIL
        };

        /**
         * @brief Create a new sentinel of selected type.
         * @param[in] type Type of the sentinel node.
         */
        explicit SentinelNode(SENTINEL_TYPE type);

        /**
         * @brief Default copy constructor
         * @param[in] obj The other object.
         */
        SentinelNode(const SentinelNode &obj) = default;

        /**
         * @brief Set obj as next node if the type is HEAD, as previous if the type
         * is TAIL.
         * @param[in] obj The node to attach.
         */
        void set(Node<T> &obj);

        /**
         * @brief Assign the sentinel always to himself.
         * @param[in] obj The other sentinel node.
         * @return The sentinel node himself.
         */
        SentinelNode<T> &operator=(const SentinelNode<T> &obj);

    protected:
        SENTINEL_TYPE _type{NOT_SET}; /**< The type of the sentinel. */
    };
} // namespace simple_list

#include "impl/SentinelNode.i.hpp"
