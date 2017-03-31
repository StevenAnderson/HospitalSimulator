#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <map>
#include <ctime>
#include <queue>
#include <vector>
#include "Patient.h"
#include "TreatmentQueue.h"
#include "PatientQueue.h"


#include "Random.h"


Random random_1;
using std::cout;

class Simulator // has all the queues and sets clock and patients
{
private:
	Treatment_Queue *treatment;
	Waiting_Queue *wait;
	std::vector<std::string> residents;
	int clock;
	double arrival_rate;
	std::vector<Patient*> patients;
public:

	Simulator() {
		clock = 0;
		std::ifstream names("residents_273ville.txt");

		std::string name;
		while (!names.eof()) {
			names >> name;
			residents.push_back(name);
		}
		treatment = new Treatment_Queue();
		wait = new Waiting_Queue(name);
	}
	int waittime = 0;
	void run_Simulation() // funct to add new patients to hospital
	{
		for (int i = clock; i < 10080;i++)
		{
			if (random_1.next_double() < arrival_rate)
			{
				wait->add(i, residents[random_1.next_int(residents.size() - 1)]);
				treatment->add(i);
			}
		}

		for (int j = 0; j < wait->get_size();j++) {
			Patient *p = wait->Front();
			waittime += 10080 - p->get_arrival_time();
			wait->Pop();
		}	
	}

	void menu_b()  // last menu, displays all the analysis information
	{
		cout << "\nThe Hospital served " << treatment->get_treated() << " people." << std::endl;
		cout << "They waited a total of " << treatment->get_wait() << " minutes." << std::endl;
		cout <<  wait->get_totalhosp() - treatment->get_treated() << " people were still in line at the end of the week." << std::endl;
		cout << "Each person waited an average time of " << (((treatment->get_wait() + waittime) / wait->get_totalhosp())) << " minutes." << std::endl;
	 
		std::string name;
		bool exit = true;
		int choice = 0;
		auto p = 0;
		//auto P = "";
		std::vector<std::string> pastpaish = treatment->get_pastpaish();
		
		while (exit)
		{
			cout << "1. List all treated patients.\n2. Search for a patient\n3. Exit \n";
			std::cin >> choice;
			switch (choice) {
			case 1:
				for (int i = 0; i < pastpaish.size(); i++)
				{
					cout << pastpaish[i] << std::endl;
				}
			
				break;
			case 2:
				cout << "\nWhat patient would you like to look up? " << std::endl;
				std::cin >> name;
				cout << "\n" << name << " went to the emergency room " << treatment->get_rekt().count(name) << " times.\n\n";
				for (auto& p : treatment->get_rekt()) {
					if (p.first == name)
						cout << name << " had an illness severity of " << p.second << std::endl;
				}
				break;
			case 3:
				exit = false;
				cout << std::endl;
				break;
			default:
				cout << "\nFailure\n";
			}
		}
	}

	void menu_a() // first menu displayed, determines the counts of nurses and docs to be used
	{
		std::cout << "Hospital Simulation\n";
		cout << "How many patients come every hour? ";

		int hourly_rate;
		std::cin >> hourly_rate;
		arrival_rate = hourly_rate / 60.0;

		int num_doctors = 0;
		int num_nurses = 0;

		cout << "\nHow many doctors do you want to simulate: ";
		std::cin >> num_doctors;
		cout << "\nHow many nurses do you want to simulate: ";
		std::cin >> num_nurses;

		treatment->set_wait(wait);
		treatment->set_docs(num_doctors);
		treatment->set_nurs(num_nurses);

	}

};

#endif