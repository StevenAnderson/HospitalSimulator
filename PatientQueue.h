#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H

#include <iostream>
#include <string>
#include <queue>
#include "Patient.h"
#include "Random.h"
#include "Compare.h"
#include "TreatmentQueue.h"

class Patient_Queue // creates the queue for all patients and their vars
{
private:
	std::string name;

public:
	Patient_Queue(std::string str) { 
		name = str;
	}
};


	class Waiting_Queue : Patient_Queue 
	{
	private:
		std::priority_queue<Patient*, std::vector<Patient*>, compare_illness>patients; 
		int counter = 0;
	public:
		

		Waiting_Queue(std::string name) : Patient_Queue(name) {}

		void add(int clock, std::string name) {
			Patient *p = new Patient(clock, name);
			patients.push(p);
			counter++;
		}
		int get_size() {
			return patients.size();

		}
		Patient* Front() {
			return patients.top();

		}
		void Pop() {
			patients.pop();

		}
		int get_totalhosp() {
			return counter;
		}


};

#endif
