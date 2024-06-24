import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

##### CERINTA 1

print ("================================== CERINTA 1 ==================================")
print ("\n")

df = pd.read_csv('train.csv')

numar_coloane = len(df.columns)
numar_linii = len(df)
numar_linii_duplicate = df.duplicated().sum()


print ("Nr col: ", numar_coloane)
print ("Nr linii: ", numar_linii)
print ("Nr linii duplicate: ", numar_linii_duplicate)
print ("\n")

print (df.info())
print ("\n")

valori_lipsa = df.isnull().sum()
print ("Valori lipsa pe fiecare coloana: ")
print (valori_lipsa)
print ("\n")

##### CERINTA 2

nr_supravietuitori = df['Survived'].sum()
nr_morti = numar_linii - nr_supravietuitori

# calculam procentajele pentru morti si supravietuitori
procent_supravietuitori = ((nr_supravietuitori / numar_linii) * 100).round(2)
procent_morti = ((nr_morti / numar_linii) * 100).round(2)

# calculam procentajele pe cele 3 clase
procent_pasageri_clasa1 = ((len(df[df["Pclass"] == 1]) / numar_linii) * 100)
procent_pasageri_clasa2 = ((len(df[df["Pclass"] == 2]) / numar_linii) * 100)
procent_pasageri_clasa3 = ((len(df[df["Pclass"] == 3]) / numar_linii) * 100)

# calc procentajele pentru barbati si femei
procent_barbati = (len(df[df["Sex"] == "male"]) / numar_linii * 100)
procent_femei = (len(df[df["Sex"] == "female"]) / numar_linii * 100)

new_df = pd.DataFrame({
    "Supravietuitori": [procent_supravietuitori],
    "Morti": [procent_morti]
})

new_df.plot(kind='bar', color=['green', 'red'])
plt.title('Procent supravietuitori si morti')
plt.show()

new_df1 = pd.DataFrame({
    "Pclass": ["1", "2", "3"],
    "Procent": [procent_pasageri_clasa1, procent_pasageri_clasa2, procent_pasageri_clasa3]
})

new_df1.plot(kind='bar', x='Pclass', y='Procent', color='blue')
plt.title('Procent pasageri pe clase')
plt.show()

new_df2 = pd.DataFrame({
    "Sex": ["Barbati", "Femei"],
    "Procent": [procent_barbati, procent_femei]
})

new_df2.plot(kind='bar', x="Sex", y="Procent", color='red')
plt.title('Procent barbati si femei')
plt.show()


##### CERINTA 3

col_num = df.select_dtypes(include=['int64', 'float64']).columns

# afisam hostogramele pentru fiecare coloana numerica
df[col_num].hist(bins=15, figsize=(15, 6), layout=(2, 4))
plt.show()

##### CERINTA 4

print ("================================== CERINTA 4 ==================================")
print ("\n")

procent_val_lipsa = (valori_lipsa / numar_linii * 100).round(2)
print ("Procent valori lipsa pe fiecare coloana: ")
print (procent_val_lipsa)

print ("\n")

##### CERINTA 5

# categorizam varsta in 4 categorii
categorii_varsta = pd.cut(df['Age'], bins=[0, 20, 40, 60, df["Age"].max()], labels=['0-20', '21-40', '41-60', '61-max'])

# adaugam coloana 'Categorie varsta' in dataframe
df['Categorie varsta'] = categorii_varsta

nr_pasageri_categorie = df['Categorie varsta'].value_counts()

nr_pasageri_categorie.plot(kind='bar', color='purple')
plt.title('Numar pasageri pe categorii de varsta')
plt.xlabel('Categorie varsta')
plt.ylabel('Numar pasageri')
plt.show()

##### CERINTA 6

barbati = df[df["Sex"] == "male"]

# grupam dupa 'Categorie varsta' si numaram supravietuitorii
barbatii_supravietuitori_categorii = barbati['Survived'].groupby(barbati['Categorie varsta'], observed=True).sum()

barbatii_supravietuitori_categorii.plot(kind='bar', color='green' , title='Numar barbati supravietuitori pe categorii de varsta')
plt.xlabel('Categorie varsta')
plt.ylabel('Numar supravietuitori')
plt.show()

##### CERINTA 7

# separam pasagerii in 2 categorii: minori si adulti
minori = df[df["Age"] < 18]
adulti = df[df["Age"] >= 18]

# numaram supravietuitorii din fiecare categorie
minori_supravietuitori = minori['Survived'].sum()
adulti_supravietuitori = adulti['Survived'].sum()

# calc procentajul de copii
procent_copii = len(minori) / numar_linii * 100

print ("================================== CERINTA 7 ==================================")
print ("\n")
print ("Procent copii: ", procent_copii)
print ("\n")

# calc procentajul supravietuitorilor atat pentru copii cat si pentru adulti
procent_supravietuitori_copii = minori_supravietuitori / len(minori) * 100
procent_supravietuitori_adulti = adulti_supravietuitori / len(adulti) * 100

plt.bar(['Copii', 'Adulti'], [procent_supravietuitori_copii, procent_supravietuitori_adulti], color=['blue', 'red'])
plt.title('Procent supravietuitori copii si adulti')
plt.show()

##### CERINTA 8

print ("================================== CERINTA 8 ==================================")
print ("\n")

# afisam inainte de completare
print (df.info())

# pentru fare si age completam cu media
df.fillna({'Fare': df['Fare'].mean()}, inplace=True)
df.fillna({'Age': df['Age'].mean()}, inplace=True)

# pentru Embarked si Categorie varsta completam cu valoarea care apare cel mai des (folosim mode)
df.fillna({'Embarked': df['Embarked'].mode()[0]}, inplace=True)
df.fillna({'Categorie varsta': df['Categorie varsta'].mode()[0]}, inplace=True)

# afisa dupa completare
print (df.info())

# salvam in noul fisier csv dataframe-ul completat
df.to_csv('rezultate_cerinta8.csv' , index=False)

##### CERINTA 9

# vector cu titlurile
titles = ['Mr.', 'Miss.', 'Mrs.', 'Dr.', 'Col.', 'Don.', 'Master.', 'Rev.' , 'Ms.' , 'Major' , 'Lady' , 'Sir', 'Countess' , 'Jonkheer' , 'Capt' , 'Mme' , 'Mlle']

# numarul de persoane pt fiecare titlu
counts = []

for title in titles:
    if 'Mr.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Dr.' in title:
        count = len(df[df['Name'].str.contains(title)])
    elif 'Col.' in title:
        count = len(df[df['Name'].str.contains(title)])
    elif 'Mrs.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
    elif 'Don.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Miss.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
    elif 'Master.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Rev.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Ms.' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
    elif 'Major' in title:
        count = len(df[df['Name'].str.contains(title)])
    elif 'Lady' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')]) 
    elif 'Sir' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Countess' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
    elif 'Jonkheer' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'male')])
    elif 'Capt' in title:
        count = len(df[df['Name'].str.contains(title)])
    elif 'Mme' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
    elif 'Mlle' in title:
        count = len(df[df['Name'].str.contains(title) & (df['Sex'] == 'female')])
        
    counts.append(count)
        
plt.bar(titles, counts , color='orange')
plt.title('Numar persoane cu titlu si sex corespunzator')
plt.xlabel('Titlu')
plt.ylabel('Numar persoane')
plt.xticks(rotation=90)
plt.tight_layout()
plt.size = (15, 6)
plt.show()

##### CERINTA 10

# facem o coloana noua 'Alone' care sa indice daca pasagerul este singur sau nu
# 1 - singur, 0 - nu este singur
df['Alone'] = (df['SibSp'] + df['Parch'] == 0).astype(int)

# grupam dupa coloana 'Alone' si numaram supravietuitorii singuri
supravietuitori_singuri = df['Survived'].groupby(df['Alone']).sum()
procent_supravietuitori_singuri = supravietuitori_singuri / numar_linii * 100

# calc procentajul de morti scazand din 100 procentajul de supravietuitori
procent_morti_singuri = 100 - procent_supravietuitori_singuri

plt.pie(procent_supravietuitori_singuri, labels=['Supravietuitori', 'Morti'], colors=['green', 'red'], autopct='%1.1f%%')
plt.title('Persoane singure')
plt.show()

# folosim head pt a lua primele 100 de randuri
primele_100 = df.head(100)
sns.catplot(x='Pclass', y='Fare', data=primele_100, hue='Survived', kind='swarm', palette='Set1' , height=6, aspect=2)
plt.show()