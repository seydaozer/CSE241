#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include<memory>
#include<iostream>

using namespace std;

namespace SEYDA_STL{

	template<class T>
	class GTUIteratorConst{
	public:
		GTUIteratorConst();
		GTUIteratorConst(T *i);
		GTUIteratorConst(const GTUIteratorConst& other);
		const T& operator*() const;
		const T& operator->() const;
		GTUIteratorConst& operator++();
		GTUIteratorConst operator++(int);
		GTUIteratorConst& operator--();
		bool operator==(const GTUIteratorConst& other) const;
		bool operator!=(const GTUIteratorConst& other) const;
		void operator=(const GTUIteratorConst& other);
		virtual ~GTUIteratorConst();
	private:
		T *p;
	};
}

#endif //GTUITERATORCONST_H
