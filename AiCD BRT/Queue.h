#pragma once
#include <iostream>

using namespace std;

template <class T> class Queue {
private:
	class ElQueue {
	public:
		T data;
		ElQueue* next;
	};

	ElQueue* head;
	ElQueue* tail;
	size_t size;

public:
	bool isEmpty() {
		if (head == NULL) return true;
		else return false;
	}

	void enQueue(T x) {
		ElQueue* newElement = new ElQueue;
		newElement->data = x;
		newElement->next = NULL;
		if (isEmpty()) {
			tail = newElement;
			head = tail;
		}
		else {
			if (head->next == NULL) head->next = newElement;
			tail->next = newElement;
			tail = tail->next;
		}
		size++;
	}

	T deQueue() {
		if (isEmpty()) throw runtime_error("Queue is empty!");
		else {
			ElQueue* tmp = head;
			if (tmp->next == NULL) {
				head = NULL;
				tail = NULL;
			}
			else head = head->next;
			T deleted = tmp->data;
			delete tmp;
			size--;
			return deleted;
		}
	}

	size_t getsize() {
		return size;
	}

	Queue() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	~Queue() = default;
};