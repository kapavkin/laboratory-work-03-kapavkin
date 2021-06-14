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
    array<int> arr(6);

    arr.insert(0, 1);

    ASSERT_EQ(arr[0], 1);

    arr.insert(1, 2);

    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[1], 2);

    arr.insert(2, 3);

    ASSERT_EQ(arr[2], 3);

    arr.insert(0, 4);

    ASSERT_EQ(arr[0], 4);

    arr.insert(2, 5);

    ASSERT_EQ(arr[2], 5);
}

TEST(array, remove)
{
    array<int> arr(6);

    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    arr.insert(0, 4);
    arr.insert(2, 5);

    arr.remove(4);

    ASSERT_NE(arr[3], 3);

    arr.remove(0);

    ASSERT_NE(arr[0], 4);

    arr.remove(1);

    ASSERT_NE(arr[0], 5);
    ASSERT_NE(arr[1], 5);
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

    st.push(1);

    ASSERT_EQ(st[0], 1);

    st.push(2);

    ASSERT_EQ(st[0], 1);
    ASSERT_EQ(st[1], 2);

    st.push(3);

    ASSERT_EQ(st[2], 3);

    st.push(4);

    ASSERT_EQ(st[3], 4);

    st.push(5);

    ASSERT_EQ(st[4], 5);
}

TEST(stack, pop)
{
    stack<int> st;

    st.push(1);

    ASSERT_EQ(st.pop(), 1);

    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    ASSERT_EQ(st.pop(), 5);
    ASSERT_NE(st[2], 5);
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

    lst.insert(0, 1);

    ASSERT_EQ(lst[0], 1);

    lst.insert(1, 2);

    ASSERT_EQ(lst[0], 1);
    ASSERT_EQ(lst[1], 2);

    lst.insert(2, 3);

    ASSERT_EQ(lst[2], 3);

    lst.insert(0, 4);

    ASSERT_EQ(lst[0], 4);

    lst.insert(2, 5);

    ASSERT_EQ(lst[2], 5);
}

TEST(list, remove)
{
    list<int> lst;

    lst.insert(0, 1);
    lst.insert(1, 2);
    lst.insert(2, 3);
    lst.insert(0, 4);
    lst.insert(2, 5);

    lst.remove(4);

    ASSERT_NE(lst[3], 3);

    lst.remove(0);

    ASSERT_NE(lst[0], 4);

    lst.remove(1);

    ASSERT_NE(lst[0], 5);
    ASSERT_NE(lst[1], 5);
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

    q.enqueue(1);

    ASSERT_EQ(q[0], 1);

    q.enqueue(2);

    ASSERT_EQ(q[0], 1);
    ASSERT_EQ(q[1], 2);

    q.enqueue(3);

    ASSERT_EQ(q[2], 3);

    q.enqueue(4);

    ASSERT_EQ(q[3], 4);
}

TEST(queue, dequeue)
{
    queue<int> q(4);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    ASSERT_EQ(q.dequeue(), 1);
    ASSERT_EQ(q[0], 2);

    ASSERT_EQ(q.dequeue(), 2);
    ASSERT_EQ(q[0], 3);

    ASSERT_EQ(q.dequeue(), 3);
    ASSERT_EQ(q[0], 4);

    ASSERT_EQ(q.dequeue(), 4);
}

TEST(queue, oversize)
{
    queue<int> q(4);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    q.dequeue();
    q.dequeue();

    q.enqueue(4);

    ASSERT_EQ(q[1], 4);

    q.enqueue(5);

    ASSERT_EQ(q[2], 5);

    q.enqueue(6);

    ASSERT_EQ(q[3], 6);

    ASSERT_EQ(q.dequeue(), 3);
    ASSERT_EQ(q[0], 4);

    ASSERT_EQ(q.dequeue(), 4);
    ASSERT_EQ(q[0], 5);

    ASSERT_EQ(q.dequeue(), 5);
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

    tr.put(0, 1);

    ASSERT_EQ(tr[0], 1);

    tr.put(1, 2);

    ASSERT_EQ(tr[0], 1);
    ASSERT_EQ(tr[1], 2);

    tr.put(2, 3);

    ASSERT_EQ(tr[2], 3);

    tr.put(0, 4);

    ASSERT_EQ(tr[0], 4);

    tr.put(2, 5);

    ASSERT_EQ(tr[2], 5);
}

TEST(tree, remove)
{
    tree<size_t, int> tr;

    tr.put(0, 1);
    tr.put(1, 2);
    tr.put(2, 3);
    tr.put(0, 4);
    tr.put(2, 5);

    tr.remove(2);

    ASSERT_FALSE(tr.contains(2));
    ASSERT_TRUE(tr.contains(0));

    tr.remove(0);

    ASSERT_FALSE(tr.contains(0));
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
