#include "Simulator.h"



int main()
{
	//Simulator hospital;
	Simulator sim; 
	sim.menu_a();// asks for doc and nurse numbers
	sim.run_Simulation();// runs actual simulation
	sim.menu_b(); /// outputs info
}