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
        # [dist][tree_bot][vel][monkey_bot][action]
        self.Qs = np.array([[[[[0 for _ in range(2)] for _ in range(10)] for _ in range(10)] for _ in range(10)] for _ in range(10)])
        self.gamma = .5
        self.grav = None
        self.horz_speed = None
        self.first_round = True

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

        # figure out gravity and horisontal speed
        if self.first_round:
            new_action = 0
            new_state = state
            self.first_round = False
        elif self.horz_speed is None:
            self.horz_speed = self.last_state['tree']['dist'] - state['tree']['dist']
            self.gravity = self.last_state['monkey']['vel'] - state['monkey']['vel']
            new_action = 0
            new_state = state
        else:
            #update Q values for the last iteration
            # figure out the previous bins:
            prev_dist = round((self.last_state['tree']['dist'] + 50)/200)
            prev_tree_bot = round((self.last_state['tree']['bot'])/40)
            prev_vel = round((self.last_state['monkey']['vel']+50)/20)
            prev_monkey_bot = round((self.last_state['monkey']['bot'])/200)
            # figure out the bins:
            dist = round((state['tree']['dist'] + 50)/50)
            tree_bot = round((state['tree']['bot'])/20)
            vel = round((state['monkey']['vel']+50)/10)
            monkey_bot = round((state['monkey']['bot'])/50)
            self.Qs[prev_dist][prev_tree_bot][prev_vel][prev_monkey_bot][self.last_action] = self.last_reward + self.gamma * max(self.Qs[dist][tree_bot][vel][monkey_bot])
            print(self.Qs[prev_dist][prev_tree_bot][prev_vel][prev_monkey_bot][self.last_action])
            new_action = self.Qs[dist][tree_bot][vel][monkey_bot].argmax()

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
