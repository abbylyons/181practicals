# Imports.
import numpy as np
import numpy.random as npr
import neural_net.data as nn

from SwingyMonkey import SwingyMonkey


class Learner(object):
    '''
    This agent jumps randomly.
    '''

    def __init__(self):
        self.last_state  = None
        self.last_action = None
        self.last_reward = None
        self.impulse = 15
        # [vertical_dist][horz_dist][grav][action]
        self.Qs = np.array([[[[0 for _ in range(2)] for _ in range(2)] for _ in range(10)] for _ in range(12)])
        self.gamma = .7
        self.grav = None
        self.horz_speed = None
        self.first_round = True
        self.tree_gap = None

    def reset(self):
        self.last_state  = None
        self.last_action = None
        self.last_reward = None
        self.grav = None
        self.horz_speed = None
        self.first_round = True

    def action_callback(self, state):
        '''
        Implement this function to learn things and take actions.
        Return 0 if you don't want to jump and 1 if you do.
        '''

        # You might do some learning here based on the current state and the last state.

        # You'll need to select and action and return it.
        # Return 0 to swing and 1 to jump.

        # figure out gravity tree gap
        if self.first_round:
            new_action = 0
            new_state = state
            self.first_round = False
            self.tree_gap = state['tree']['top']-state['tree']['bot']
        elif self.horz_speed is None:
            self.horz_speed = self.last_state['tree']['dist'] - state['tree']['dist']
            if self.last_state['monkey']['vel'] - state['monkey']['vel'] == 1:
                self.gravity = 0
            else:
                self.gravity = 0
            new_action = 0
            new_state = state
        else:
            #update Q values for the last iteration
            # figure out the previous bins:
            prev_v_dist = (self.last_state['tree']['top'] - self.last_state['monkey']['top']+ self.tree_gap)/50
            prev_horz_dist = (self.last_state['tree']['dist']+150)/100
            # figure out the bins:
            v_dist = (state['tree']['top'] - state['monkey']['top']+self.tree_gap)/50
            horz_dist = (state['tree']['dist']+150)/100
            self.Qs[prev_v_dist][prev_horz_dist][self.gravity][self.last_action] = self.last_reward + self.gamma * max(self.Qs[v_dist][horz_dist][0])
            action0Q = self.Qs[v_dist][horz_dist][0][0]
            action1Q = self.Qs[v_dist][horz_dist][0][1]


            # this can be better
            if action0Q == 0:
                new_action = 0
            elif action1Q == 0:
                new_action = 1;
            else:
                new_action = self.Qs[v_dist][horz_dist][self.gravity].argmax()
            new_state  = state

        self.last_action = new_action
        self.last_state  = new_state

        return self.last_action

    def reward_callback(self, reward):
        '''This gets called so you can see what reward you get.'''
        # train the network
        self.last_reward = reward


def run_games(learner, hist, iters = 100, t_len = 100):
    '''
    Driver function to simulate learning by having the agent play a sequence of games.
    '''

    for ii in range(iters):
        # Make a new monkey object.
        swing = SwingyMonkey(sound=False,                  # Don't play sounds.
                             text="Epoch %d" % (ii),       # Display the epoch on screen.
                             tick_length = t_len,          # Make game ticks super fast.
                             action_callback=learner.action_callback,
                             reward_callback=learner.reward_callback)

        # Loop until you hit something.
        while swing.game_loop():
            pass

        # Save score history.
        hist.append(swing.score)

        # Reset the state of the learner.
        learner.reset()

    return


if __name__ == '__main__':

	# Select agent.
	agent = Learner()

	# Empty list to save history.
	hist = []

	# Run games.
	run_games(agent, hist, 1000, 10)

	# Save history.
	np.save('hist',np.array(hist))
