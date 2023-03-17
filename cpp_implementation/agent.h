#ifndef AGENT_H 
#define AGENT_H
#include <vector> 
#include <cstdio>

class Agent { 
	private: 
		double delta, epsilon; 
		double min_comp, max_comp;
	    std::vector<double> comp_arr; 
		std::vector<double> comp_dens_arr;
	
	public: 
		//default constructor defined in implementation
		Agent(); 
		//alternative constructor 
		Agent(double epsilon, double delta, double max_comp, double min_comp); 
		double get_skill(); 	
		void get_params(){printf("delta: %f, epsilon: %f, comp range: [%f, %f]\n", delta, epsilon, min_comp,max_comp); }	
		void update_dens(std::vector<double> evals, int choice); 	
		std::vector<double> get_dens_arr() { return comp_dens_arr;}
		std::vector<double> get_comp_arr() {return comp_arr;}
		void update_range(int no_data_points); 
		void set_minmax(double min, double max) {min_comp = min; max_comp = max;}
		void set_comp_arrays(); 
};

#endif
