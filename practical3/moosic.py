import numpy as np
import csv
import math
from sklearn import linear_model
from sklearn.cluster import KMeans
from sklearn.ensemble import RandomForestRegressor
from sklearn import cluster


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





######################################################################

# NICASIA'S ARTIST CLUSTERING:


## CODE TO GENERATE MATRIX -- SLOW, SO JUST READ IN MATRIX INSTEAD (BELOW)
# mx = np.zeros([len(artists_idx), len(artists_idx)])

# thisround = 0
# for art_id in artists_idx:
#     num_common_players = np.zeros(len(artists_idx))
#     prop_common_players = np.zeros(len(artists_idx))
#     for user in train_data:
#         if art_id in train_data[user]:
#             for art_id2 in artists_idx:
#                 if art_id2 in train_data[user]:
#                     num_common_players[artists_idx[art_id2]] += 1
#     total_players = num_common_players[artists_idx[art_id]]
#     prop_common_players = num_common_players/float(total_players)
#     mx[thisround] = prop_common_players
#     thisround += 1

# artists_to_cluster = mx.T


# READ IN PREVIOUSLY GENERATED ARTIST MATRIX:
artists_to_cluster = np.zeros([2000,2000])

with open("artists_matrix.csv", 'r') as amx:
    artist_mx_csv = csv.reader(amx, delimiter=',', quotechar='"')
    counter = 0
    for row in artist_mx_csv:
        artists_to_cluster[counter] = row
        counter += 1


numclusters = 20

km = KMeans(n_clusters=20, init='k-means++', n_init=10, max_iter=300, 
    tol=0.0001, precompute_distances='auto', verbose=0, copy_x=True, n_jobs=1)

ag = cluster.AgglomerativeClustering(n_clusters=20, affinity='euclidean',  
    connectivity=None, n_components=None, compute_full_tree='auto', linkage='ward')

km_clusters  = KMeans.fit_predict(km, artists_to_cluster)

ag_clusters = cluster.AgglomerativeClustering.fit_predict(ag, artists_to_cluster)


clusters_1hot_km = np.zeros([len(artists_idx), numclusters])
for i in range(len(artists_idx)):
    newrow = np.zeros(numclusters)
    onehot = km_clusters[i]
    newrow[onehot] = 1
    clusters_1hot_km[i] = newrow


clusters_1hot_ag = np.zeros([len(artists_idx), numclusters])
for i in range(len(artists_idx)):
    newrow = np.zeros(numclusters)
    onehot = ag_clusters[i]
    newrow[onehot] = 1
    clusters_1hot_ag[i] = newrow








######################################################################


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





####################################################################

# FOR SUBMITTING PREDICTIONS


# to_predict = []
# ids = []
# # Get inputs.
# with open(test_file, 'r') as test_fh:
#     test_csv = csv.reader(test_fh, delimiter=',', quotechar='"')
#     next(test_csv, None)

#     for row in test_csv:
#         id     = row[0]
#         user   = row[1]
#         artist = row[2]
#         to_predict.append([clsters[user_idx[user]], clusters_1hot_km[artists_idx[artist]], user_scores[user], sexes[user], ages[user]])
#         # to_predict.append([clsters[user_idx[user]], artist_data[artist], user_scores[user], sexes[user], ages[user]])
#         ids.append(id)

# print("got inputs")

# # get fitting data
# fitX = []
# fitY = []
# with open(train_file, 'r') as train_fh:
#     train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
#     next(train_csv, None)
#     for row in train_csv:
#         user   = row[0]
#         artist = row[1]
#         plays  = row[2]

#         fitX.append([clsters[user_idx[user]], artist_data[artist], user_scores[user], sexes[user], ages[user]])
#         fitY.append(int(plays))

# print("got fitting data")

# # with open(fit_file, 'w') as fit_fh:
# #     fit_csv = csv.writer(fit_fh,
# #                           delimiter=',',
# #                           quotechar='"',
# #                           quoting=csv.QUOTE_MINIMAL)
# #     fit_csv.writerow(['Artist Score', 'user_score', 'sex', 'age', 'plays'])
# #
# #     for i in range(len(fitX)):
# #         new_row = fitX[i]
# #         new_row.append(fitY[i])
# #         fit_csv.writerow(new_row)
# #
# # print("saved fit data")
# #
# # with open(pred_file, 'w') as pred_fh:
# #     pred_csv = csv.writer(pred_fh,
# #                           delimiter=',',
# #                           quotechar='"',
# #                           quoting=csv.QUOTE_MINIMAL)
# #     pred_csv.writerow(['Artist Score', 'user_score', 'sex', 'age', 'id'])
# #
# #     for i, row  in enumerate(to_predict):
# #         new_row = row
# #         new_row.append(ids[i])
# #         pred_csv.writerow(new_row)
# #
# #
# # print("saved pred data")

# #
# with open(soln_file, 'w') as soln_fh:
#     soln_csv = csv.writer(soln_fh,
#                           delimiter=',',
#                           quotechar='"',
#                           quoting=csv.QUOTE_MINIMAL)
#     soln_csv.writerow(['Id', 'plays'])

#     for i, value in enumerate(preds):
#         soln_csv.writerow([ids[i], value])

# print("All done!")



####################################################################

# FOR CROSS VALIDATION





to_predict = []
actual_plays = []

# get fitting data
fitX = []
fitY = []
with open(train_file, 'r') as train_fh:
    cnt = 0
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        if cnt < 2000000:
            fitX.append([clsters[user_idx[user]], clusters_1hot_km[artists_idx[artist]], user_scores[user], sexes[user], ages[user]])
            fitY.append(int(plays))
        else:         
            to_predict.append
            actual_plays.append(int(plays))

        cnt += 1

print("got fitting data")

# PREDICT HERE

clf = RandomForestRegressor()
clf.fit(fitX, fitY)

testX=np.array(to_predict,dtype=float)
preds = clf.predict(testX)

error_array = abs(preds - actual_plays)
error = float(sum(error_array))/float(len(preds))


print("finished predicting")
print("error", error)












