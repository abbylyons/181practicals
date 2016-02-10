# File with ridge, lasso, and enet tests

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from rdkit import Chem
from rdkit.Chem import ChemicalFeatures
from rdkit import RDConfig
import os
from sklearn import cross_validation
from sklearn.linear_model import LinearRegression, Ridge, Lasso, ElasticNet, ElasticNetCV, LassoLarsCV

fdefName = os.path.join(RDConfig.RDDataDir,’BaseFeatures.fdef’)
factory = ChemicalFeatures.BuildFeatureFactory(fdefName)

df_train = pd.read_csv("train.csv")
df_test = pd.read_csv("test.csv")

def write_to_file(filename, predictions):
    with open(filename, "w") as f:
        f.write("Id,Prediction\n")
        for i,p in enumerate(predictions):
            f.write(str(i+1) + "," + str(p) + "\n")

def getfeat(smile_array):

    feats = []
    for smile in smile_array:
        m = Chem.MolFromSmiles(smile)
        feats.append(factory.GetFeaturesForMol(m))
    return np.vstack(feats)

print("Loading data :)")
#store gap values
Y_train = df_train.gap.values
X_test = getfeat(df_test.smiles.values)
base_X = getfeat(df_train.smiles.values)
base_Y = np.vstack(Y_train)


def ridgereg(a):
    print("Doing ridge regression")
    clf = Ridge(alpha=a)
    clf.fit(base_X, base_Y)
    print ("Score = %f" % clf.score(base_X, base_Y))
    clf_pred = clf.predict(X_test)
    write_to_file("ridge.csv", clf_pred)

def lassoreg(a):
    print ("Doing lasso regression")
    clf2 = Lasso(alpha=a)
    clf2.fit(base_X, base_Y)
    print ("Score = %f" % clf2.score(base_X, base_Y))
    clf2_pred = clf2.predict(X_test)
    write_to_file("lasso.csv", clf2_pred)

def enet(a):
    print ("Doing elastic net")
    clf3 = ElasticNet(alpha=a)
    clf3.fit(base_X, base_Y)
    print ("Score = %f" % clf3.score(base_X, base_Y))
    clf3_pred = clf3.predict(X_test)
    write_to_file("elastic.csv", clf3_pred)

def enetCV():
    print ("Doing elastic net")
    cross_val = cross_validation.ShuffleSplit(len(base_X), n_iter=5, test_size=0.2, random_state=0)
    clf4 = ElasticNetCV(cv=cross_val)
    clf4.fit(base_X, base_Y)
    print ("Score = %f" % clf4.score(base_X, base_Y))
    clf4_pred = clf4.predict(X_test)
    write_to_file("elasticCV.csv", clf4_pred)

def lassolarscv():
    print ("Doing cross-validated LassoLars")
    cross_val = cross_validation.ShuffleSplit(len(base_X), n_iter=5, test_size=0.2, random_state=0)
    clf5 = LassoLarsCV(cv=cross_val)
    clf5.fit(base_X, base_Y)
    print ("Score = %f" % clf5.score(base_X, base_Y))
    clf5_pred = clf5.predict(X_test)
    write_to_file("lassolars.csv", clf5_pred)

enetCV()
lassolarscv()

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
