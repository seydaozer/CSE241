#include "GTUVector.h"
#include "GTUContainer.h"

#include<iostream>
using namespace std;

#include<stdexcept>
using std::bad_alloc;

namespace SEYDA_STL{
	
	template<class T>
	GTUVector<T>::GTUVector() : used(0), capacity(50), _empty(true){
		_vector = make_shared<T>(capacity);
	}

	template<class T>
	GTUVector<T>::GTUVector(int max_size) : used(0), capacity(max_size), _empty(true){
		_vector = make_shared<T>(capacity);
	}

	//Assignment operator
	template<class T>
	void GTUVector<T>::operator=(const GTUVector<T>& other){
		if(capacity != other.capacity){ // if these vector's capacities are not the same, I resize vector(this->_vector).
			_vector = nullptr;
			_vector = make_shared<T>(other.capacity);
		}

		capacity = other.capacity;
		used = other.used;
		_empty = other._empty;

		GTUIterator<T> iter;
		int i = 0;
		for(iter=other.begin(); iter!=other.end(); ++iter){
			_vector.get()[i] = *iter;
			i++;
		}
		for(iter=this->begin(); iter!=this->end(); ++iter)
			cout << *iter << " ";
	}

	template<class T>
	bool GTUVector<T>::empty() const{
		return _empty;
	}

	template<class T>
	int GTUVector<T>::size() const{
		return used;
	}

	template<class T>
	int GTUVector<T>::max_size() const{
		return capacity;
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::insert(GTUIterator<T>& index, const T& element) throw(bad_alloc){
		if(used >= capacity)
			throw bad_alloc();

		else{
			if ( used == 0)	_empty = false;

			used++;

			GTUIterator<T> iter;
			T temp, value = element;
			for(iter=index; iter!=this->end(); ++iter){
				temp = *iter;
				*iter = value;
				value = temp;
			}

			for(iter=this->begin(); *iter!=element; ++iter);

			return iter;		
			
		}
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::erase(GTUIterator<T>& index){
		bool first_in = true;
		T temp , value;

		--index;
		GTUIterator<T> iter;
		for(iter = this->end(); iter!=index; --iter){
			temp = *iter;
			if(first_in == true){
				used--;
				value = temp;
				first_in = false;
			}
			else{
				*iter = value;
				value = temp;
			}
		}
		++index;

		for(iter=this->begin(); iter!=index; ++iter);

		return iter;	
	}

	template<class T>
	void GTUVector<T>::clear(){
		used = 0;
		_vector = nullptr;
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::begin() const{
		GTUIterator<T> iter;
		iter = _vector.get();
		return iter;
	}

	template<class T>
	GTUIterator<T> GTUVector<T>::end() const{
		GTUIterator<T> iter;
		iter = _vector.get();

		for(auto i=0; i<used; i++)
			++iter;

		return iter;
	}

	template<class T>
	T GTUVector<T>::operator[](int index) const{
		T result;
		for(int i=0; i<=index; i++){
			result = _vector.get()[i];
		}

		return result;
	}

	template<class T>
	void GTUVector<T>::addElement(const T element){

		if( used < capacity ){
			GTUIterator<T> iter;
			if ( used == 0){
				_empty = false;
				iter = this->begin();
				*iter = element;
			}	
			else{
				for(iter=this->begin(); iter!=this->end(); ++iter);
				*iter = element;
			}
			used++;
		}

		else{ // used >= capacity
			GTUIterator<T> iter;
			T temp[capacity];

			int count = 0;
			for(iter=this->begin(); iter!=this->end(); ++iter){
				temp[count] = *iter;
				count++;
			}

			capacity += capacity;
			used = count + 1;

			_vector = nullptr;
			_vector = make_shared<T>(capacity);

			iter = this->begin();

			int i = 0;
			for(int j = count; j>0; j--){
				*iter = temp[i];
				++iter;
				i++;
			}

			*iter = element;
			
			for(iter=this->begin(); iter!=this->end(); ++iter)
				cout << *iter << " ";
		}
	}
}