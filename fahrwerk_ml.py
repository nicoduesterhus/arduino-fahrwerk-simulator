import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

daten = pd.read_csv("daten.csv", names=["zeit", "abstand", "winkel", "situation"])

# Chronologischer Split je Klasse: erste 80 % Training, letzte 20 % Test.
# Kein zufaelliger Split, weil aufeinanderfolgende Messwerte stark korreliert sind
# und die Genauigkeit sonst zu optimistisch ausfaellt.
train, test = [], []
for _, gruppe in daten.groupby("situation", sort=False):
    grenze = int(len(gruppe) * 0.8)
    train.append(gruppe.iloc[:grenze])
    test.append(gruppe.iloc[grenze:])
train = pd.concat(train)
test = pd.concat(test)

merkmale = ["abstand", "winkel"]
modell = DecisionTreeClassifier(max_depth=4, random_state=0)
modell.fit(train[merkmale], train["situation"])

genauigkeit = accuracy_score(test["situation"], modell.predict(test[merkmale]))
print(f"Genauigkeit: {genauigkeit * 100:.1f}%")

probe = pd.DataFrame([[5, 90], [15, 90], [28, 90]], columns=merkmale)
for abstand, vorhersage in zip(probe["abstand"], modell.predict(probe)):
    print(f"Abstand {abstand:>2} cm -> {vorhersage}")