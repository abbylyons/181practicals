import numpy as np
import csv

# Predict via the median number of plays.

train_file = 'train.csv'
test_file  = 'test.csv'
soln_file  = 'global_median.csv'

# Load the training data.
train_data = {}
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        artist = row[1]
        plays  = int(row[2])

        if not artist in train_data:
            train_data[artist] = plays
        else:
            train_data[artist] += plays

# Compute the global median.
for artist in train_data:
    train_data[artist] = np.log(train_data[artist])
