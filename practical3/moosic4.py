import numpy as np
import csv

# Predict via the user-specific median.
# If the user has no data, use the global median.

train_file = 'train.csv'
test_file  = 'test.csv'
soln_file  = 'all_median.csv'

# Load the training data.
train_data = {}
re_train_data = {}
cnt = 0
valid_data = []
valid_X = []
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        # if cnt < 3700000:
        if not user in train_data:
            train_data[user] = {}

        train_data[user][artist] = int(plays)

        if not artist in re_train_data:
            re_train_data[artist] = {}

        re_train_data[artist][user] = int(plays)
        # cnt += 1
        # else:
        #     valid_data.append([user, artist])
        #     valid_X.append(int(plays))

print("Loaded data")

# Compute the global median and per-user median.
plays_array  = []
user_medians = {}
for user, user_data in train_data.iteritems():
    user_plays = []
    for artist, plays in user_data.iteritems():
        plays_array.append(plays)
        user_plays.append(plays)

    user_medians[user] = np.median(np.array(user_plays))
global_median = np.median(np.array(plays_array))

print("got medians")
# Compute the global median and per-artist median.
re_plays_array  = []
artist_medians = {}
for artist, artist_data in re_train_data.iteritems():
    artist_plays = []
    for user, plays in artist_data.iteritems():
        re_plays_array.append(plays)
        artist_plays.append(plays)

    artist_medians[user] = np.median(np.array(artist_plays))
global_artist_median = np.median(np.array(re_plays_array))

print ("got artist medians")



# #check valid_error
# tot_err = 0.0
# cnt = 0.0
# for i, ls in enumerate(valid_data):
#     if ls[0] in user_medians:
#         pred = user_medians[user]
#     else:
#         pred = global_median
#     tot_err += np.abs(valid_X[i] - pred)
#     cnt += 1.0
# print("valid error orig: " + str(tot_err/cnt))
#
# #check valid_error
# tot_err = 0.0
# cnt = 0.0
# for i, ls in enumerate(valid_data):
#     if ls[0] in user_medians and ls[1] in artist_medians:
#         pred = (user_medians[user]+artist_medians[artist])/2
#     elif ls[0] in user_medians:
#         pred = (user_medians[user]+global_artist_median)/2
#     elif ls[1] in artist_medians:
#         pred = (global_median+artist_medians[artist])/2
#     else:
#         pred = (global_median+global_artist_median)/2
#     tot_err += np.abs(valid_X[i] - pred)
#     cnt += 1.0
# print("valid error both: " + str(tot_err/cnt))

# Write out test solutions.
with open(test_file, 'r') as test_fh:
    test_csv = csv.reader(test_fh, delimiter=',', quotechar='"')
    next(test_csv, None)

    with open(soln_file, 'w') as soln_fh:
        soln_csv = csv.writer(soln_fh,
                              delimiter=',',
                              quotechar='"',
                              quoting=csv.QUOTE_MINIMAL)
        soln_csv.writerow(['Id', 'plays'])

        for row in test_csv:
            id     = row[0]
            user   = row[1]
            artist = row[2]

            if user in user_medians and artist in artist_medians:
                soln_csv.writerow([id, (user_medians[user]+artist_medians[artist])/2])
            elif user in user_medians:
                soln_csv.writerow([id, (user_medians[user]+global_artist_median)/2])
            elif artist in artist_medians:
                soln_csv.writerow([id, (global_median+artist_medians[artist])/2])
            else:
                # print "User", id, "not in training data."
                soln_csv.writerow([id, (global_median+global_artist_median)/2])
