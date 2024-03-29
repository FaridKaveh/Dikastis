#Dikastis 

Diskastis (from greek meaning 'Judge')  is a project to rate chess players based on engine evaluations of their move strengths. A player is modelled as a stochastic agent in a one-parameter space. Each move made by him/her is used to update the estimate of their player strength. See the paper by Fatta et al. for details (https://ieeexplore.ieee.org/abstract/document/4938634). I will be making some substantional changes to the rating system proposed in this paper. In particular I believe their system unfairly punishes players who play suboptimal moves that nevertheless make the position more difficult for the opponent to play.  

The engine used for evaluation is Stockfish 15 NNUE. Dikastis' rating system is absolute, unlike the ELO rating system, which is relative. It is also transferrable to games other than chess, as it does not use any chess specific information.

To compile Dikastis you only need the ```cpp_implementation``` folder. To compile, make sure you have the g++ compiler installed (you can check using the command ```g++ --version```). Then navigate to the ```cpp_implementation``` folder andtype the following in Terminal (Linux/MacOS) 

```
 g++ *.cpp -o <FILE_NAME>
```

replacing ```<FILE_NAME>``` with whatever you want to call the output executable.    
### 
