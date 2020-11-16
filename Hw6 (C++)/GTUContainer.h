#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include<stdexcept>
using std::bad_alloc;

#include "GTUIterator.cpp"

namespace SEYDA_STL{

	template<class T>
	class GTUContainer{
	public:
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual int max_size() const = 0;
		virtual GTUIterator<T> insert(GTUIterator<T>& index, const T& element) throw(bad_alloc) = 0;
		virtual GTUIterator<T> erase(GTUIterator<T>& index) = 0;
		virtual void clear() = 0;
		virtual GTUIterator<T> begin() const = 0;
		virtual GTUIterator<T> end() const = 0;
	};
}

#endif //GTUCONTAINER_H