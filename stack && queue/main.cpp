#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "stack.h"
#include "queue.h"

int main() {
	new_stack::stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	while (!st.empty()) {
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;

	new_queue::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	while (!q.empty()) {
		std::cout << q.front() << " ";
		q.pop();
	}
	std::cout << std::endl;

	new_queue::priority_queue<int, std::vector<int>, new_compare::greater<int>> pq;
	pq.push(2);
	pq.push(3);
	pq.push(1);
	pq.push(5);
	pq.push(4);
	pq.push(100);
	pq.push(200);
	pq.push(0);
	while (!pq.empty()) {
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;
	return 0;
}