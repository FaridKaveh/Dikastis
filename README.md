#Dikastis 

Diskastis (from greek meaning 'Judge')  is a project to rate chess players based on engine evaluations of their move strengths. A player is modelled as a stochastic agent in a one-parameter space. Each move made by him/her is used to update the estimate of their player strength. See the paper by Fatta et al. for details (https://ieeexplore.ieee.org/abstract/document/4938634). I will making be some substantional changes to the rating system proposed in this paper. In particular I believe their system unfairly punishes players who play suboptimal moves that nevertheless make the position more difficult for the opponent to play.  

The engine used for evaluation is Stockfish 15 NNUE. Dikastis' rating system is absolute, unlike the ELO rating system, which is relative. It is also transferrable to games other than chess, as it does not use any chess specific information. 
