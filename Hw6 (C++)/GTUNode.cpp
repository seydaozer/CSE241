#include<iostream>
#include<memory>
#include "GTUNode.h"

using namespace std;

namespace SEYDA_STL{

		GTUNode::GTUNode(){
			this->data=0;
			this->next=nullptr;
			this->prev=nullptr;
		}

}