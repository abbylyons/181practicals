import numpy as np
import csv
from matplotlib import pyplot as plt
# Predict via the user-specific median.
# If the user has no data, use the global median.

train_file = '../../practical3_data/train.csv'
test_file  = '../../practical3_data/test.csv'
artists_file = '../../practical3_data/artists.csv'
profiles_file = '../../practical3_data/profiles.csv'
soln_file  = '../../practical3_data/user_median.csv'


from sklearn.cluster import KMeans
from sklearn import cluster
from sklearn import datasets


# Predict via the user-specific median.
# If the user has no data, use the global median.


train_file  = 'train.csv'
test_file   = 'test.csv'
soln_file   = 'out.csv'
user_file   = 'profiles.csv'
pred_file   = 'to_predict.csv'
fit_file    = 'to_fit.csv'
artist_file = 'artists.csv'

# LOAD ARTIST_SIMILARITY MATRIX:

artists_mx = np.zeros([2000,2000])

with open("artists_matrix.csv", 'r') as amx:
    artist_mx_csv = csv.reader(amx, delimiter=',', quotechar='"')
    counter = 0
    for row in artist_mx_csv:
        artists_mx[counter] = row
        counter += 1
artists_mx = artists_mx.T

print("Loaded artists matrix")

# Load the training data.
# Load the training data.
train_data_v = {}

counter = 0
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]
    
        if not user in train_data_v:
            train_data_v[user] = {}

        train_data_v[user][artist] = int(plays)
        
        counter += 1



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




# Compute the global median and per-user median.
plays_array  = []
user_medians = {}
for user, user_data in train_data_v.iteritems():
    user_plays = []
    for artist, plays in user_data.iteritems():
        plays_array.append(plays)
        user_plays.append(plays)

    user_medians[user] = np.median(np.array(user_plays))

print("Computed user medians")




####################################################################

# FOR SUBMITTING PREDICTIONS


to_pred = []
ids = []
# Get inputs.
with open(test_file, 'r') as test_fh:
    test_csv = csv.reader(test_fh, delimiter=',', quotechar='"')
    next(test_csv, None)

    for row in test_csv:
        id     = row[0]
        user   = row[1]
        artist = row[2]
        to_pred.append([user, artist])
        ids.append(id)

print("got inputs")


preds = []
for i in range(len(to_pred)):
    user = to_pred[i][0]
    artist = to_pred[i][1]
    artist_id = artists_idx[artist]
    if user in train_data_v:
        user_known_plays = train_data_v[user]
        max_similarity = 0
        max_similarity_id = 0
        for known_artist in user_known_plays:
            if artists_mx[artist_id, artists_idx[known_artist]] > max_similarity:
                max_similarity = artists_mx[artist_id, artists_idx[known_artist]]
                max_similarity_id = artists_idx[known_artist]

        closest_artist = 0
        for artist in user_known_plays:
            if artists_idx[artist] == max_similarity_id:
                closest_artist = artist

        
        MEDIAN_WEIGHT = .9
        if user in user_medians:
            prediction = MEDIAN_WEIGHT * user_medians[user] + (1-MEDIAN_WEIGHT) * train_data_v[user][artist]
            
        else: 
            prediction = MEDIAN_WEIGHT * 118 + (1-MEDIAN_WEIGHT * train_data_v[user][artist])
        preds.append(prediction)
    else:
        prediction = 118
        preds.append(prediction)
    
#
print(len(preds))
print(len(to_pred))

with open(soln_file, 'w') as soln_fh:
    soln_csv = csv.writer(soln_fh,
                          delimiter=',',
                          quotechar='"',
                          quoting=csv.QUOTE_MINIMAL)
    soln_csv.writerow(['Id', 'plays'])


    counter = 0
    for i, value in enumerate(preds):
        soln_csv.writerow([ids[i], value])
        counter += 1
    print counter

print("All done!")


