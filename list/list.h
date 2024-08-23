#pragma once

#include <iostream>
#include <cassert>
using namespace std;
namespace new_list {
	template<class T>
	struct ListNode {
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;

		ListNode(const T& x = T()) :_next(nullptr), _prev(nullptr), _data(x) {}
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator {
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		Node* _node;

		__list_iterator(Node* node) :_node(node) {}

		self& operator++() {
			_node = _node->_next;
			return *this;
		}

		self operator++(int) {
			self temp(*this);
			_node = _node->_next;
			return temp;
		}

		self& operator--() {
			_node = _node->_prev;
			return *this;
		}

		self operator--(int) {
			self temp(*this);
			_node = _node->_prev;
			return temp;
		}

		Ref operator*() {
			return _node->_data; 
		}

		Ptr operator->() {		//多用于自定义类型中
			return &_node->_data;
		}

		bool operator != (const self& s){
			return _node != s._node;
		}

		bool operator == (const self& s) {
			return _node == s._node;
		}
	};

	//太冗长，可以直接优化
	/*template<class T>	
	struct __list_const_iterator {
		typedef ListNode<T> Node;
		typedef __list_const_iterator<T> self;
		Node* _node;

		__list_const_iterator(Node* node) :_node(node) {}

		self& operator++() {
			_node = _node->_next;
			return *this;
		}

		self operator++(int) {
			self temp(*this);
			_node = _node->_next;
			return temp;
		}

		self& operator--() {
			_node = _node->_prev;
			return *this;
		}

		self operator--(int) {
			self temp(*this);
			_node = _node->_prev;
			return temp;
		}

		const T& operator*() {
			return _node->_data;
		}

		bool operator != (const self& s) {
			return _node != s._node;
		}

		bool operator == (const self& s) {
			return _node == s._node;
		}
	};*/

	template<class T>
	class list {
		typedef ListNode<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		/*typedef __list_const_iterator<T> const_iterator;*/
		iterator begin() {
			/*return iterator(_head->_next);*/
			//单参数构造函数隐式类型转换
			return _head->_next;
		}

		iterator end() {
			return _head;
		}

		const_iterator begin() const{ 
			return _head->_next;
		}

		const_iterator end() const {
			return _head;
		}

		list() {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list(list<T>& lt) {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			for (const auto& x : lt) {
				push_back(x);
			}
		}

		list<T>& operator=(list<T>& lt) {	//传统写法
			if (this != lt) {
				clear();
				for (const auto& x : lt) {
					push_back(x);
				}
			}
			return *this;
		}

		void swap(list<T>& temp) {
			std::swap(_head, temp._head);
		}

		list<T>& operator=(list<T> lt) {
			swap(lt);
			return *this;
		}
		void push_back(const T& x) {
			/*Node* newnode = new Node(x);
			Node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;*/
			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x);
		}

		void pop_back() {
			erase(--end());
		}

		void pop_front() {
			erase(begin());
		}
		
		void clear() {
			iterator it = begin();
			while (it != end()) {
				it = erase(it);
			}
		}

		iterator insert(iterator pos, const T& x) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return newnode;
		}

		iterator erase(iterator pos) {
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;

			delete cur;
			return next;
		}

		~list() {
			clear();

			delete _head;
			_head = nullptr;
		}
	private:
		Node* _head;
	};

	void Test_1() {
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		list<int>::iterator it = lt.begin();
		while (it != lt.end()) {
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;

		lt.pop_back();
		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;
	}

	void Test_2() {
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;

		lt.push_front(5);
		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;

		lt.pop_back();
		lt.pop_front();
		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;

		lt.clear();
		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;
	}

	void print_list(const list<int>& lt) {
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end()) {
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;
	}

	void Test_3() {
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		for (auto x : lt) {
			cout << x << " ";
		}
		cout << endl;
		print_list(lt);
	}

	struct nums {
		int _a1;
		int _a2;

		nums(int a1 = 2, int a2 = 3) :_a1(a1), _a2(a2){}
	};

	void Test_4() {
		list<nums> lt;
		lt.push_back(nums());
		lt.push_back(nums());
		lt.push_back(nums());
		lt.push_back(nums());

		list<nums>::iterator it = lt.begin();
		while (it != lt.end()) {
			/*cout << (*it)._a1 << " " << (*it)._a2 << endl;*/
			cout << it->_a1 << " " << it->_a2 << endl;
			++it;
		}
	}
}