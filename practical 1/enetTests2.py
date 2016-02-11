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

fdefName = os.path.join(RDConfig.RDDataDir,'BaseFeatures.fdef')
factory = ChemicalFeatures.BuildFeatureFactory(fdefName)

df_train = pd.read_csv("train.csv")
df_train = df_train.head(1000)
df_test = pd.read_csv("test.csv")
df_test = df_test.head(1000)

def write_to_file(filename, predictions):
    with open(filename, "w") as f:
        f.write("Id,Prediction\n")
        for i,p in enumerate(predictions):
            f.write(str(i+1) + "," + str(p) + "\n")

def getfeat(smile_array):
    feats = []
    featIds = []
    min = 6
    maxId = 0
    for smile in smile_array:
        m = Chem.MolFromSmiles(smile)
        f = factory.GetFeaturesForMol(m)
        #if (len(f) < min): min = len(f)
        feats.append(f[:min])
    for m in range(0, len(feats)):
    	for n in range(0, len(feats[m])):
    		if (feats[m][n].GetId() > maxId): maxId = feats[m][n].GetId()
    	#feats[m] = feats[m][:min]
    print(maxId)
    return np.vstack(featIds)

print("Loading data :)")
#store gap values
Y_train = df_train.gap.values
print(Y_train)
print(Y_train.shape)
X_test = getfeat(df_test.smiles.values)
base_X = getfeat(df_train.smiles.values)
base_Y = np.vstack(Y_train)
print(base_Y)


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
    print(base_X.shape)
    print(base_Y.shape)
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
