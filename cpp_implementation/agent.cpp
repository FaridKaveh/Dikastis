#include <iostream> 
#include <vector> 
#include <algorithm> 
#include "agent.h"
#include "helper.cpp"
#include <functional>
#include <math.h> 
#include <random> 


void Agent::update_range(int no_data_points){ 
	/*Part of the dynamic range implementation. Gets rid of the tail ends of competence range if the tail probability is
	 * very small. Iterating forward, checks if the entries of comp_dens_arr are very small (10E-6 or smaller) and 
	 * erases them of they are. If a certain element reached  has values above this, then we are no longer in the 'tail',
	 * so stops removing elements. Does the same procedure iterating in reverse. */
	int n = comp_dens_arr.size(); 
	if (no_data_points > 10) {
		std::vector<double>::iterator dens_it = comp_dens_arr.begin(); 
		std::vector<double>::iterator comp_it = comp_arr.begin(); 
			//first loop removes tail from the left	
       		while (dens_it != comp_dens_arr.end()){ 
				if (*dens_it <= std::pow(10, -5)*1/(double)n) { 
					dens_it = comp_dens_arr.erase(dens_it);
					comp_it = comp_arr.erase(comp_it); 
					
				} 
				else break; 
			}

		std::vector<double>::reverse_iterator dens_rit = comp_dens_arr.rbegin();
	        std::vector<double>::reverse_iterator comp_rit = comp_arr.rbegin();
		// second loop removes rail from the right 	
		while (dens_rit != comp_dens_arr.rend()) {
			if (*dens_rit <= std::pow(10, -5) * 1/(double)n) {
			        // erase method does not take reverse_iterators, hence this workaround. 
				dens_rit = decltype(dens_rit)(comp_dens_arr.erase((dens_rit+1).base()));
				comp_rit = decltype(comp_rit)(comp_arr.erase((comp_rit +1).base()));

				
			}

			else break; 
	
		}
		
		/* we now refill comp_arr and comp_dens_arr with steps in between each of the old increments such that 
		the new vectors have the same size as the old ones*/
		int new_steps = (n-comp_dens_arr.size())/(comp_dens_arr.size()-1); 
		std::cout << "new steps: " << new_steps << std::endl;
		
		// This next block is a mess of iterators and it barely works. Do not touch. 
		if (new_steps > 0) { 

			epsilon = (comp_arr[1] - comp_arr[0])/(double)new_steps; 
			std::cout << "epsilon = " << epsilon << std::endl;
			std::vector<double> insert_vec;
			for (int k = 0; k < comp_dens_arr.size() - 1; k += new_steps){ 
				std::vector<double>::reverse_iterator it_dens = comp_dens_arr.rbegin() + k;
				std::vector<double>::reverse_iterator it_comp = comp_arr.rbegin() + k;
				insert_vec = populate_vector(*it_comp, epsilon, new_steps); 
				std::vector<double>::iterator forward_dens_it = (it_dens + 1).base();
				std::vector<double>::iterator forward_comp_it = (it_comp +1).base();
				comp_arr.insert(forward_comp_it, insert_vec.rbegin(),insert_vec.rend()); 
				double val = *(it_dens);
				comp_dens_arr.insert(forward_dens_it, new_steps-1, val);
			}

		}
		min_comp = *comp_arr.begin(); max_comp = *(comp_arr.end()-1);
		//renormalising the density arr
		double renormalise; 
		for (auto& elem: comp_dens_arr) renormalise += elem;
		std::transform(comp_dens_arr.begin(), comp_dens_arr.end(), comp_dens_arr.begin(), std::bind(std::multiplies<double>(), std::placeholders::_1, 1/renormalise));
 	
		
	}	
}

Agent::Agent(){ 
	// default constructor for agent. Sets the competence range to [-5,5]
	delta = 0.1; 
	epsilon = delta;
	max_comp = 10; min_comp = -max_comp; 
	double intervals = (max_comp-min_comp)/epsilon;	
	for (int i = 0; i < intervals+1; i++) comp_arr.push_back(min_comp+i*epsilon); 
			

	comp_dens_arr.assign(comp_arr.size(), 1/(double)comp_arr.size()); 
}
	/*update_dens updates the competence probability density according to the 'choice' made from 'eval'.
	 It's a simple application of Bayes*/
double Agent::get_skill(){
	double skill = 0;  
	for (int i = 0; i < comp_arr.size(); i++) skill += comp_arr[i]*comp_dens_arr[i]; 
       return skill;	
}
void Agent::update_dens(std::vector<double> evals, int choice){ 

	auto  v_max = max_element(evals.begin(), evals.end());
	double K = sqrt(2.0) - 1.0; std::vector<double> cond_prob_arr;
       	double base = *v_max - evals[choice] + K;	
	
	//conditional probability of competence given choice from evals was observed
	for (std::vector<double>::iterator it = comp_arr.begin(); it != comp_arr.end(); it++) {
		cond_prob_arr.push_back(pow(base, -(*it)));
	}

	
	double normalisation = 0;

	//update comp_dens_arr given conditional probabilities
	for (int i = 0; i < comp_dens_arr.size(); i++){
	       	comp_dens_arr[i] = comp_dens_arr[i] * cond_prob_arr[i]; 
		normalisation += comp_dens_arr[i];	
	}	
	std::transform(comp_dens_arr.begin(), comp_dens_arr.end(), comp_dens_arr.begin(), 
		std::bind(std::multiplies<double>(), std::placeholders::_1, 1/normalisation));
} 
 
