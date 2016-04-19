import numpy as np
import csv
import math


# Predict via the user-specific median.
# If the user has no data, use the global median.

def MAE(X_hat, X):
    err = 0
    for i, x in enumerate(X):
        err += np.abs(X_hat[i] - x)
    return float(err/N)

P = {}
S = {}
N = 0.0
norm = 0.1 # normalization factor
eps = 0.1

def pred(user, artist):
    return S[user]* P[artist]

train_file  = 'train.csv'
test_file   = 'test.csv'
soln_file   = 'out.csv'

# Load the training data.
user_data = {}
artist_data = {}
i = 0
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        if i == 100000:
            break
        i += 1
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        P[artist] = 4
        S[user] = 4
        N += 1

        if not user in user_data:
            user_data[user] = {}

        user_data[user][artist] = int(plays)


print("LOADED TRAINING DATA")


plays_array  = []
user_medians = {}
for user, userdict in user_data.iteritems():
    user_plays = []
    for artist, plays in userdict.iteritems():
        plays_array.append(plays)
        user_plays.append(plays)

    user_medians[user] = np.median(np.array(user_plays))
global_median = np.median(np.array(plays_array))

print("Computed the global median.")

cnt = 0
error = float('inf')
hi_low = []
while cnt < 100 and error > 0:
    # Calculate Xhats
    X_hats = []
    X = []
    for user, artistDict in user_data.iteritems():
        for artist, plays in artistDict.iteritems():
            prediction = pred(user, artist)
            X_hats.append(prediction)
            X.append(plays)
            if prediction > plays:
                hi_low.append(0)
            else:
                hi_low.append(1)

    new_error = MAE(X_hats, X)
    if new_error - error > eps:
         break
    error = new_error
    print("Error: " + str(error))
    index = 0
    P_grads = {}
    S_grads = {}
    P_counts = {}
    S_counts = {}
    for user, artistDict in user_data.iteritems():
        for artist, plays in artistDict.iteritems():
            if cnt % 2 == 0:
                if artist not in P_grads:
                    P_grads[artist] = 0
                if hi_low[index] == 0:
                    P_grads[artist] -= S[user]
                else:
                    P_grads[artist] += S[user]
                if artist not in P_counts:
                    P_counts[artist] = 0
                P_counts[artist] += 1
            else:
                if user not in S_grads:
                    S_grads[user] = 0
                if hi_low[index] == 0:
                    S_grads[user] -= P[artist]
                else:
                    S_grads[user] += P[artist]
                if user not in S_counts:
                    S_counts[user] = 0
                S_counts[user] += 1

            index += 1

    if cnt % 2 == 0:
        for artist in P:
            P[artist] += P_grads[artist]/P_counts[artist] * norm
    else:
        for user in S:
            S[user] += S_grads[user]/S_counts[user] * norm

    cnt += 1

print(S.itervalues().next())
print(P.itervalues().next())
print("Finished Coordinate decent")

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

            if user in S:
                soln_csv.writerow([id, pred(user, artist)])
            else:
                #print "User", id, "not in training data."
                soln_csv.writerow([id, global_median])


print("All done!")
