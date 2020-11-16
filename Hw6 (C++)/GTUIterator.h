#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include<memory>
#include<iostream>

using namespace std;

namespace SEYDA_STL{

	template<class T>
	class GTUIterator{
	public:
		GTUIterator();
		GTUIterator(T *i);
		GTUIterator(const GTUIterator& other);
		T& operator*() const;
		T& operator->() const;
		GTUIterator& operator++();
		GTUIterator operator++(int);
		GTUIterator& operator--();
		bool operator==(const GTUIterator& other) const;
		bool operator!=(const GTUIterator& other) const;
		void operator=(const GTUIterator& other);
		virtual ~GTUIterator();
	private:
		T *p;
	};
}

#endif //GTUITERATOR_H
