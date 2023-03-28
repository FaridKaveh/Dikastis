#include <iostream>
#include <string>
#include <fstream>


/* To get move evaluations from stockfish, dikastis needs to have a dialogue with stockfish. This file handles
their dialogue by sending commands from dikastis and receiving responses from stockfish */


std::string 
get_fen(const char* file){ 
    std::ifstream ifin(file); 
    std::string fen; 
    ifin >> fen; 


    std::cout << fen << std::endl;
    return fen; 
} 

int main() {
    const char* file = "/home/code/moves.txt" 
    get_fen(file);

    return 0; 
}