#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

namespace new_vector {
	template<class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{}

		//拷贝构造（深拷贝）
		vector(const vector<T>& v) {
			_start = new T[v.capacity()];
			memcpy(_start, v._start, v.size() * sizeof(T));
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator end) {
			while (first != end) {
				push_back(*first);
				++first;
			}
		}

		vector(size_t n, const T& val = T()) {
			resize(n, val);
		}

		vector(int n, const T& val = T()) {		//为了防止优先匹配问题出现
			resize(n, val);
		}

		//交换函数
		void swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		//赋值运算符重载
		vector<T>& operator=(vector<T> v) {
			swap(v);
			return *this;
		}

		//析构函数
		~vector() {
			if (_start) {
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		size_t size() const {
			return _finish - _start;
		}

		size_t capacity() const {
			return _end_of_storage - _start;
		}

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _finish;
		}

		const_iterator begin() const { 
			return _start;
		}

		const_iterator end() const { 
			return _finish;
		}

		void reserve(size_t num) {
			if (num > capacity()) {
				size_t old = size();
				T* temp = new T[num];
				if (_start) { //如果_start不为空则直接拷贝数据
					/*memcpy(temp, _start, old * sizeof(T));*/	//内置类型没有问题，但是自定义类西会涉及到深拷贝的问题
					for (size_t i = 0; i < old; i++) {	//处理自定义类型深拷贝问题
						temp[i] = _start[i];
					}
				}
				delete[] _start;

				_start = temp;
				_finish = _start + old;
				_end_of_storage = _start + num;
			}
		}

		void resize(size_t n, T val = T()) {
			if (n > size()) {
				reserve(n);
				while (_finish < _start + n) {
					*_finish = val;
					++_finish;
				}
			}
			else {
				_finish = _start + n;
			}
		}

		iterator erase(iterator pos) {
			assert(pos >= _start && pos <= _finish);
			iterator it = pos + 1;
			while (it < _finish) {
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			
			return pos;
		}

		void push_back(const T& x) {
			if (_finish == _end_of_storage) {
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}

			*_finish = x;
			++_finish;
		}

		void pop_back() {
			assert(size() > 0);
			--_finish;
		}

		iterator insert(iterator pos, const T& x) {
			assert(pos >= begin() && pos <= end());
			if (_finish == _end_of_storage) {
				//如果出现扩容情况，reserve会释放旧空间，pos不进行数据更新会导致pos指向原来空间的位置，导致报错
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			
			/*memmove(pos + 1, pos, sizeof(T) * (_finish - pos));*/ //同样存在浅拷贝问题
			iterator end = _finish - 1;
			while (end >= pos) {
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}

		T& operator[](size_t pos) {
			assert(pos < size());
			return _start[pos];
		}

		const T& operator[](size_t pos) const{
			assert(pos < size());
			return _start[pos];
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	void Test_1() {
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.insert(v.begin(), 100);
		v.insert(v.begin() + 2, 100);
		/*vector<int>::iterator it = v.begin();
		while (it != v.end()) {
			cout << *it << " ";
			++it;
		}*/
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}

	void Test_2() {
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);
		v1.push_back(1);

		vector<int> v2 = v1;
		for (int i = 0; i < v2.size(); i++) cout << v2[i] << " ";
		cout << endl;
	}

	void Test_3() {
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		v.push_back(7);

		for (auto x : v) {
			cout << x << " ";
		}
		cout << endl;

		v.resize(8);
		for (auto x : v) {
			cout << x << " ";
		}
		cout << endl;

		v.resize(15, 2);
		for (auto x : v) {
			cout << x << " ";
		}
		cout << endl;

		v.resize(2);
		for (auto x : v) {
			cout << x << " ";
		}
		cout << endl;
	}

	void Test_4() {
		vector<int> nums;
		nums.push_back(1);
		nums.push_back(2);
		nums.push_back(3);
		nums.push_back(4);
		nums.push_back(5);
		nums.push_back(6);

		for (auto x : nums) {
			cout << x << " ";
		}
		cout << endl;

		vector<int>::iterator it = nums.begin();
		while (it != nums.end()) {
			if (*it % 2 == 0) it = nums.erase(it);
			else ++it;
		}
		for (auto x : nums) {
			cout << x << " ";
		}
		cout << endl;
	}

	void Test_5() {
		vector<string> v;
		v.push_back("hello");
		v.push_back("hello");
		v.push_back("hello");
		v.push_back("hello");
		v.push_back("hello");
		v.push_back("hello");

		for (auto& s : v) {
			cout << s << " ";
		}
		cout << endl;
	}

	void Test_6() {
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);
		v1.push_back(7);

		vector<int> v2(v1.begin(), v1.end());
		for (int i = 0; i < v2.size(); i++) cout << v2[i] << " ";
		cout << endl;
	}
}