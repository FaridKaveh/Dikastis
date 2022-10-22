#include <iostream> 
#include <vector> 
#include <algorithm> 
#include "agent.h"
#include <functional>
#include <math.h> 

Agent::update_range(int no_data_points){ 
	int n = comp_dens_arr.size(); 
	if (no_data_points > 10) {
       		for (int i = 0; i < n; i++){ 
			if (comp_dens_arr[i] <= std::pow(10, -5)*1/(double)n) { 
				comp_dens_arr[i] 
			} 
			break; 
		}
		for (std::vector<double>::iterator it = dens_arr.end(), it != dens_arr.begin(), it--){ 
		}	
	}	
}

Agent::Agent(){ 
	// default constructor for agent. Sets the competence range to [-3,3]
	delta = 0.1; 
	epsilon = delta;
	max_comp = 3; min_comp = -3; 
	double intervals = (max_comp-min_comp)/epsilon;	
	for (int i = 0; i < intervals+1; i++) comp_arr.push_back(min_comp+i*epsilon); 
			

	comp_dens_arr.assign(comp_arr.size(), 1/(double)comp_arr.size()); 
		}
double Agent::get_skill(){
	double skill = 0; 
	for (int i = 0; i < comp_arr.size(); i++) skill += comp_arr[i]*comp_dens_arr[i]; 
       return skill;	
}
void Agent::update_dens(std::vector<double> evals, int choice){ 
	/*update_dens updates the competence probability density according to the 'choice' made from 'eval'.
	 It's a simple application of Bayes theorem */
	auto  v_max = max_element(evals.begin(), evals.end());
	double K = 0.01; std::vector<double> cond_prob_arr;
       	double base = *v_max - evals[choice] + K;	
	
	//conditional probability of comp given choice from evals was observed
	for (std::vector<double>::iterator it = comp_arr.begin(); it != comp_arr.end(); it++) {
		cond_prob_arr.push_back(pow(base, -(*it)));
	}

	
	double normalisation = 0;

	//update comp_dens_arr given conditional probabilities
	for (int i = 0; i < comp_dens_arr.size(); i++){
	       	comp_dens_arr[i] = comp_dens_arr[i] * cond_prob_arr[i]; 
		normalisation += comp_dens_arr[i];	
	}	
	std::transform(comp_dens_arr.begin(), comp_dens_arr.end(), comp_dens_arr.begin(), std::bind(std::multiplies<double>(), std::placeholders::_1, 1/normalisation));
} 

int main() { 
	Agent player1;
	player1.get_params(); std::cout << std::endl;
       	std::vector<double> evals = {-1.2, 1.0, 3.7, -2}; 
	int choice = 2; 
	double skill = player1.get_skill(); 
	player1.update_dens(evals, choice); 	
	double skill1 = player1.get_skill();
	std::vector<double> dens_arr = player1.get_dens_arr(); 
	std::cout << skill << "; " << skill1 << std::endl;
	std::cout << dens_arr[0] << "; " << dens_arr[50] << std::endl;
	return 0; 
} 
