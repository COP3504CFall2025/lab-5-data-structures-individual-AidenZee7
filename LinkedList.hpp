#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
	// Stores pointers to first and last nodes and count
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;
	unsigned int count;

public:
	// Behaviors
	void printForward() const {
		Node* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->data << " ";
			ptr = ptr->next;
		}
	}
	void printReverse() const {
		Node* ptr = tail;
		while (ptr != nullptr) {
			cout << ptr->data << " ";
			ptr = ptr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* a = new Node{data, nullptr, head};
		if (head != nullptr) { // if list not empty
			(*head).prev = a; // change old head's previous from nullptr to new head
		}
		head = a;
		if (tail == nullptr) {
			tail = a;
		}
		count++;
	}
	void addTail(const T& data) {
		Node* a = new Node{data, tail, nullptr};
		if (tail != nullptr) { // if list not empty
			(*tail).next = a;
		}
		tail = a;
		if (head == nullptr) { // if empty
			head = a;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		}
		Node* old = head;
		if (head == tail) { // if only one node
			delete old;
			count--;
			head = nullptr;
			tail = nullptr;
			return true;
		}
		else {
			head->next->prev = nullptr;
			head = old->next;
			delete old;
			old = nullptr;
		}
		count--;
		return true;
	}

	bool removeTail() {
		if (tail == nullptr) {
			return false;
		}
		Node* old = tail;
		if (tail == head) { // if one node
			delete tail;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		else {
			old->prev->next = nullptr;
			tail = old->prev;
			delete old;
			old = nullptr;
		}
		count--;
		return true;
	}

	void clear() {
		while (tail != head) { // while there's more than 1 element
			removeTail();
		}
		//delete that last element
		delete head;
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept { // move assign
		if (this == &other) {
			return (*this);
		}
		clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return (*this);
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) { // copy assign
		if (this == &rhs) {
			return (*this);
		}
		LinkedList<T> temp;
		Node* ptr = rhs.head;
		while (ptr != nullptr) {
			temp.addTail(ptr->data);
			ptr = ptr->next;
		}
		clear();
		head = temp.head;
		tail = temp.tail;
		count = temp.count;
		temp.head = nullptr;
		temp.tail = nullptr;
		temp.count = 0;
		return (*this);
	}
	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) { // copy constr
		count = 0;
		Node* ptr = list.head;
		head = nullptr;
		tail = nullptr;
		while (ptr != nullptr) {
			addTail(ptr->data);
			ptr = ptr->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept { // move constr
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		clear();
	}
};
