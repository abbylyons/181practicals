import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Ridge
from sklearn.preprocessing import PolynomialFeatures
from sklearn import cross_validation
from rdkit import Chem, DataStructs
from rdkit.Chem import AllChem
from rdkit.Chem import Descriptors

limiter = -1

df_train = pd.read_csv("train.csv")
df_test = pd.read_csv("test.csv")

def write_to_file(filename, predictions):
    with open(filename, "w") as f:
        f.write("Id,Prediction\n")
        for i,p in enumerate(predictions):
            f.write(str(i+1) + "," + str(p[0]) + "\n")



# LOADING DATA

print("Loading data")
#store gap values
Y_train = df_train.gap.values
#delete 'Id' column
df_test = df_test.drop(['Id'], axis=1)
#delete 'gap' column
df_train = df_train.drop(['gap'], axis=1)
df_train = df_train
X_test = np.vstack(df_test.drop(['smiles'], axis=1).values)


print("Generating molecules and fingerprints")
# generate molecules from smiles
# mols = []

# for smile in df_train.smiles:
#     mols.append(Chem.MolFromSmiles(smile))

# generate values

# TPSA value from molecules
# fps = [Descriptors.TPSA(m) for m in mols]
# df_train['feat'] = pd.DataFrame(np.vstack(fps))

# drop smiles column
df_train = df_train.drop(['smiles'], axis=1)
base_X = np.vstack(df_train.values)
base_Y = np.vstack(Y_train)

# Sum up the features
# sums = [row.sum() for row in df_train.values]
# X_train = df_train.feat.values


print("Running tests")
# total_scores = []
# for i in range(1, 100):
#     cross_val = cross_validation.ShuffleSplit(len(base_X), n_iter=3, test_size=0.2, random_state=0)
#     clf = Ridge(alpha=i, copy_X=True)
#     total_scores.append(cross_validation.cross_val_score(clf, base_X, base_Y, scoring='mean_squared_error', cv=cross_val).mean())
#
clf = Ridge(alpha=1.6)
clf.fit(base_X, base_Y)
clf_pred = clf.predict(X_test)
write_to_file("ridge.csv", clf_pred)

#
# #This will print the mean of the list of errors that were output and
# # provide your metric for evaluation
# for i in range(1, 100):
#     print("alpha: " + str(i*0.2) + " -> score: " + str(total_scores[i-1]))
#
# # Plot the data.
# plt.plot(range(1, 100), total_scores, 'o')
# plt.xlabel("alpha")
# plt.ylabel("Score")
# plt.show()


# THIS IS ALL FOR LIN REGRESSION WITH POLYNOMIAL BASIS

# generate test sets
# print("Generating test sets")

# base_X = np.vstack(np.array(sums)[:limiter])
# base_Y = np.vstack(Y_train[:limiter])
# new_Xs = []
# for i in range(1, 10):
#     poly = PolynomialFeatures(degree=i)
#     new_Xs.append(poly.fit_transform(base_X))
# run tests

# print("Running tests")
# total_scores = []
# for i in range(len(new_Xs)):
#     cross_val = cross_validation.ShuffleSplit(len(new_Xs[i]), n_iter=3, test_size=0.2, random_state=0)
#     LR = LinearRegression()
#     Xs = np.array(new_Xs[i])
#     Ys = np.array(base_Y)
#     total_scores.append(cross_validation.cross_val_score(LR, Xs, Ys, scoring='mean_squared_error', cv=cross_val,).mean())
#
# # This will print the mean of the list of errors that were output and
# # provide your metric for evaluation
# for i in range(len(total_scores)):
#     print("degree: " + str(i+1) + " -> score: " + str(total_scores[i]))
#
# # Plot the data.
# plt.plot(range(1, 10), total_scores, 'o')
# plt.xlabel("Degree")
# plt.ylabel("Score")
# plt.show()


# LR = LinearRegression()
# LR.fit(X_train, Y_train)
# LR_pred = LR.predict(X_test)
# write_to_file("sample1.csv", LR_pred)
