#ifndef DOCTORNURSE_H
#define DOCTORNURSE_H
#include "Patient.h"
//done

#include "Patient.h"
#include "Random.h"

extern Random random1;

class DoctorNurse{

private:

public:
	DoctorNurse() {} // both doc and nurse Treat people

	virtual void Treat(int clock, Patient* P) = 0; 

};

class Doctor:DoctorNurse { // doc takes longer to treat
							// but can treat people of higher severity


private:

public:
	Doctor() {}
	void Treat(int clock, Patient* p) {
		p->set_doctor(true);
		p->set_startsurgery(clock);
	//	p->set_arrival_time(clock);
		p->set_surgery_time(random_1.next_int(19) + 1);
	}

};

class Nurse : DoctorNurse {

private:
public:
	Nurse() {}

	void Treat(int clock, Patient* p) {
		p->set_doctor(false);  // not a doc
		p->set_startsurgery(clock);
	//	p->set_arrival_time(clock);
		p->set_surgery_time(random_1.next_int(9) + 1); //fast treat times
	}



};

#endif
