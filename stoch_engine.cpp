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

void Agent::update_dens(std::vector<double> evals, int choice){ 
	/*update_dens updates the competence probability density according to the 'choice' made from 'eval'.
	 It's a simple application of Bayes theorem */
	double v_max = max_element(evals.begin(), evals.end());
	double K = 0.01; std::vector<double> cond_prob_arr;
       	double base = v_max - evals[choice] + K; 	
	
	//conditional probability of comp given choice from evals was observed
	for (std::vector::iterator it = comp_arr.begin(); it != comp_arr.end(), it++) cond_prob_arr.push_back(base**(-(*it)));    
	
	double normalisation = 0;

	//update comp_dens_arr given conditional probabilities
	for (int i = 0; i < comp_dens_arr.size(); i++){
	       	comp_dens_arr[i] = comp_dens_arr[i] * cond_prob_arr[i]; 
		normalisation += comp_dens_arr[i]	
	}	
	std::transform(comp_dens_arr.begin(), comp_dens_arr.end(), comp_dens_arr.begin(), std::bind(std::multiplies<T>(), std::placeholders::_1, 3));
} 

int main() { 
	Agent player1; 
	player1.get_params(); 
	return 0; 
} 
