#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cannot_create_stack_with_too_big_length)
{
	ASSERT_ANY_THROW(TStack<int> st(500));
}

TEST(TStack, cannot_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, stack_overflow_is_an_error)
{
	TStack<int> st(5);
	for (int i = 0; i < 5; i++) {
		st.push(i);
	}
	ASSERT_ANY_THROW(st.push(12));
}

TEST(TStack, cannot_pop_from_empty_stack)
{
	TStack<int> st(5);
	st.push(4);
	st.pop();
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, get_size_works_properly)
{
	TStack<int> st(5);
	st.push(4);
	st.pop();
	st.push(23);
	ASSERT_EQ(1, st.getsize());
}

TEST(TStack, empty_stack_is_empty)
{
	TStack<int> st(5);
	st.push(4);
	st.pop();
	st.push(23);
	st.pop();
	ASSERT_TRUE(st.empty());
}

TEST(TStack, not_empty_stack_is_not_empty)
{
	TStack<int> st(5);
	st.push(4);
	st.pop();
	st.push(23);
	st.pop();
	st.push(5);
	ASSERT_FALSE(st.empty());
}

TEST(TStack, full_stack_is_full)
{
	TStack<int> st(1);
	st.push(4);
	st.pop();
	st.push(23);

	ASSERT_TRUE(st.full());
}

TEST(TStack, almost_full_stack_is_not_full)
{
	TStack<int> st(5);
	st.push(4);
	st.pop();
	st.push(23);
	st.pop();
	st.push(5);
	st.push(5);
	st.push(5);
	st.push(5);
	ASSERT_FALSE(st.full());
}
