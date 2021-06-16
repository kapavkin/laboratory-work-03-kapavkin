#include <utility>

#include "array.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

#include "gtest/gtest.h"

namespace array_test {
TEST(array, constructor)
{
    array<int> arr0;
    array<int> arr1(2);
    array<int> arr2(arr0);
    array<int> arr3(arr1);
}

TEST(array, insert)
{
    array<int> arr(10);

    arr.insert(0, 0);

    ASSERT_EQ(arr[0], 0);

    arr.insert(1, 1);

    ASSERT_EQ(arr[0], 0);
    ASSERT_EQ(arr[1], 1);

    arr.insert(2, 2);

    ASSERT_EQ(arr[2], 2);

    arr.insert(0, 3);

    ASSERT_EQ(arr[0], 3);

    arr.insert(2, 4);

    ASSERT_EQ(arr[2], 4);
}

TEST(array, remove)
{
    array<int> arr(10);

    arr.insert(0, 0);
    arr.insert(1, 1);
    arr.insert(2, 2);
    arr.insert(0, 3);
    arr.insert(2, 4);

    arr.remove(4);

    ASSERT_NE(arr[3], 2);

    arr.remove(0);

    ASSERT_NE(arr[0], 3);

    arr.remove(1);

    ASSERT_NE(arr[0], 4);
    ASSERT_NE(arr[1], 4);
}

TEST(array, iterator)
{
    array<int> arr(6);

    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    arr.insert(0, 4);
    arr.insert(2, 5);

    size_t i = 0;
    for (int it : arr) {
        ASSERT_EQ(arr[i++], it);
    }

    ASSERT_EQ(i, arr.capacity());
}
}

namespace stack_test {
TEST(stack, constructor)
{
    stack<int> st0;
    stack<int> st1(2);
    stack<int> st2(st0);
    stack<int> st3(st1);
}

TEST(stack, push)
{
    stack<int> st;

    st.push(0);

    ASSERT_EQ(st[0], 0);

    st.push(1);

    ASSERT_EQ(st[0], 0);
    ASSERT_EQ(st[1], 1);

    st.push(2);

    ASSERT_EQ(st[2], 2);

    st.push(3);

    ASSERT_EQ(st[3], 3);

    st.push(4);

    ASSERT_EQ(st[4], 4);
}

TEST(stack, pop)
{
    stack<int> st;

    st.push(0);

    ASSERT_EQ(st.pop(), 0);

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);

    ASSERT_EQ(st.pop(), 4);
    ASSERT_NE(st[2], 4);
}

TEST(stack, iterator)
{
    stack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    size_t i = 0;
    for (int it : st) {
        ASSERT_EQ(st[i++], it);
    }

    ASSERT_EQ(i, st.size());
}
}

namespace list_test {
TEST(list, constructor)
{
    list<int> lst0;
    list<int> lst1(lst0);
}

TEST(list, insert)
{
    list<int> lst;

    lst.insert(0, 0);

    ASSERT_EQ(lst[0], 0);

    lst.insert(1, 1);

    ASSERT_EQ(lst[0], 0);
    ASSERT_EQ(lst[1], 1);

    lst.insert(2, 2);

    ASSERT_EQ(lst[2], 2);

    lst.insert(0, 3);

    ASSERT_EQ(lst[0], 3);

    lst.insert(2, 4);

    ASSERT_EQ(lst[2], 4);
}

TEST(list, remove)
{
    list<int> lst;

    lst.insert(0, 0);
    lst.insert(1, 1);
    lst.insert(2, 2);
    lst.insert(0, 3);
    lst.insert(2, 4);

    lst.remove(4);

    ASSERT_NE(lst[3], 2);

    lst.remove(0);

    ASSERT_NE(lst[0], 3);

    lst.remove(1);

    ASSERT_NE(lst[0], 4);
    ASSERT_NE(lst[1], 4);
}

TEST(list, iterator)
{
    list<int> lst;

    lst.insert(0, 1);
    lst.insert(1, 2);
    lst.insert(2, 3);
    lst.insert(0, 4);
    lst.insert(2, 5);

    size_t i = 0;
    for (int it : lst) {
        ASSERT_EQ(lst[i++], it);
    }

    ASSERT_EQ(i, lst.size());
}
}

namespace queue_test {
TEST(queue, constructor)
{
    queue<int> q0(2);
    queue<int> q1(q0);
}

TEST(queue, enqueue)
{
    queue<int> q(4);

    q.enqueue(0);

    ASSERT_EQ(q[0], 0);

    q.enqueue(1);

    ASSERT_EQ(q[0], 0);
    ASSERT_EQ(q[1], 1);

    q.enqueue(2);

    ASSERT_EQ(q[2], 2);

    q.enqueue(3);

    ASSERT_EQ(q[3], 3);
}

TEST(queue, dequeue)
{
    queue<int> q(4);

    q.enqueue(0);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    ASSERT_EQ(q.dequeue(), 0);
    ASSERT_EQ(q[0], 1);

    ASSERT_EQ(q.dequeue(), 1);
    ASSERT_EQ(q[0], 2);

    ASSERT_EQ(q.dequeue(), 2);
    ASSERT_EQ(q[0], 3);

    ASSERT_EQ(q.dequeue(), 3);
}

TEST(queue, oversize)
{
    queue<int> q(4);

    q.enqueue(0);
    q.enqueue(1);
    q.enqueue(2);

    q.dequeue();
    q.dequeue();
    
    q.enqueue(3);

    ASSERT_EQ(q[1], 3);

    q.enqueue(4);

    ASSERT_EQ(q[2], 4);

    q.enqueue(5);

    ASSERT_EQ(q[3], 5);

    ASSERT_EQ(q.dequeue(), 2);
    ASSERT_EQ(q[0], 3);

    ASSERT_EQ(q.dequeue(), 3);
    ASSERT_EQ(q[0], 4);

    ASSERT_EQ(q.dequeue(), 4);
}

TEST(queue, iterator)
{
    queue<int> q(4);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    size_t i = 0;
    for (int it : q) {
        ASSERT_EQ(q[i++], it);
    }

    ASSERT_EQ(i, q.size());
}
}

namespace tree_test {
TEST(tree, constructor)
{
    tree<size_t, int> tr0;
    tree<size_t, int> tr1(tr0);
}

TEST(tree, put)
{
    tree<size_t, int> tr;

    tr.put(0, 0);

    ASSERT_EQ(tr[0], 0);

    tr.put(1, 1);

    ASSERT_EQ(tr[0], 0);
    ASSERT_EQ(tr[1], 1);

    tr.put(2, 2);

    ASSERT_EQ(tr[2], 2);

    tr.put(0, 3);

    ASSERT_EQ(tr[0], 3);

    tr.put(2, 4);

    ASSERT_EQ(tr[2], 4);
}

TEST(tree, remove)
{
    tree<size_t, int> tr;

    tr.put(0, 0);
    tr.put(1, 1);
    tr.put(2, 2);
    tr.put(0, 3);
    tr.put(2, 4);

    tr.remove(2);

    ASSERT_FALSE(tr.contains(2));
    ASSERT_TRUE(tr.contains(0));

    tr.remove(0);

    ASSERT_FALSE(tr.contains(0));
}

TEST(tree, iterator)
{
    tree<size_t, int> tr;

    tr.put(4, 5);
    tr.put(3, 4);
    tr.put(2, 3);
    tr.put(1, 2);
    tr.put(0, 1);

    size_t i = 0;
    for (std::pair<size_t, int> it : tr) {
        ASSERT_EQ(tr[i++], it.second);
    }

    ASSERT_EQ(i, tr.size());
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
