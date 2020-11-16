#include "GTUContainer.h"
#include "GTUVector.cpp"
#include "GTUSet.cpp"

#include<iostream>
#include<memory>

using namespace std;
using namespace SEYDA_STL;

template <class T>
GTUIterator<T> find(GTUIterator<T> first, GTUIterator<T> last, const T& element);

//template <class T>
//GTUIterator find_if(GTUIterator<T> first, GTUIterator<T> last, UnaryPredicate pred);

//template <class T>
//Function for_each(GTUIterator<T> first, GTUIterator<T> last, Function fn);

template<class T>
void testFunction(T element);

int main(){
	cout << "Please select a type " << endl;
	cout << "1- Vector " << endl;
	cout << "2- Set " << endl;
	int choice;
	cin >> choice;

	
	if(choice == 1){ //GTUVECTOR
		GTUVector<double> v1(5); // one-parameter constructure

		if( v1.empty() )	cout << "This vector is empty." << endl;
		else	cout << "This vector is not empty. It's size: " << v1.size() << endl;
		 
		v1.addElement(1.2);
		v1.addElement(2.3);
		v1.addElement(3.4);

		if( v1.empty() )	cout << "This vector is empty." << endl;
		else	cout << "This vector is not empty. It's size: " << v1.size() << endl;

		try{
			GTUIterator<double> it = v1.begin();
			++it;
			it = v1.insert(it, 1.5);
			for(GTUIterator<double> iter = v1.begin(); iter!=v1.end(); ++iter)
				cout << *iter << " ";
			cout << endl;
		}

		catch(bad_alloc){
			cout << "---------------------" << endl;
				cout << "Your vector is full!!" << endl << "The capacity is " << v1.max_size() << "." << endl;
			cout << "---------------------" << endl;
		}

		cout << "I want to erase this element: " << v1[1] << endl;
		GTUIterator<double> it = v1.begin();
		it.operator++(1);
		it = v1.erase(it);
		for(GTUIterator<double> iter = v1.begin(); iter!=v1.end(); ++iter)
			cout << *iter << " ";
		cout << endl;


		GTUVector<double> v2; // no-parameter constructure
		v2 = v1; // probably transferring of the adress of v1 causes an error
		for(GTUIterator<double> iter = v2.begin(); iter!=v2.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
		}

	else if(choice == 2){ //GTUSET
		GTUSet<double> s1(5); // one-parameter constructure

		if( s1.empty() )	cout << "This set is empty." << endl;
		else	cout << "This set is not empty. It's size: " << s1.size() << endl;
		 
		s1.addElement(1.2);
		s1.addElement(2.3);
		s1.addElement(3.4);

		if( s1.empty() )	cout << "This set is empty." << endl;
		else	cout << "This set is not empty. It's size: " << s1.size() << endl;

		try{
			GTUIterator<double> i = s1.begin();
			++i;
			i = s1.insert(i, 1.5);
			for(GTUIterator<double> iter = s1.begin(); iter!=s1.end(); ++iter)
				cout << *iter << " ";
			cout << endl;
		}

		catch(bad_alloc){
			cout << "---------------------" << endl;
			cout << "Your set is full!!" << endl << "The capacity is " << s1.max_size() << "." << endl;
			cout << "---------------------" << endl;
		}

		GTUIterator<double> i = s1.begin();
		i.operator++(1);
		cout << "I want to erase this element: " << *i << endl;
		i = s1.erase(i);
		for(GTUIterator<double> iter = s1.begin(); iter!=s1.end(); ++iter)
			cout << *iter << " ";
		cout << endl;

		GTUSet<double> s2; // no-parameter constructure
		s2 = s1; // probably transferring of the adress of v1 causes an error
		for(GTUIterator<double> iter = s2.begin(); iter!=s2.end(); ++iter)
			cout << *iter << " ";
		cout << endl;
	}
	
	return 0;
}

template <class T>
GTUIterator<T> find(GTUIterator<T> first, GTUIterator<T> last, const T& element){
	while(first != last){
		if(*first == element)	return first;
		++first;
	}
	return last;
}


/*template <class T>
GTUIterator<T> find_if(GTUIterator<T> first, GTUIterator<T> last, UnaryPredicate pred){
	while(first != last){
		if(pred(*first))	return first;
		++first;
	}
	return last;
}*/

/*template <class T>
Function for_each(GTUIterator<T> first, GTUIterator<T> last, Function fn){
	while(first != last){
		fn(*first);
		++first;
	}
	return fn;
}*/

template<class T>
void testFunction(T element){
	cout << " " << element << " ";
}
