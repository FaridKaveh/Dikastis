#include <iostream> 
#include <vector> 
#include <algorithm> 
#include "agent.h"

Agent::Agent(){ 
	// default constructor for agent. Sets the competence range to [-3,3]
	delta = 0.1; 
	epsilon = delta;
	max_comp = 3; min_comp = -3; 
	double intervals = (max_comp-min_comp)/epsilon;	
	for (int i = 0; i < intervals; i++) comp_arr.push_back(max_comp-i*epsilon); 
			

	comp_dens_arr.assign(comp_arr.size(), 1/comp_arr.size()); 
		}	

int main() { 
	Agent player1; 
	player1.get_params(); 
	return 0; 
} 
