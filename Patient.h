#ifndef PATIENT_H
#define PATIENT_H
////done
#include <string>
#include "Random.h"
extern Random random_1;

class Patient
///all patient info/ variables 
{
private:
	int arrival_time=0; 
	int surgery_time=0;
	int discharge_time=0;
	int total_time=0;
	std::string name;
	bool doctor=true;
	int illness=0;
	int startsurgery = 0;


public:
	Patient(int clock, std::string name) // initializes the patient when they are 'admitted'
	{
		this->name = name;
		arrival_time = clock;
		int rand = random_1.next_int(10) + 1;
		if (rand <= 7)
			illness = random_1.next_int(9) + 1;
		else if (rand > 7 && rand <= 9)
			illness =11+random_1.next_int(4);
		else
			illness = 15+random_1.next_int(4) + 1;

	}
	void set_arrival_time(int clock) { //// All the Gets and Sets
		arrival_time = clock;
	}
	void set_surgery_time(int t) {
		surgery_time = t;
	}
	void set_doctor(bool doc) {
		doctor = doc;
	}
	void set_total_time(int clock) {
		total_time = clock - arrival_time;
	}

	int get_arrival_time() {
		return arrival_time;
	}
	void set_startsurgery(int t) {
		startsurgery = t;
	}

	int get_startsurgery() {
		return startsurgery;
	}
	int get_surgery_time() {
		return surgery_time;
	}
	int get_total_time() {
		return total_time;
	}
	std::string get_name() {
		return name;
	}
	bool get_doctor() {
		return doctor;
	}
	int get_illness() {
		return illness;
	}


};



#endif