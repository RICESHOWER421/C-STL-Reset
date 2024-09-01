#pragma once

namespace new_compare {		//·Âº¯Êý±È½ÏÆ÷
	template<class T>
	class less {
	public:
		bool operator() (const T& x, const T& y) {
			return x < y;
		}
	};

	template<class T>
	class greater {
	public:
		bool operator() (const T& x, const T& y) {
			return x < y;
		}
	};
}

namespace new_queue {
	template<class T, class Container = std::deque<T>>
	class queue {
	public:
		void push(const T& x) {
			_con.push_back(x);
		}

		void pop() {
			_con.pop_front();
		}

		const T& front() {
			return _con.front();
		}

		const T& back() {
			return _con.back();
		}
		size_t size() {
			return _con.size();
		}

		bool empty() {
			return _con.empty();
		}
	private:
		Container _con;
	};

	template<class T, class Container = std::vector<T>, class Compare = new_compare::less<T>>
	class priority_queue {
	public:
		void adjust_up(int child) {	
			Compare cmp;
			int parent = (child - 1) / 2;
			while (child > 0) {
				if (cmp(_con[parent],_con[child])) {
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else break;
			}
		}

		void adjust_down(int parent) {	
			Compare cmp;
			int child = parent * 2 + 1;
	
			while (child < _con.size()) {
				if (child + 1 < _con.size() && cmp(_con[child],_con[child + 1])) ++child;
				if (cmp(_con[parent],_con[child])) {
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else break;
			}
		}

		void push(const T& x) {
			_con.push_back(x);

			adjust_up(_con.size() - 1);
		}

		void pop() {
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}

		const T& top() {
			return _con[0];
		}

		size_t size() {
			return _con.size();
		}

		bool empty() {
			return _con.empty();
		}
	private:
		Container _con;
	};
}