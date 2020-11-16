#ifndef GTUSET_H
#define GTUSET_H

#include<memory>
#include<iostream>

#include "GTUContainer.h"

#include<stdexcept>
using std::bad_alloc;

namespace SEYDA_STL{

	template<class T>
	class GTUSet: public GTUContainer<T>{
	public:
		//Constructures
		GTUSet();
		GTUSet(int max_size);

		void operator=(const GTUSet& other);

		bool empty() const override;
		int size() const override;
		int max_size() const override;
		GTUIterator<T> insert(GTUIterator<T>& index, const T& element) throw(bad_alloc);
		GTUIterator<T> erase(GTUIterator<T>& index) override;
		void clear() override;
		GTUIterator<T> begin() const override;
		GTUIterator<T> end() const override;
		//helper function
		bool controlElements(const T element) const;
		void addElement(const T element);
	private:
		int used;
		int capacity;
		bool _empty;
		shared_ptr<T> _set;
	};

}

#endif //GTUSET_H

