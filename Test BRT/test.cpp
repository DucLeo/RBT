#include "pch.h"
#include "gtest/gtest.h"
#include "..\BRT\RBT.h"

TEST(Test_Insert) {
	//When tree is empty
	RBT<int, int> tree;
	tree.insert(10, 8);
	ASSERT_EQ(tree.root->key, 10);
	ASSERT_EQ(tree.root->value, 8);
	//Insert the same key
	ASSERT_THROW(tree.insert(10, 10), logic_error);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);
	Queue<Element<int, int>*>* elements = tree.allElementsByBFT();
	Element<int, int>* tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 10);
	ASSERT_EQ(tmp->value, 8);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 8);
	ASSERT_EQ(tmp->value, 3);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 12);
	ASSERT_EQ(tmp->value, 7);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 3);
	ASSERT_EQ(tmp->value, 2);
}
TEST(Test_Find) {
	//When tree is empty
	RBT<int, int> tree;
	ASSERT_THROW(tree.find(4), invalid_argument);
	tree.insert(10, 8);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);
	//When key to find does not exist
	ASSERT_THROW(tree.find(4), invalid_argument);
	ASSERT_EQ(tree.find(12)->value, 7);
	ASSERT_EQ(tree.find(3)->value, 2);
}
TEST(Test_Remove) {
	RBT<int, int> tree;
	tree.insert(10, 8);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);

	tree.insert(11, 12);
	//When key to remove does not exist
	ASSERT_THROW(tree.remove(13), invalid_argument);
	tree.remove(11);
	Queue<Element<int, int>*>* elements = tree.allElementsByBFT();
	Element<int, int>* tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 10);
	ASSERT_EQ(tmp->value, 8);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 8);
	ASSERT_EQ(tmp->value, 3);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 12);
	ASSERT_EQ(tmp->value, 7);
	tmp = elements->deQueue();
	ASSERT_EQ(tmp->key, 3);
	ASSERT_EQ(tmp->value, 2);
}
TEST(Test_Clear) {
	RBT<int, int> tree;
	//When tree is empty
	ASSERT_THROW(tree.clear(), logic_error);
	tree.insert(10, 8);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);
	tree.clear();
	ASSERT_EQ(tree.root, tree.nil);
}
TEST(Test_GetKeys) {
	RBT<int, int> tree;
	tree.insert(10, 8);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);
	List<int>* keys = tree.getKeys();
	EoList<int>* tmp = keys->head;
	ASSERT_EQ(tmp->data, 10);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 8);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 12);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 3);
	ASSERT_EQ(tmp, keys->tail);

	delete keys;
}
TEST(Test_GetValues) {
	RBT<int, int> tree;
	tree.insert(10, 8);
	tree.insert(8, 3);
	tree.insert(12, 7);
	tree.insert(3, 2);
	List<int>* values = tree.getValues();
	EoList<int>* tmp = values->head;
	ASSERT_EQ(tmp->data, 8);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 3);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 7);
	tmp = tmp->next;
	ASSERT_EQ(tmp->data, 2);
	ASSERT_EQ(tmp, values->tail);
	delete values;
}