#include <utility>

#include "array.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

#include "gtest/gtest.h"

namespace array_test {
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
TEST(tree, iterator)
{
    tree<size_t, int> tr;

    tr.put(0, 1);
    tr.put(1, 2);
    tr.put(2, 3);
    tr.put(0, 4);
    tr.put(2, 5);
    tr.put(4, 6);
    tr.put(2, 7);
    tr.put(3, 8);

    size_t i = 0;
    for (std::pair<size_t, int> it : tr) {
        ASSERT_EQ(tr[it.first], it.second);
        i++;
    }

    ASSERT_EQ(i, tr.size());
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
