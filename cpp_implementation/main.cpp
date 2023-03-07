#include <iostream> 
#include "agent.h" 
#include <random> 
#include <algorithm> 


//random number generator for testing. 
std::random_device rd; //seed for  random generator
std::default_random_engine re(rd()); //random generator
std::uniform_real_distribution<double> one_to_one(-1,0.5); //desired distribution
std::uniform_int_distribution<int> zero_to_one (1,2);

auto evaluation {std::bind(one_to_one, re)}; //bind generator and dist for convienience


int main() { 
	Agent player1;
	player1.get_params(); std::cout << std::endl;
	std::vector<double>  comp_arr = player1.get_comp_arr(); 
        	
	std::vector<double>::iterator max_it = std::find(comp_arr.begin(), comp_arr.end(), (double)10); 
	int max_idx = std::distance(comp_arr.begin(), max_it); 

	std::cout << player1.get_dens_arr()[max_idx] << std::endl;
	std::vector<double>  evals = {-1, 1, 2}	 ;
	printf("P(c = 5) = %f \n",player1.get_dens_arr()[max_idx]); 
	int n = player1.get_comp_arr().size();
		
       	for (int j = 0; j <10 ; j++) { 

		//for(int i = 0; i < 10; i++) evals.push_back(evaluation());
			
		//int choice = std::distance(evals.begin(),std::max_element(evals.begin(), evals.end())); 
		
			int choice = zero_to_one(re); 
			// std::cout << "Maximum eval was: " << *(std::max_element(evals.begin(),evals.end())) << std::endl;
			// std::cout << "Minimum evals was: " << *(std::min_element(evals.begin(), evals.end())) << std::endl; 
			// std::cout << "choice made was" << evals[choice] << std::endl; 
			player1.update_dens(evals, choice); 
			// printf("P(c = 10) = %f \n",player1.get_dens_arr()[max_idx]); 
			// std::cout << " ----------------------------------------------- " << std::endl; 
	} 
	player1.update_range(11); 
	std::vector<double> dens_arr = player1.get_dens_arr();
	std::vector<double> new_comp_arr = player1.get_comp_arr(); 
	std::cout << std::scientific;
	int m = new_comp_arr.size();
	int q = dens_arr.size();
	printf("m = %i, q = %i \n", m, q);
	
	for (int i = 0; i < 10; i++){ 
		printf("%f, ", new_comp_arr[i]); 
	}
	std::cout << std::endl;
	for (int i = 10; i < 20; i++){ 
		printf("%E, ", dens_arr[i]); 
	}
	std::cout << std::endl; player1.get_params(); std::cout << std::endl; 

	// std::cout << "minimum competence is " << new_comp_arr.front() << std::endl; 
	// std::cout << "max competence is " << new_comp_arr.back() << std::endl;
	double normalised; 
	for (auto& elem: dens_arr) normalised += elem; 
	std::cout << "density sums to :" << normalised << std::endl; 
	// std::cout << "old size: " << n << " new size: " << m << std::endl; 
	return 0; 
} 
