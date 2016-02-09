import csv
import os
import sys
import neural as nn
import random

__author__ = 'timothy'


# Loads previously converted training data
def load_data(filename, test_len):

    # Check that training data has been converted:
    if not os.access("./" + filename, os.R_OK):
        print("training data can't be accessed")
        sys.exit()

    #initialize data


    print("Loading data")

    reader = csv.reader(open("./" + filename))
    next(reader)
    rows = []

    for i in range(test_len):
        row = next(reader)
        new_row = []
        for k in range (1,258):
            new_row.append(float(row[k]))
        rows.append(new_row)

    return rows


def test_net(net, data):

    total_square_error = 0
    for i in range(100):
        row = random.choice(data)
        inp = row[0:256]
        out = row[256]
        total_square_error += (out-net.forward_pass(inp)[0]*3)**2
    return total_square_error/100


def run_test(net, out_file):


    # Check that the data can be accessed.
    if not os.access("./test.csv", os.R_OK):
        print("data can't be accessed")
        sys.exit()


    print("testing")

    reader = csv.reader(open("./test.csv"))
    writer = csv.writer(open("./" + out_file, 'wb+'), delimiter=',')
    next(reader)

    writer.writerow(["Id", "Prediction"])

    for row in reader:
        new_row = []
        for i in range(2, 258):
            new_row.append(float(row[i]))
        final_row = [row[0], net.forward_pass(new_row)[0]*3]
        writer.writerow(final_row)
        if float(row[0]) % 1000 == 0:
            print(row[0])

def save_net(net, name):

    # choose an emotion
    path = "./nets/" + name
    data = net.get_weights()
    with open(path, 'wb+') as csv_file:
        weight_writer = csv.writer(csv_file, delimiter=',')
        weight_writer.writerow(data)


def load_net(name):
    print("Loading net...")
    path = "./nets/" + name
    input = open(path, "r")
    net = nn.init_net()
    weights = []
    with open(path, 'rb') as csv_file:
        weight_reader = csv.reader(csv_file, delimiter=',')
        for row in weight_reader:
            for el in row:
                weights.append(float(el))
    net.put_weights1d(weights)
    print("Net loaded!")
    return net