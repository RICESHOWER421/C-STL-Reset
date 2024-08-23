#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <iterator>
#include <cassert>
using namespace std;

class MyString {
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	MyString(const char* str = "") {
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	//传统写法
	/*MyString(const MyString& str) {
		_str = new char[str._capacity + 1];
		strcpy(_str, str._str);
		_size = str._size;
		_capacity = str._capacity;
	}*/

	//现代写法
	MyString(const MyString& str) {
		MyString temp(str._str);
		swap(temp);
	}

	const char* c_str() const{
		return _str;
	}

	size_t size() const{
		return _size;
	}

	iterator begin() const{
		return _str;
	}

	iterator end() const {
		return _str + _size;
	}

	const char& operator[](size_t pos) const{
		assert(pos <= _size);
		return _str[pos];
	}

	char& operator[](size_t pos) {
		assert(pos <= _size);
		return _str[pos];
	}
	
	void reserve(size_t num) {
		if (num > _capacity) {
			char* temp = new char[num + 1];
			strcpy(temp, _str);
			delete[] _str;
			_str = temp;
			_capacity = num;
		}
	}

	void push_back(char ch) {
		if (_size == _capacity) {
			size_t new_capacity = _capacity == 0 ? 4 : _capacity * 2;
			reserve(new_capacity);
		}

		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	void append(const char* str) {
		size_t len = strlen(str);
		if (_size + len > _capacity) {
			reserve(_size + len);
		}

		strcpy(_str + _size, str);
		_size += len;
	}

	MyString& operator+=(char ch) {
		push_back(ch);
		return *this;
	}

	MyString& operator+=(const char* str) {
		append(str);
		return *this;
	}

	//传统写法
	MyString& operator=(const MyString& str) {
		if (this != &str) {
			char* temp = new char[str._capacity + 1];
			strcpy(temp, str._str);
			delete[] _str;

			_str = temp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	
	//现代写法
	/*MyString& operator=(MyString str) {
		swap(str);
		return *this;
	}*/

	//this->c_str() << cout 所以这样写是不可以的
	/*ostream& operator<<(ostream& cout) {
		cout << this->c_str();
		return cout;
	}*/

	void insert(size_t pos, char ch){
		assert(pos <= _size);

		if (_size == _capacity) {
			size_t new_capacity = _capacity == 0 ? 4 : _capacity * 2;
			reserve(new_capacity);
		}

		size_t end = _size + 1;
		while (end > pos) {
			_str[end] = _str[end - 1];
			--end;
		}

		_str[pos] = ch;
		++_size;
	}

	void insert(size_t pos, const char* str) {
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity) {
			reserve(_size + len);
		}

		size_t end = _size + len;
		while (end > pos) {
			_str[end] = _str[end - len];
			--end;
		}

		strncpy(_str + pos, str, len);
		_size += len;
	}

	void erase(size_t pos, size_t len = npos) {
		assert(pos < _size);

		if (len == npos || pos + len >= _size) {
			_str[pos] = '\0';
			_size = pos;
		}
		else {
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}
	}

	void swap(MyString& str) {
		std::swap(_str, str._str);
		std::swap(_capacity, str._capacity);
		std::swap(_size, str._size);
	}

	size_t find(char ch, size_t pos = npos) const{
		for (int i = pos; i < _size; i++) {
			if (ch == _str[i]) return i;
		}

		return npos;
	}

	size_t find(const char* str, size_t pos = 0) {
		const char* ptr = strstr(_str + pos, str);
		if (ptr) return ptr - _str;
		else return npos;
	}

	MyString substr(size_t pos = 0, size_t len = npos) {
		assert(pos < _size);
		size_t end = pos + len;
		if (len == npos || pos + len >= _size) { //如果字串接触到主串末尾
			end = _size;
		}

		MyString temp;
		temp.reserve(end - pos);
		for (size_t i = pos; i < end; i++) {
			temp += _str[i];
		}

		return temp;
	}

	void clear() {
		_str[0] = '\0';
		_size = 0;
	}

	~MyString() {
		delete[] _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
	static size_t npos;
};

ostream& operator<<(ostream& out, const MyString& str) {
	cout << str.c_str();
	return cout;
}

//istream& operator>>(istream& cin, MyString& str) {
//	if (str.size() != 0) 
//		str.clear();
//
//	char ch = cin.get();
//	while (ch != ' ' && ch != '\n') {
//		str += ch;
//		ch = cin.get();
//	}
//	return cin;
//}

//优化版本,优化一些空间
istream& operator>>(istream& cin, MyString& str) {
	str.clear();
	char buff[128];
	char ch = cin.get();
	int i = 0;
	while (ch != ' ' && ch != '\n') {
		buff[i++] = ch;
		if (i == 127) {
			buff[i] = '\0';
			str += buff;
			i = 0;
		}

		ch = cin.get();
	}

	if (i > 0) {
		buff[i] = '\0';
		str += buff;
	}

	return cin;
}
size_t MyString::npos = -1;


/*测试案例*/
void Test_1() {
	MyString str = "hello world";
	MyString::const_iterator it = str.begin();
	while (it != str.end()) {
		cout << *it;
		++it;
	}
	cout << endl;

	str += ' ';
	str += "wonderful";
	cout << str.c_str() << endl;

	str.insert(0, "aaaaa");
	cout << str.c_str() << endl;
}

void Test_2(){
	MyString str = "abnsdjsakldjla";
	cout << str.c_str()<< endl;
	cout << str.size() << endl;
	str.erase(5, 5);
	cout << str.c_str() << endl;
	cout << str.size() << endl;

	str.erase(2);
	cout << str.c_str() << endl;
	cout << str.size() << endl;

	/*断言报错*/
	/*str.erase(100);
	cout << str.c_str() << endl;
	cout << str.size() << endl;*/
}

void Test_3() {
	MyString str = "nihaowohaodajiahao";
	size_t temp = str.find("hao");
	cout << temp << endl;
	size_t temp_1 = str.find("jih");
	cout << temp_1 << endl;
}

void Test_4() {
	MyString s1 = "nihao";
	MyString s2 = "dsadjaskdjasljdakls";
	s2 = s1;
	MyString s3(s1);
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
}

void Test_5(){
	MyString s1 = "nihaowohaodajiahao";
	cout << s1.substr(2,5).c_str() << endl;
	cout << s1.substr(2).c_str() << endl;
}

void Test_6() {
	MyString s2 = "hello world\0nihao";
	cout << s2 << endl;
	cout << s2.c_str() << endl;

	s2.clear();
	cout << s2 << endl;
	cout << s2.c_str() << endl;
	/*MyString s3 = "nihao";
	cin >> s3;
	cout << s3 << endl;
	MyString s4;
	cin >> s4;
	cout << s4 << endl;*/
}

void Test_7() {
	MyString s1;
	cin >> s1;
	cout << s1 << endl;

	MyString s2;
	cin >> s2;
	cout << s2 << endl;

	MyString s3;
	cin >> s3;
	cout << s3 << endl;

	MyString s4;
	cin >> s4;
	cout << s4 << endl;
}

//如果使用现代写法的话，s1 = s2语句中s2调用了拷贝构造？？？
void Test_8() {
	MyString s1 = "nihao";
	MyString s2 = "hi";
	s1 = s2;
	cout << s1 << endl;
	cout << s1 << endl;
}