#pragma once 
#include <vector> 

class Agent { 
	private: 
		double delta, epsilon; 
		double min_comp, max_comp;
	       	std::vector<double> comp_arr; 
		std::vector<double> comp_dens_arr;
	
	public: 
		Agent(); //default constructor defined in implementation
		
		void get_params(){printf("delta: %f, epsilon: %f, comp range: [%f, %f]", delta, epsilon, min_comp,max_comp); }	
		
		void update_dens(std::vector<double> evals, int choice); 	
};

