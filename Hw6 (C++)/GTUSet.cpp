#include "GTUSet.h"
#include "GTUContainer.h"

#include<iostream>
using namespace std;

#include<stdexcept>
using std::bad_alloc;

namespace SEYDA_STL{
	
	template<class T>
	GTUSet<T>::GTUSet() : used(0), capacity(100), _empty(true){
		_set = make_shared<T>(capacity);
	}

	template<class T>
	GTUSet<T>::GTUSet(int max_size) : used(0), capacity(max_size), _empty(true){
		_set = make_shared<T>(capacity);
	}

	template<class T>
	void GTUSet<T>::operator=(const GTUSet<T>& other){
		if(capacity != other.capacity){// if these sets's capacities are not the same, I resize vector(this->_set).
			_set = nullptr;
			_set = make_shared<T>(other.capacity);
		}
		capacity = other.capacity;
		used = other.used;
		_empty = other._empty;

		GTUIterator<T> iter;
		int i = 0;
		for(iter=other.begin(); iter!=other.end(); ++iter){
			_set.get()[i] = *iter;
			i++;
		}
	}

	template<class T>
	bool GTUSet<T>::empty() const{
		return _empty;
	}

	template<class T>
	int GTUSet<T>::size() const{
		return used;
	}

	template<class T>
	int GTUSet<T>::max_size() const{
		return capacity;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::insert(GTUIterator<T>& index, const T& element) throw(bad_alloc){
		if(used >= capacity)
			throw bad_alloc();

		else{
			if(controlElements(element) == true ){
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
	}

	template<class T>
	bool GTUSet<T>::controlElements(const T element) const{
		//if the set contains the element, this function returns false because must not add the element to set. 
		GTUIterator<T> iter;
		for(iter=this->begin(); iter!=this->end(); ++iter){
			if(*iter == element) return false;
		}
		return true;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::erase(GTUIterator<T>& index){
		auto first_in = true;
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
	void GTUSet<T>::clear(){
		used = 0;
		_set = nullptr;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::begin() const{
		GTUIterator<T> iter;
		iter = _set.get();
		return iter;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::end() const{
		GTUIterator<T> iter;
		iter = _set.get();

		for(auto i=0; i<used; i++)
			++iter;

		return iter;
	}

	template<class T>
	void GTUSet<T>::addElement(const T element){

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

			_set = nullptr;
			_set = make_shared<T>(capacity);

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