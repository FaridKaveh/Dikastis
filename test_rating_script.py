import numpy as np 

class Agent: 

    """ The Agent class defines a stochastic engine which plays a game where there is an optimal 
    or 'confident' strategy. The skill rating of the agent is updated using a Bayesian model
    whenever the it makes a move using the 'update_dens' function 
    """

    def __init__(self, min_comp, max_comp, delta, epsilon = 0.001) -> None:
        self.delta = delta 
        self.epsilon = epsilon
        self.min_comp = min_comp; self.max_comp = max_comp; 
        self.intval_length = self.max_comp - self.min_comp
        self.comp_arr = np.arange(self.min_comp,
            self.max_comp + self.epsilon, self.epsilon )
        self.comp_dens_arr = (1/np.shape(self.comp_arr)[0]) * np.ones(np.shape(self.comp_arr)[0])

        
    def get_skill(self) -> np.float64:
         

        return np.average(self.comp_arr, weights = self.comp_dens_arr)
    
    def play_game(self, evals) -> int:
        
        return NotImplementedError
    def update_dens(self, evals, choice) -> None:

        v_max = np.max(evals) 
        K = 0.01
        comp = self.get_skill(); 
        likelihoods = [(v_max - eval + K)**(-comp) for eval in evals]
        return NotImplementedError 