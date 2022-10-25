#include <iostream> 
#include "agent.h" 
#include <random> 
#include <algorithm> 


//random number generator for testing. 
std::random_device rd; //seed for  random generator
std::default_random_engine re(rd()); //random generator
std::uniform_real_distribution<double> one_to_one(-1,1); //desired distribution

auto evaluation {std::bind(one_to_one, re)}; //bind generator and dist for convienience


int main() { 
	Agent player1;
	player1.get_params(); std::cout << std::endl;
	std::cout << player1.get_comp_arr().size() << std::endl; 
       	std::cout << player1.get_dens_arr()[50] << std::endl;	
	std::vector<double>  evals;
       	for (int j = 0; j <10 ; j++) { 

		for(int i = 0; i < 10; i++) evals.push_back(evaluation());
			
		int choice = std::distance(evals.begin(),std::max_element(evals.begin(), evals.end())); 
		player1.update_dens(evals, choice); 
		printf("P(c = %f) = %f \n",player1.get_comp_arr()[99], player1.get_dens_arr()[99]); 
	} 
	player1.update_range(11); 
	std::cout << "minimum competence is " << player1.get_comp_arr()[0] << std::endl; 
	return 0; 
} 
