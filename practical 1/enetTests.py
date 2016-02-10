# File with ridge, lasso, and enet tests

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from sklearn.linear_model import LinearRegression, Ridge, Lasso, ElasticNet, lasso_path, enet_path

df_train = pd.read_csv("train.csv")
df_test = pd.read_csv("test.csv")

def write_to_file(filename, predictions):
    with open(filename, "w") as f:
        f.write("Id,Prediction\n")
        for i,p in enumerate(predictions):
            f.write(str(i+1) + "," + str(p) + "\n")

print("Loading data")
#store gap values
Y_train = df_train.gap.values
#delete 'Id' column
df_test = df_test.drop(['Id'], axis=1)
#delete 'gap' column
df_train = df_train.drop(['gap'], axis=1)
df_train = df_train
X_test = np.vstack(df_test.drop(['smiles'], axis=1).values)

df_train = df_train.drop(['smiles'], axis=1)
base_X = np.vstack(df_train.values)
base_Y = np.vstack(Y_train)

print("Doing ridge regression")
clf = Ridge(alpha=1.0)
clf.fit(base_X, base_Y)
print "Score = %f" % clf.score(base_X, base_Y)
clf_pred = clf.predict(X_test)
write_to_file("ridge.csv", clf_pred)


print ("Doing lasso regression")
clf2 = Lasso(alpha=1e-4)
clf2.fit(base_X, base_Y)
print "Score = %f" % clf2.score(base_X, base_Y)
clf2_pred = clf2.predict(X_test)
write_to_file("lasso.csv", clf2_pred)

print ("Doing elastic net")
clf3 = ElasticNet(alpha=1e-4)
clf3.fit(base_X, base_Y)
print "Score = %f" % clf3.score(base_X, base_Y)
clf3_pred = clf3.predict(X_test)
write_to_file("elastic.csv", clf3_pred)

# LASSO/ENET PATH CALCULATIONS
# Not sure how to make predictions with this...

# eps = 5e-3

# print("Computing lasso")
# alphas_lasso, coefs_lasso, _ = lasso_path(
# 	base_X, base_Y, eps, fit_intercept=False)

# print("Computing positive lasso")
# alphas_positive_lasso, coefs_positive_lasso, _ = lasso_path(
# 	base_X, base_Y, eps, positive=True, fit_intercept=False)

# print("Computing elastic net")
# alphas_enet, coefs_enet, _ = enet_path(
# 	base_X, base_Y, eps=eps, l1_ratio=0.8, fit_intercept=False)

# print("Computing positive elastic net")
# alphas_positive_enet, coefs_positive_enet, _ = enet_path(
# 	base_X, base_Y, eps=eps, l1_ratio=0.8, positive=True, fit_intercept=False)
