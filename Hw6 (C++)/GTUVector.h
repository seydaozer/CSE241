#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include<memory>
#include<iostream>

#include "GTUContainer.h"

#include<stdexcept>
using std::bad_alloc;

namespace SEYDA_STL{

	template<class T>
	class GTUVector : public GTUContainer<T>{
	public:
		//Constructures
		GTUVector();
		GTUVector(int max_size);

		void operator=(const GTUVector& other);

		bool empty() const override;
		int size() const override;
		int max_size() const override;
		GTUIterator<T> insert(GTUIterator<T>& index, const T& element) throw(bad_alloc);
		GTUIterator<T> erase(GTUIterator<T>& index) override;
		void clear()  override;
		GTUIterator<T> begin() const override;
		GTUIterator<T> end() const override;
		T operator[](int index) const;

		//helper function
		void addElement(const T element);

	private:
		int used;
		int capacity;
		bool _empty;
		shared_ptr<T> _vector;
	};

}

#endif //GTUVECTOR_H

