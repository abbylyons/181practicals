import numpy as np
import csv
import math
from sklearn import linear_model
from sklearn.cluster import KMeans
from sklearn.ensemble import RandomForestRegressor

# Predict via the user-specific median.
# If the user has no data, use the global median.


train_file  = 'train.csv'
test_file   = 'test.csv'
soln_file   = 'out.csv'
user_file   = 'profiles.csv'
pred_file   = 'to_predict.csv'
fit_file    = 'to_fit.csv'
artist_file = 'artists.csv'

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


print("LOADED TRAINING DATA")

artists_idx = {}
cnt = 0
with open(artist_file, 'r') as artist_fh:
    artist_csv = csv.reader(artist_fh, delimiter=',', quotechar='"')
    next(artist_csv, None)
    for row in artist_csv:
        artist_id  = row[0]

        artists_idx[artist_id] = cnt
        cnt += 1


artist_matrix = []
user_cnt = 0
user_idx = {}
for user, artist_dict in train_data.iteritems():
    user_idx[user] = user_cnt
    user_cnt += 1
    new_row = [0 for _ in range(cnt)]
    for artist, plays in artist_dict.iteritems():
        new_row[artists_idx[artist]] = plays
    artist_matrix.append(new_row)


print("Genertated matrix")
print(len(artist_matrix))
print(len(artist_matrix[0]))

clf = KMeans(n_clusters = 10, max_iter = 10)
clsters = clf.fit_predict(artist_matrix)

print("Clustered")

# Compute the global median and per-user median.
plays_array  = []
user_medians = {}
for user, user_data in train_data.iteritems():
    user_plays = []
    for artist, plays in user_data.iteritems():
        plays_array.append(plays)
        user_plays.append(plays)

    user_medians[user] = np.median(np.array(user_plays))

print("Computed user medians")

# calculate artist scores
for artist in artist_data:
    artist_data[artist] = np.log(artist_data[artist])

print("computed artist scores")

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

print("computed user scores")

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

    med = np.median(np.array(all_ages))
    for key, value in ages.iteritems():
        if value == 99:
            ages[key] = med


print("extracted profile data")

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
        to_predict.append([clsters[user_idx[user]], artist_data[artist], user_scores[user], sexes[user], ages[user]])
        ids.append(id)

print("got inputs")

# get fitting data
fitX = []
fitY = []
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        fitX.append([clsters[user_idx[user]], artist_data[artist], user_scores[user], sexes[user], ages[user]])
        fitY.append(int(plays))

print("got fitting data")

# PREDICT HERE

clf = RandomForestRegressor()
clf.fit(fitX, fitY)

testX=np.array(to_predict,dtype=float)
preds = clf.predict(testX)

print("finished predicting")

# with open(fit_file, 'w') as fit_fh:
#     fit_csv = csv.writer(fit_fh,
#                           delimiter=',',
#                           quotechar='"',
#                           quoting=csv.QUOTE_MINIMAL)
#     fit_csv.writerow(['Artist Score', 'user_score', 'sex', 'age', 'plays'])
#
#     for i in range(len(fitX)):
#         new_row = fitX[i]
#         new_row.append(fitY[i])
#         fit_csv.writerow(new_row)
#
# print("saved fit data")
#
# with open(pred_file, 'w') as pred_fh:
#     pred_csv = csv.writer(pred_fh,
#                           delimiter=',',
#                           quotechar='"',
#                           quoting=csv.QUOTE_MINIMAL)
#     pred_csv.writerow(['Artist Score', 'user_score', 'sex', 'age', 'id'])
#
#     for i, row  in enumerate(to_predict):
#         new_row = row
#         new_row.append(ids[i])
#         pred_csv.writerow(new_row)
#
#
# print("saved pred data")

#
with open(soln_file, 'w') as soln_fh:
    soln_csv = csv.writer(soln_fh,
                          delimiter=',',
                          quotechar='"',
                          quoting=csv.QUOTE_MINIMAL)
    soln_csv.writerow(['Id', 'plays'])

    for i, value in enumerate(preds):
        soln_csv.writerow([ids[i], value])

print("All done!")
