#include <iostream>
#include <string>
#include <fstream>


/* To get move evaluations from stockfish, dikastis needs to have a dialogue with stockfish. This file handles
their dialogue by sending commands from dikastis and receiving responses from stockfish */


std::string 
get_fen(const char* file){ 
    std::ifstream ifin(file); 
    std::string fen; 
    std::getline(ifin, fen);
    
    ifin.close();
    std::cout << fen.c_str() << std::endl;
    return fen; 
    
} 

int main() {
    const char* file = "moves.txt";
    get_fen(file);

    return 0; 
}