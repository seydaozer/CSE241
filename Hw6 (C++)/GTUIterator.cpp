#include "GTUIterator.h"
#include<memory>
#include<iostream>

using namespace std;

namespace SEYDA_STL{

	template<class T>
	GTUIterator<T>::GTUIterator() : p(nullptr) { }

	template<class T>
	GTUIterator<T>::GTUIterator(T *i) : p(i) { }

	template<class T>
	GTUIterator<T>::GTUIterator(const GTUIterator<T>& other) : p(other.p) { }

	template<class T>
	void GTUIterator<T>::operator=(const GTUIterator<T>& other){
		if(other.p == p)	return;
		p = other.p;
	}
	
	template<class T>
	T& GTUIterator<T>::operator*() const{
		return *p;
	}
	
	template<class T>
	T& GTUIterator<T>::operator->() const{
		return *p;
	}

	//Preincrement
	template<class T>
	GTUIterator<T>& GTUIterator<T>::operator++(){
		p++;
		return *this;
	}

	//Postincrement
	template<class T>
	GTUIterator<T> GTUIterator<T>::operator++(int i){
		GTUIterator<T> temp(*this);
		p++;
		return temp;
	}
	
	template<class T>
	GTUIterator<T>& GTUIterator<T>::operator--(){
		p--;
		return *this;
	}

	template<class T>
	bool GTUIterator<T>::operator==(const GTUIterator<T>& other) const{
		if(other.p == p)	return true;
		return false;
	}

	template<class T>
	bool GTUIterator<T>::operator!=(const GTUIterator<T>& other) const{
		return !(*this == other);
	}

	//Destructure
	template<class T>
	GTUIterator<T>::~GTUIterator(){
		p = nullptr;
	}
	
}