#include <iostream> 
#include <vector> 
#include <algorithm> 


class Agent{
	/* The Agent class defines a stochastic engine which plays a game where there is an optimal 
    or 'confident' strategy. The skill rating of the agent is updated using a Bayesian model
    whenever the it makes a move using the 'update_dens' function  */

	private: 
		float delta, epsilon; 
		float min_comp, max_comp;
	       	std::vector<float> comp_arr; 
		std::vector<float> comp_dens_arr; 
	public:
		Agent (){ 
			// default constructor for agent. Sets the competence range to [-3,3]
			delta = 0.1; 
			epsilon = delta;
			max_comp = 3; min_comp = -3; 
			float intervals = (max_comp-min_comp)/epsilon;	
			for (int i = 0; i < intervals; i++){
				comp_arr.push_back(max_comp-i*epsilon); 
			}

			comp_dens_arr.assign(comp_arr.size(), 1/comp_arr.size()); 
		}	
};

int main() { 
	return 0;
}
