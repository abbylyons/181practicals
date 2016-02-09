import data as nn
import config as cfg
import csv
import helpers
import random

__author__ = 'Timothy H. C. Tamm'


def init_net():

    num_inputs = cfg.inputs
    num_outputs = cfg.outputs
    num_hidden_layers = 1
    num_npl = cfg.NPL

    return nn.NeuralNet(num_inputs, num_outputs, num_hidden_layers, num_npl)


# function for training neural net with backpropagation
def backprop_train(testing_name, test_len):

    # initalize a net
    net = init_net()

    return continue_bp(net, test_len, testing_name)


def error(ideal, actual):
    return nn.total_error(ideal, actual)


# function for continuing to train a net.
def continue_bp(net, test_len, testing_name=""):

    # load training data
    data = helpers.load_data("train.csv", test_len)
    train_len = int(test_len*0.8)
    training_data = data[0:train_len+1]
    testing_data = data[train_len+1:]


    # # writer for testing data
    # csv_file = None
    # writer = None
    # if testing_name != "":
    #     path = "./results/" + testing_name
    #     csv_file = open(path, 'wb+')
    #     writer = csv.writer(csv_file, delimiter=',')

    print("Training Neural Net")

    # train the net
    for i in range(train_len):

        # Print out progress:
        if i % 5000 == 0:
            per = float(i) / float(train_len) * 100
            print("Training: " + str(format(per, '.2f')) + "%")
            error = helpers.test_net(net, testing_data)
            print("current error:" + str(error))

            # # write testing results if testing
            # if writer is not None:
            #     data = [i, helpers.test_net(net, testing_data)]
            #     writer.writerow(data)

        # pick a specific test case
        test_case = training_data[i]
        net.train(test_case[:256], [test_case[256]/3])

    # # write testing results if testing
    # if writer is not None:
    #     data = [test_len, helpers.test_net(net, testing_data)]
    #     writer.writerow(data)
    #
    # # close the file
    # if csv_file is not None:
    #     csv_file.close()

    return net
