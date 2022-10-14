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
        """Returns the mean of comp_arr w.r.t comp_dens_arr, i.e. the expected skill of Agent"""

        return np.average(self.comp_arr, weights = self.comp_dens_arr)
    
    def play_game(self, evals) -> int:

        """Picks a move according to its evaluation from 'evals' with skill 'apparent_comp'."""

        apparent_comp = np.random.choice(self.comp_arr, size = 1, p = self.comp_dens_arr )
        
        return NotImplementedError
    def update_dens(self, evals, choice) -> None:
        """Updates self.comp_dens_arr according to an observation evals[choice]."""
        v_max = np.max(evals) 
        K = 0.01 
        cond_prob_arr = (v_max - evals[choice] + K)**(-self.comp_arr) 
        self.comp_dens_arr = (self.comp_dens_arr*cond_prob_arr)/np.sum(cond_prob_arr * self.comp_dens_arr) 

        