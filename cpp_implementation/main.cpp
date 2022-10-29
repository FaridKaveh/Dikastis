#include <iostream> 
#include "agent.h" 
#include <random> 
#include <algorithm> 


//random number generator for testing. 
std::random_device rd; //seed for  random generator
std::default_random_engine re(rd()); //random generator
std::uniform_real_distribution<double> one_to_one(-1,0.5); //desired distribution
std::uniform_int_distribution<int> one_to_ten (0,9);

auto evaluation {std::bind(one_to_one, re)}; //bind generator and dist for convienience


int main() { 
	Agent player1;
	player1.get_params(); std::cout << std::endl;
	std::vector<double>  comp_arr = player1.get_comp_arr(); 
        	
	std::vector<double>::iterator zero_it = std::find(comp_arr.begin(), comp_arr.end(), (double)0); 
	int zero_idx = std::distance(comp_arr.begin(), zero_it); 

	std::cout << player1.get_dens_arr()[zero_idx] << std::endl;
	std::vector<double>  evals;
       	for (int j = 0; j <10 ; j++) { 

		for(int i = 0; i < 10; i++) evals.push_back(evaluation());
			
		//int choice = std::distance(evals.begin(),std::max_element(evals.begin(), evals.end())); 
		int choice = one_to_ten(re); 
		std::cout << "Maximum eval was: " << *(std::max_element(evals.begin(),evals.end())) << std::endl;
		std::cout << "choice made was" << evals[choice] << std::endl; 
		player1.update_dens(evals, choice); 
		printf("P(c = 0) = %f \n",player1.get_dens_arr()[zero_idx]); 
	} 
	player1.update_range(11); 
	std::vector<double> dens_arr = player1.get_dens_arr();
	std::vector<double> new_comp_arr = player1.get_comp_arr(); 
	std::cout << "minimum competence is " << new_comp_arr.front() << std::endl; 
	std::cout << "max competence is " << new_comp_arr.back() << std::endl;
	double normalised; 
	for (auto& elem: dens_arr) normalised += elem; 
	std::cout << "density sums to :" << normalised << std::endl; 
	return 0; 
} 
