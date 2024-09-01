#pragma once
template<class Iterator, class Ref, class Ptr>
struct Reverse_iterator {
	typedef Reverse_iterator<Iterator, Ref, Ptr> Self;

	Reverse_iterator(Iterator it)
		:cur(it) {}

	Iterator cur;
	Self& operator++() {
		--cur;
		return *this;
	}

	Self operator++(int) {
		Self temp = cur;
		--cur;
		return *temp;
	}

	Self& operator--() {
		++cur;
		return *this;
	}

	Self operator--(int) {
		Self temp = cur;
		++cur;
		return *temp;
	}

	Ref operator*() {
		Iterator temp = cur;
		--temp;
		return *temp;
	}

	Ptr operator->() {
		return &(operator*());
	}

	bool operator!=(const Self& s) {
		return cur != s.cur;
	}

	bool operator==(const Self& s) {
		return cur != s.cur;
	}
};