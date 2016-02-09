import neural as N
import helpers
__author__ = 'timothy'

net = N.backprop_train("third_net.csv", 100000)
helpers.save_net(net, "third_net.csv")
# net = helpers.load_net("second_net.csv")
# helpers.run_test(net, "output.csv")
