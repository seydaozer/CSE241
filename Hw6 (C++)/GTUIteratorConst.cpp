#include "GTUIteratorConst.h"
#include<memory>
#include<iostream>

using namespace std;

namespace SEYDA_STL{

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst() : p(nullptr) { }

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(T *i) : p(i) { }

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(const GTUIteratorConst<T>& other) : p(other.p) { }

	template<class T>
	void GTUIteratorConst<T>::operator=(const GTUIteratorConst<T>& other){
		if(other.p == p)	return;
		p = other.p;
	}
	
	template<class T>
	const T& GTUIteratorConst<T>::operator*() const{
		return *p;
	}
	
	template<class T>
	const T& GTUIteratorConst<T>::operator->() const{
		return *p;
	}

	//Preincrement
	template<class T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator++(){
		p++;
		return *this;
	}

	//Postincrement
	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator++(int i){
		GTUIteratorConst<T> temp(*this);
		p++;
		return temp;
	}
	
	template<class T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator--(){
		p--;
		return *this;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator==(const GTUIteratorConst<T>& other) const{
		if(other.p == p)	return true;
		return false;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst<T>& other) const{
		return !(*this == other);
	}

	//Destructure
	template<class T>
	GTUIteratorConst<T>::~GTUIteratorConst(){
		p = nullptr;
	}
	
}