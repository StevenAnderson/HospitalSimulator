#ifndef TREATMENTQUEUE_H
#define TREATMENTQUEUE_H

#include <queue>
#include <iostream>
#include <map>
#include "Patient.h"
#include "PatientQueue.h"
#include "Compare.h"
#include "Random.h"
#include "DoctorNurse.h"
extern Random  random_1;

class Treatment_Queue // queue of people getting treated in the moment
{
private:
	Waiting_Queue *Wait;
	std::priority_queue<Patient*, std::deque<Patient*>, compare> patients;
	std::map<std::string, int >records; // stores past patients (some patients will be in more than once
	std::vector<std::string> pastpaish;
	Doctor* doctor;
	Nurse* nurse;

	int tot_treat;
	int tot_wait;
	int num_doc;
	int num_nur;
	int doc_in_sur;
	int nur_in_sur;


public:


	std::map<std::string, int> get_rekt() {
		return records;
	}
	
	std::vector<std::string> get_pastpaish()
	{
		return pastpaish;
	}

	Treatment_Queue() {
		tot_treat = 0;
		tot_wait = 0;
		doc_in_sur = 0;
		nur_in_sur = 0;

		nurse = new Nurse();
		doctor = new Doctor();

	}

	void set_docs(int docs) {
		num_doc = docs;
	}
	void set_nurs(int t) {
		num_nur = t;
	}
	void set_wait(Waiting_Queue *wait) {
		Wait = wait;
	}
	int get_treated	() {
		return tot_treat;
	}

	int get_wait() {
		return tot_wait;
	}
	int get_num_doc() {
		return num_doc;
	}
	int get_num_nur() {
		return num_nur;
	}
	int get_doc_busy() {
		return doc_in_sur;
	}
	int get_nur_busy() {
		return nur_in_sur;

	}
	bool empty(Waiting_Queue wait) {
		if (wait.get_size() != 0)
			return false;
		else
			return true;
	}


	void add(int clock) {
		if (Wait->get_size()!=0 || clock<60) // gives patients to available docs or nurses
		//future improvment, for faster times, only allow docs to work on high severity patients
		{
			if (num_doc + num_nur > doc_in_sur + nur_in_sur) {
				Patient *p = Wait->Front();
				if (p->get_illness() <= 10 && num_nur > nur_in_sur) {
					nur_in_sur++;
					nurse->Treat(clock, p);
					patients.push(p);
					tot_wait += p->get_startsurgery() - p->get_arrival_time();
					Wait->Pop();
				}
				else if (p->get_illness() <= 10 && num_nur == nur_in_sur && doc_in_sur<num_doc) {
					doc_in_sur++;
					doctor->Treat(clock, p);
					patients.push(p);
					tot_wait += p->get_startsurgery() - p->get_arrival_time();
					Wait->Pop();
				}
				else if (p->get_illness() > 10 && num_doc > doc_in_sur) {
					doc_in_sur++;
					doctor->Treat(clock, p);
					patients.push(p);
					tot_wait += p->get_startsurgery() - p->get_arrival_time();
					Wait->Pop();
				}
			}
		} 
		if (!patients.empty()) { 
			while (!patients.empty() && (clock >= patients.top()->get_startsurgery()+patients.top()->get_surgery_time())) {
				if (patients.top()->get_doctor()) {
					doc_in_sur--;
				}
				else if (!patients.top()->get_doctor())
					nur_in_sur--;


				records.insert(std::make_pair(patients.top()->get_name(), patients.top()->get_illness()));
				pastpaish.push_back(patients.top()->get_name());
				tot_treat++;
				patients.top()->set_total_time(clock);
				//tot_wait += clock - patients.top()->get_startsurgery();
				patients.pop();



			}
		}
	}
	friend class PatientQueue;

};

#endif
