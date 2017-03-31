#ifndef COMPARE_H
#define COMPARE_H
//done
#include "Compare.h"

class compare_illness { //determines which patient has greatest illness/ high priority
public:
		bool operator() (Patient* P1, Patient* P2) {
		return (P1->get_illness() < P2->get_illness());
	}
};
class compare
{
public: 
	bool operator() (Patient* p1, Patient* p2) { // who will be out fastest
		return (p1->get_surgery_time() > p2->get_surgery_time());
	}
};
#endif