#include <iostream> 
#include <random> 
#include <algorithm> 
#include <fcntl.h>
#include "agent.h" 
#include "helper.h"
#include "stockfish_dialogue.h"


//random number generator for testing. 
std::random_device rd; //seed for  random generator
std::default_random_engine re(rd()); //random generator
std::uniform_real_distribution<double> one_to_one(-1,0.5); //desired distribution
std::uniform_int_distribution<int> zero_to_nine (0,9);

auto evaluation {std::bind(one_to_one, re)}; //bind generator and dist for convienience


int main() { 
	Agent player1(0.1, 0.1, 10.0, -10.0);
	player1.get_params(); 
	// sf_dialogue("moves.txt"); 
	int fd =  open ("test.txt", O_RDONLY);
	const char* hey = "hello";
	get_eval(fd, hey);
	
	return 0; 
} 
