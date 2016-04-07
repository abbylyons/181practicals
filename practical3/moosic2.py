import numpy as np
import csv
import math


# Predict via the user-specific median.
# If the user has no data, use the global median.

def MAE(X_hat, X):
    err = 0
    for i, x in enumerate(x):
        err += np.abs(X_hat[i] - x)
    return err/N

P = {}
S = {}
N = 0
norm = 0.05 # normalization factor

def p_a_grad(artist):
    grad = 0
    for user in artist_data[artist]:
        grad += S[user]
    return grad/N

def s_u_grad(user):
    grad = 0
    for artist in user_data[user]:
        grad += P[artist]
    return grad/N

def pred(user, artist):
    return P[artist] * S[user]

train_file  = 'train.csv'
test_file   = 'test.csv'
soln_file   = 'out.csv'

# Load the training data.
user_data = {}
artist_data = {}
with open(train_file, 'r') as train_fh:
    train_csv = csv.reader(train_fh, delimiter=',', quotechar='"')
    next(train_csv, None)
    for row in train_csv:
        user   = row[0]
        artist = row[1]
        plays  = row[2]

        P[artist] = 10
        S[user] = 10
        N += 1

        if not user in user_data:
            user_data[user] = {}

        user_data[user][artist] = int(plays)

        if not artist in artist_data:
            artist_data[artist] = []

        if not user in artist_data[artist]:
            artist_data[artist].append(user)


print("LOADED TRAINING DATA")


# Compute the global median.
plays_array = []
for user, user_data in train_data.iteritems():
    for artist, plays in user_data.iteritems():
        plays_array.append(plays)
global_median = np.median(np.array(plays_array))

print("Computed the global median.")

cnt = 0
error = float('inf')
while cnt < 10 or error > 100:
    print(cnt)

    # Calculate Xhats
    X_hats = []
    X = []
    for user, artistDict in user_data.iteritems():
        for artist, plays in artistDict.iteritems():
            X_hats.append(pred(user, artist))
            X.append(plays)

    error = MAE(X_hats, X)
    print("Error: " + error)

    if cnt % 2 == 0:
        for artist, value in P.iteritems():
            P[artist] -= p_a_grad(artist) * norm
    else:
        for user, value in S.iteritems():
            S[user] -= s_u_grad(user) * norm

    cnt += 1

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
                print "User", id, "not in training data."
                soln_csv.writerow([id, global_median])


print("All done!")
