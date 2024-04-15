#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>
#include <concepts>


template<
	class T,
	std::size_t N

>class My_Array
{
private:
	size_t m_length{};
	T* m_data{};

public:
	using value_type = T;
	using size_type = size_t;
	using reference = T&;
	using pointer = T*;
	My_Array() = default;

	My_Array(size_t length)
		: m_length{ length }
		, m_data{ new T/*[static_cast<std::size_t>(length)]*/ {} }
	{

	}

	//My_Array(std::initializer_list<T> list)  // allow My_Array to be initialized via list initialization
	//	: My_Array(static_cast<T>(list.size())) // use delegating constructor to set up initial array
	//{
	//	// Now initialize our array from the list
	//	size_t count{ 0 };
	//	for (auto element : list)
	//	{
	//		m_data[count] = element;
	//		++count;
	//	}
	//}

	/*~My_Array()
	{
		delete[] m_data;
	}*/

	//	My_Array(const My_Array&) = delete; // to avoid shallow copies
	//	My_Array& operator=(const My_Array& list) = delete; // to avoid shallow copies

	T& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	/*My_Array<T, N>& operator=(  My_Array<T, N>&& r) {
		//this->~My_Array();
		for (int i = 0; i < N; i++)
			this[i] = r[i];
		return *this;
	}*/

	size_t size() const { return m_length; }
	size_t maxsize() const { return N; };
	size_t at(size_t index) {

		if (index >= this->size())
			// throw std::out_of_range("Значение не найдено в контейнере");
			std::cout << "OSIBKA;";
		else return m_data[index];
	}
public:
	struct Iterator {
		friend class Container;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;  // or also value_type*
		using reference = T&;  // or also value_type&
	public:
		Iterator(const My_Array<T, N>& array, T* ptr) : current_(ptr), array_(array) {}
		void Swap(Iterator& other) {
			pointer temp = this->m_ptr;
			this->m_ptr = other.m_ptr;
			other.m_ptr = temp;
		}
		reference operator*() const { return *current_; }
		Iterator& operator++() {
			if (current_ < array_.m_data + array_.m_length) {
				++current_;
			}
			return *this;
			
		}
		reference operator[](int n) { return *(this + n); }
		// Post-increment operator (unused but provided for completeness)
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		Iterator& operator--() {
			if (current_ < array_.m_data + array_.m_length) {
				--current_;
			}
			return *this;
		}

		// Post-increment operator (unused but provided for completeness)
		Iterator operator--(int) {
			Iterator temp = *this;
			--(*this);
			return temp;
		}
		Iterator& operator+=(Iterator& other) {
			difference_type m = other;
			if (m >= 0) while (m--) ++this;
			else while (m++) --this;
			return this;
		}
		Iterator operator+(Iterator& other) {
			Iterator temp = this;
			return temp += other;
		}
		Iterator& operator-=(Iterator& other) {
			return this += -other;
		}
		Iterator operator-(Iterator& other) {
			Iterator temp = this;
			return temp -= other;
		}


	private:
		pointer current_;
		const My_Array<T, N>& array_;
		friend Iterator operator+(Iterator it, difference_type n) { return it += n; }
		friend Iterator operator+(difference_type n, Iterator it) { return it += n; }
		friend Iterator operator-(Iterator it, difference_type n) { return it -= n; }
		friend difference_type operator-(const Iterator& a, const Iterator& b) { return a.current_ - b.current_; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.current_ == b.current_; }
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.current_ != b.current_; }
		friend bool operator< (const Iterator& a, const Iterator& b) { return a.current_ < b.current_; }
		friend bool operator> (const Iterator& a, const Iterator& b) { return a.current_ > b.current_; }
		friend bool operator<= (const Iterator& a, const Iterator& b) { return a.current_ <= b.current_; }
		friend bool operator>= (const Iterator& a, const Iterator& b) { return a.current_ >= b.current_; }
	};
	bool operator==(const Iterator& other) const {
		return this->size() == other.size();
	}
	bool operator<(const Iterator& other) const {
		return this->size() < other.size();
	}
	bool operator>(const Iterator& other) const {
		return this->size() > other.size();
	}
	bool operator>=(const Iterator& other) const {
		return !(this->size() < other.size());
	}
	bool operator<=(const Iterator& other) const {
		return !(this->size() > other.size());
	}



	// Comparison operator to check if iterators point to different elements
	bool operator!=(const Iterator& other) const {
		return !(*this == other);
	}
	Iterator begin() const { return Iterator(*this, m_data); }
	Iterator end() const { return Iterator(*this, m_data + m_length); }
	Iterator cbegin() const { return Iterator(m_data); }
	Iterator cend() const { return Iterator(m_data + m_length); }


	bool empty() {
		return(this->begin() == this->end());
	}
	T front() {
		return *this->begin();
	}
	T back() {
		return m_data[this->size() - 1];

	}
	T data() {
		if (this->size)
			return this->begin();
		else return nullptr;
	}
	void fill(const T& value)  /*requires number<T>*/ {
		for (std::size_t i = 0; i < m_length; ++i) {
			m_data[i] = value;
		}
	}
	void swap(My_Array<T, N>& arr1) {
		if (this != &arr1) {
			for (std::size_t i = 0; i < N; ++i) {
				std::swap(m_data[i], arr1.at(i));
			}
			std::swap(this->m_length, arr1.m_length);
		}
	}
	void push(T value) {
		if (this->size() == 0)
			m_data = new T;
		if (this->size() < this->maxsize()) {
			int i = this->size();
			//std::cout << this->size();
			this->m_data[i] = value ;
			this->m_length++;
		}
	}
	void erase(size_t index) {

		if (index < 0 || index >= this->size()) {
			return;
		}


		for (size_t i = index; i < this->size() - 1; ++i) {
			m_data[i] = m_data[i + 1];
		}


		--m_length;
	}


public:


};