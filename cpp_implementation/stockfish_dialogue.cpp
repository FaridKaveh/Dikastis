#include <iostream> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 
#include <fstream> 
#include "helper.h"
#include "stockfish_dialogue.h"



/* To get move evaluations from stockfish, dikastis needs to have a dialogue with stockfish. This file handles
their dialogue by sending commands from dikastis and receiving responses from stockfish */



int sf_dialogue(const char* file) { 
    //arg array for execvp
    //sf_commands.sh is the bash script of to be run by child process
    const char* argv[] = {"./sf_commands.sh", NULL};
    //array for pipe
    int child_write_pipe[2];
    
    
    // const char* fen;
    const char* interpreter = "#!/usr/bin/expect \n";
    const char* spawn = "spawn /home/farid/Apps/stockfish_15_linux_x64_avx2/stockfish15\nexpect Stockfish\n";

    std::ifstream fenfile (file);  
    std::string fen; 


    if(!(fenfile.is_open())) { printf("Failed to open fen file.\n"); return 0;}
    //loop fenfile for successive positions
    while (getline(fenfile, fen)){ 
        if (fen == "EOG") { break;}
        if (pipe(child_write_pipe)){ 
            printf("Failed to pipe.");
            return EXIT_FAILURE; 
        }
        //child process will run a bash script that takes evaluation data from stockfish for current fen
        pid_t pid = fork(); 

        if (pid == -1) { 
            printf("Failed to fork");
        }
        else if (pid == 0) { 
            //this is the chid. Close read end of pipe and set stdout and stderr to write end. 
            close(child_write_pipe[0]); 
            dup2(child_write_pipe[1],1);
            dup2(child_write_pipe[1], 2); 
            //can now close the write end as well, the dup2 copy will do this job.
            close(child_write_pipe[1]);
            execvp(argv[0], (char* const*) argv);
        }

        else{ 
            //This is the parent. Close write end of pipe. 
            close(child_write_pipe[1]);
            int status;
            waitpid(pid, &status, 0); 

            if (WIFEXITED(status)) { 
                printf("child terminated normally\n");
            }

            else {printf("execvp error\n");}
            //read_from_file declared and implemented in helper.cpp
            read_from_file(child_write_pipe[0]);
            std::cout << "-------------------------------------------" << std::endl;


            //Write the next bash script to be run onto commfile.
            std::ofstream commfile;
            commfile.open("sf_commands.sh");
            commfile << interpreter << spawn;
            commfile << "send \"position fen " << fen << " \\n isready \\n\"\n"; 
            commfile << "expect readyok\n";
            commfile << "send \"go depth 15 \\n \" \n"; 
            commfile << "expect info depth 15 \n";
            commfile << "send \" isready \\n\"\n";
            commfile << "expect readyok \n";

            commfile.close();
        }
       
    }
    
    fenfile.close();
    return EXIT_SUCCESS;
}