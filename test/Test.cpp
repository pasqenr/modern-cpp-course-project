/**
 * @copyright Copyright 2018 SimpleList
 *
 * @license{<blockquote>
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * </blockquote>}
 *
 * @author Enrico Pasquali                                                  <br>
 *         Univerity of Verona, Dept. of Computer Science                   <br>
 *         enrico.pasquali@studenti.univr.it
 * @date June, 2018
 * @version v0.1
 *
 * @file
 */

#include "../include/OrderedList.hpp"
#include "../include/UnorderedList.hpp"
#include "Node.hpp"

#define CATCH_CONFIG_MAIN

#include <../lib/catch.hpp>

#undef CATCH_CONFIG_MAIN

template<typename T>
void mul(sl::Node<T> &n) {
    n.value(n.value() * 2);
}

TEST_CASE("Node ctors", "[node_ctor]") {
    using T = int;

    sl::Node<T> n1;
    sl::Node<T> n2(2);
    const sl::Node<T> &n3(n1);

    REQUIRE(n1.value() == 0);
    REQUIRE(n2.value() == 2);
    REQUIRE(n3.value() == 0);
}

TEST_CASE("Node operators", "node [node_op]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(1);
    sl::Node<T> n3(2);

    REQUIRE(n1 != n2);
    REQUIRE(n1 == n1);
    REQUIRE(n1 <= n2);
    REQUIRE(n1 <= n3);
    REQUIRE(n1 < n3);
    REQUIRE(n3 > n1);
    REQUIRE(n3 >= n1);
    REQUIRE(n3 >= n3);
}

TEST_CASE("Node value", "[node_value]") {
    using T = int;

    sl::Node<T> n1(1);

    REQUIRE(n1.value() == 1);

    n1.value(2);

    REQUIRE(n1.value() == 2);
}

TEST_CASE("Node next", "[node_next]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);

    n1.next(n2);

    REQUIRE(n1.next() == n2);
    REQUIRE(n1 != n2);
    REQUIRE(n1.next() != n1);

    n1.next(n3);

    REQUIRE(n1.next() == n3);
}

TEST_CASE("Node prev", "[node_prev]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);

    n1.prev(n2);

    REQUIRE(n1.prev() == n2);
    REQUIRE(n1 != n2);
    REQUIRE(n1.prev() != n1);

    n1.prev(n3);

    REQUIRE(n1.prev() == n3);
}

TEST_CASE("Node append_next", "[append_next]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);

    n1.append_next(n2);

    REQUIRE(n1.next() == n2);

    n1.append_next(n3);

    REQUIRE(n1.next() == n3);
    REQUIRE(n1.next().next() == n2);
}

TEST_CASE("Node append_prev", "[append_prev]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);

    n1.append_prev(n2);

    REQUIRE(n1.prev() == n2);

    n1.append_prev(n3);

    REQUIRE(n1.prev() == n3);
    REQUIRE(n1.prev().prev() == n2);
}

TEST_CASE("UnoredereList first", "[ul_first]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::UnorderedList<T> list;

    list.add_back(n1);

    REQUIRE(list.first() == n1);

    list.add_back(n2);

    REQUIRE(list.first() == n1);
}

TEST_CASE("UnoredereList empty", "[ul_empty]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::UnorderedList<T> list;

    REQUIRE(list.empty());

    list.add_back(n1);

    REQUIRE(list.first() == n1);
    REQUIRE(!list.empty());

    list.remove_back();

    REQUIRE(list.empty());
}

TEST_CASE("UnorderedList add_back", "[ul_add_back]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_back(n1);

    REQUIRE(list.first() == n1);
    REQUIRE(list.last() == n1);

    list.add_back(n2);

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.last() == n2);

    list.add_back(n3);

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.first().next().next() == n3);
    REQUIRE(list.last() == n3);

    REQUIRE(n1.next() == n2);
    REQUIRE(n1.next().next() == n3);
    REQUIRE(n2.prev() == n1);
    REQUIRE(n2.next() == n3);
}

TEST_CASE("UnorderedList add_front", "[ul_add_front]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_front(n1);

    REQUIRE(list.first() == n1);
    REQUIRE(list.last() == n1);

    list.add_front(n2);

    REQUIRE(list.first() == n2);
    REQUIRE(list.first().next() == n1);
    REQUIRE(list.last() == n1);

    list.add_front(n3);

    REQUIRE(list.first() == n3);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.first().next().next() == n1);
    REQUIRE(list.last() == n1);

    REQUIRE(n3.next() == n2);
    REQUIRE(n3.next().next() == n1);
    REQUIRE(n2.prev() == n3);
    REQUIRE(n2.next() == n1);
}

TEST_CASE("UnorderedList remove_back", "[ul_remove_back]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_back(n1);
    list.add_back(n2);
    list.add_back(n3);

    REQUIRE(list.last() == n3);

    auto &r3 = list.remove_back();

    REQUIRE(r3 == n3);

    auto &r2 = list.remove_back();
    auto &r1 = list.remove_back();

    REQUIRE(list.empty());
    REQUIRE(r2 == n2);
    REQUIRE(r1 == n1);
}

TEST_CASE("UnorderedList remove_front", "[ul_remove_front]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_front(n1);
    list.add_front(n2);
    list.add_front(n3);

    REQUIRE(list.first() == n3);

    auto &r3 = list.remove_front();

    REQUIRE(r3 == n3);

    auto &r2 = list.remove_front();
    auto &r1 = list.remove_front();

    REQUIRE(list.empty());
    REQUIRE(r2 == n2);
    REQUIRE(r1 == n1);
}

TEST_CASE("UnorderedList remove", "[ul_remove]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_back(n1);
    list.add_back(n2);
    list.add_back(n3);

    auto &r3 = list.remove(2);
    auto &r2 = list.remove(1);
    auto &r1 = list.remove(0);

    REQUIRE(r3 == n3);
    REQUIRE(r2 == n2);
    REQUIRE(r1 == n1);
    REQUIRE(list.empty());

    list.add_back(n1);

    REQUIRE(list.first() == n1);
    REQUIRE(list.last() == n1);
}

TEST_CASE("List apply", "[l_apply]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::UnorderedList<T> list;

    list.add_back(n1);
    list.add_back(n2);
    list.add_back(n3);

    list.apply(mul);

    REQUIRE(n1.value() == 2);
    REQUIRE(n2.value() == 4);
    REQUIRE(n3.value() == 6);
}

TEST_CASE("OrderedList add", "[ol_add]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::Node<T> n4(4);
    sl::OrderedList<T> list;

    list.add(n1);
    list.add(n2);
    list.add(n3);

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.first().next().next() == n3);
    REQUIRE(list.last() == n3);

    sl::OrderedList<T> list2;

    list2.add(n3);
    list2.add(n2);
    list2.add(n1);

    REQUIRE(list2.first() == n1);
    REQUIRE(list2.first().next() == n2);
    REQUIRE(list2.first().next().next() == n3);
    REQUIRE(list2.last() == n3);

    sl::OrderedList<T> list3;

    list3.add(n2);
    list3.add(n3);
    list3.add(n1);

    REQUIRE(list3.first() == n1);
    REQUIRE(list3.first().next() == n2);
    REQUIRE(list3.first().next().next() == n3);
    REQUIRE(list3.last() == n3);

    sl::OrderedList<T> list4;

    list4.add(n3);
    list4.add(n2);
    list4.add(n4);
    list4.add(n1);

    REQUIRE(list4.first() == n1);
    REQUIRE(list4.first().next() == n2);
    REQUIRE(list4.first().next().next() == n3);
    REQUIRE(list4.first().next().next().next() == n4);
    REQUIRE(list4.last() == n4);
    REQUIRE(list4.last().prev() == n3);
    REQUIRE(list4.last().prev().prev() == n2);
    REQUIRE(list4.last().prev().prev().prev() == n1);
}

TEST_CASE("OrderedList remove_value", "[ol_remove_value]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::Node<T> n4(4);
    sl::OrderedList<T> list;

    list.add(n1);
    list.add(n2);
    list.add(n3);
    list.add(n4);

    list.remove_value(n3.value());

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.first().next().next() == n4);
    REQUIRE(list.last() == n4);
    REQUIRE(list.last().prev() == n2);
    REQUIRE(list.last().prev().prev() == n1);

    list.remove_value(n1.value());

    REQUIRE(list.first() == n2);

    list.remove_value(n4.value());

    REQUIRE(list.last() == n2);

    list.remove_value(n2.value());

    REQUIRE(list.empty());

    list.add(n3);
    list.add(n2);
    list.add(n4);
    list.add(n1);

    list.remove_value(n2.value());

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n3);
    REQUIRE(list.last().prev() == n3);

    list.remove_value(n3.value());

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n4);

    list.remove_value(n1.value());

    REQUIRE(list.last() == n4);
    REQUIRE(list.first() == n4);
}

TEST_CASE("OrderedList remove_front", "[ol_remove_front]") {
    using T = int;

    sl::Node<T> n1(1);
    sl::Node<T> n2(2);
    sl::Node<T> n3(3);
    sl::Node<T> n4(4);
    sl::OrderedList<T> list;

    list.add(n1);
    list.add(n2);

    auto &r1 = list.remove_front();

    REQUIRE(r1 == n1);
    REQUIRE(list.first() == n2);

    list.remove_front();

    REQUIRE(list.empty());

    list.add(n3);
    list.add(n4);
    list.add(n1);
    list.add(n2);

    REQUIRE(list.first() == n1);
    REQUIRE(list.first().next() == n2);
    REQUIRE(list.last().prev() == n3);
    REQUIRE(list.last() == n4);
}

TEST_CASE("UnorderedList create_from_array", "[ul_create_from_array]") {
    using T = int;

    const size_t ksize = 3;
    T array[ksize] = {1, 2, 3};

    auto *list = sl::UnorderedList<T>::create_from_array(array, ksize);

    REQUIRE(list->first().value() == 1);
    REQUIRE(list->first().next().value() == 2);
    REQUIRE(list->last().value() == 3);

    delete list;
}
