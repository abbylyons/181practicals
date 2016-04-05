import numpy as np
import csv
import math
from sklearn import linear_model

# Predict via the user-specific median.
# If the user has no data, use the global median.

train_file = 'train.csv'
test_file  = 'test.csv'
soln_file  = 'user_median.csv'
user_file  = 'profiles.csv'

# Load the training data.
train_data = {}
artist_data = {}
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        if not user in train_data:
            train_data[user] = {}

        train_data[user][artist] = int(plays)

        if not artist in artist_data:
            artist_data[artist] = int(plays)
        else:
            artist_data[artist] += int(plays)

# Compute the global median and per-user median.
plays_array  = []
user_medians = {}
for user, user_data in train_data.iteritems():
    user_plays = []
    for artist, plays in user_data.iteritems():
        plays_array.append(plays)
        user_plays.append(plays)

    user_medians[user] = np.median(np.array(user_plays))

# calculate artist scores
for artist in artist_data:
    artist_data[artist] = np.log(artist_data[artist])

# log transform the data
for user, user_data in train_data.iteritems():
    user_medians[user] = math.log(user_medians[user])

# find the maximum median
max_median = 0
for user, user_data in train_data.iteritems():
    if user_medians[user] > max_median:
        max_median = user_medians[user]

user_scores = {}
for user, user_data in train_data.iteritems():
    user_scores[user] = user_medians[user] / max_median

sexes = {}
ages = {}
all_ages = []
with open(user_file, 'r') as usr_fh:
    usr_csv = csv.reader(usr_fh, delimiter=',', quotechar='"')
    next(usr_csv, None)

    for row in usr_csv:
        user    = row[0]
        sex     = row[1]
        age     = row[2]
        country = row[3]

        if sex == "":
            sexes[user] = 0
        elif sex == "m":
            sexes[user] = 1
        elif sex == "f":
            sexes[user] = 2

        if not age == "":
            if int(age) >= 7 and int(age) <= 80:
                ages[user] = int(age)
                all_ages.append(int(age))
            else:
                ages[user] = 99
        else:
            ages[user] = 99

        median = np.median(np.array(all_ages))

        for key, value in ages.iteritems():
            if value == 99:
                ages[key] = median

to_predict = []
ids = []
# Get inputs.
with open(test_file, 'r') as test_fh:
    test_csv = csv.reader(test_fh, delimiter=',', quotechar='"')
    next(test_csv, None)

    for row in test_csv:
        id     = row[0]
        user   = row[1]
        artist = row[2]
        to_predict.append([artist_data[artist], user_scores[user], sexes[user], ages[user]])
        ids.append(id)

# PREDICT HERE
preds = {}
artist_data[artist]
user_scores[user]
sexes[user]
ages[user]

clf = linear_model.Ridge(alpha = .01)
clf.fit(to_predict)

#
with open(soln_file, 'w') as soln_fh:
    soln_csv = csv.writer(soln_fh,
                          delimiter=',',
                          quotechar='"',
                          quoting=csv.QUOTE_MINIMAL)
    soln_csv.writerow(['Id', 'plays'])

    for key, value in preds:
        soln_csv.writerow([key, value)
