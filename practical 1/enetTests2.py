# File with ridge, lasso, and enet tests

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from rdkit import Chem
from rdkit.Chem import AllChem
from rdkit.Chem import ChemicalFeatures
from rdkit import RDConfig
import os
from sklearn import cross_validation
from sklearn.linear_model import LinearRegression, Ridge, Lasso, ElasticNet, ElasticNetCV, LassoLarsCV

fdefName = os.path.join(RDConfig.RDDataDir,'BaseFeatures.fdef')
factory = ChemicalFeatures.BuildFeatureFactory(fdefName)

fpl = 512


df_train_new = pd.read_csv("base_X2.csv")
df_y_train = pd.read_csv("y_train.csv")

def write_to_file(filename, predictions):
    with open(filename, "w") as f:
        f.write("Id,Prediction\n")
        for i,p in enumerate(predictions):
            f.write(str(i+1) + "," + str(p) + "\n")


def write_to_inp_file(filename, table):

    print("writing " + filename)
    with open(filename, "w") as f:
        f.write("gap")
        # for i in range(1,fpl):
        #     f.write(", bit" + str(i))
        f.write("\n")
        for row in table:
            # for el in row[:-1]:
            #     f.write(str(el) + ", ")
            f.write(str(row)+ "\n")

# function for generating features from molecules
def getfeat(smile_array):
    feats = []
    for smile in smile_array:
        bin_array = [0]*50
        m = Chem.MolFromSmiles(smile)
        f = factory.GetFeaturesForMol(m)
        for feat in f:
            bin_array[feat.GetId()] = 1
        feats.append(bin_array[1:])
    return feats

# Function for generationg morgan fingerprints as inputs
def fp_factory(smile_array, length, radius):
    data_array = []
    for i,smile in enumerate(smile_array):
        if i % 10000 == 0 : print(i)
        m = Chem.MolFromSmiles(smile)
        data_array.append((AllChem.GetMorganFingerprintAsBitVect(
            m, radius, nBits=length)).ToBitString())
    data_array = np.array(data_array)
    return np.array([list(fp_string) for fp_string in data_array], dtype=int)

print("Loading data :)")
#store gap values
# X_test = (fp_factory(df_test.smiles.values, fpl, 2))
# write_to_inp_file("X_test2.csv", X_test)
# base_X = np.vstack(fp_factory(df_train.smiles.values, fpl, 2))
# write_to_inp_file("base_X2.csv", base_X)
base_Y = np.vstack(df_y_train.values)
base_X = df_train_new.values

def ridgereg(a):
    print("Doing ridge regression")
    clf = Ridge(alpha=a)
    clf.fit(base_X, base_Y)
    print ("Score = %f" % clf.score(base_X, base_Y))
    df_test_new = pd.read_csv("X_test2.csv")
    X_test = df_test_new.values
    clf_pred = clf.predict(X_test)
    write_to_file("ridge.csv", clf_pred)

def lassoreg(a):
    print ("Doing lasso regression")
    clf2 = Lasso(alpha=a)
    clf2.fit(base_X, base_Y)
    print ("Score = %f" % clf2.score(base_X, base_Y))
    df_test_new = pd.read_csv("X_test2.csv")
    X_test = df_test_new.values
    clf2_pred = clf2.predict(X_test)
    write_to_file("lasso.csv", clf2_pred)

def enet(a):
    print ("Doing elastic net")
    clf3 = ElasticNet(alpha=a)
    clf3.fit(base_X, base_Y)
    print ("Score = %f" % clf3.score(base_X, base_Y))
    df_test_new = pd.read_csv("X_test2.csv")
    X_test = df_test_new.values
    clf3_pred = clf3.predict(X_test)
    write_to_file("elastic.csv", clf3_pred)

def enetCV():
    print ("Doing elastic net")
    cross_val = cross_validation.ShuffleSplit(len(base_X), n_iter=5, test_size=0.2, random_state=0)
    clf4 = ElasticNetCV(cv=cross_val)
    clf4.fit(base_X, base_Y)
    print ("Score = %f" % clf4.score(base_X, base_Y))
    df_test_new = pd.read_csv("X_test2.csv")
    X_test = df_test_new.values
    clf4_pred = clf4.predict(X_test)
    write_to_file("elasticCV.csv", clf4_pred)

def lassolarscv():
    print ("Doing cross-validated LassoLars")
    cross_val = cross_validation.ShuffleSplit(len(base_X), n_iter=5, test_size=0.2, random_state=0)
    clf5 = LassoLarsCV(cv=cross_val)
    clf5.fit(base_X, base_Y)
    print ("Score = %f" % clf5.score(base_X, base_Y))
    df_test_new = pd.read_csv("X_test2.csv")
    X_test = df_test_new.values
    clf5_pred = clf5.predict(X_test)
    write_to_file("lassolars.csv", clf5_pred)

# enetCV()
# lassolarscv()
