# TEMA 1

- <h3 style="color:#ffd752">AUTOR : Avramoniu Calin-Stefan</h3>
- <h3 style="color:#ffd752">GRUPA : 312CC</h3>
- <h3 style="color:#ffd752">PUNCTAJ : <span style="color:lightgreen">79</span> puncte</h3>

<br></br>

# TASK 1 - Anomaly Detection

1.  <h3 style="color:lightblue">check_predictions :</h3> 
    <p style="font-size:16px">Functia calculeaza 3 contoare pentru cele 3 metrici
    necesare (false_positives, false_negatives , true_positives).
    Acestea sunt calculate prin compararea dintre predictii
    si vectorul de adevaruri.</p>
2.  <h3 style="color:lightblue">estimate_gaussian :</h3> 
    <p style="font-size:16px">Implementam primele 2 formule din cerinta.</p>
3.  <h3 style="color:lightblue">gaussian_distribution :</h3> 
    <p style="font-size:16px">Implementarea functiei care descrie probabilitatea de aparitie din cerinta.</p>
4.  <h3 style="color:lightblue">metrics :</h3> 
    <p style="font-size:16px">Implementam functia F1 dupa formula din enunt.</p>
5.  <h3 style="color:lightblue">multivariate_gaussian :</h3> 
    <p style="font-size:16px">Calculam probabilitatile folosind functia gaussian_distribution.</p>
6.  <h3 style="color:lightblue">optimal_threshhold :</h3> 
    <p style="font-size:16px">Dorim sa salvam cel mai bun epsilon, cel mai bun F1 etc. Pentru a realiza
    acest lucru vom calcula intai probabilitatile minime si maxime, iar apoi
    vom modifica vectorul de predictii in functie de outlieri.
    Se vor folosi functiile metrics si check_predictions pentru a
    furniza datele actuale. In cele din urma acestea se compara cu vechile date cele mai bune si se inlocuiesc
    daca este cazul.</p>

<br></br>

# TASK 2 - Kernel Regression

1.  <h3 style="color:lightgreen">linear_kernel / polynomial_kernel / gaussian_kernel :</h3> 
    <p style="font-size:16px">Se implementeaza formulele furnizate in cerinta taskului.</p>
2.  <h3 style="color:lightgreen">build_kernel :</h3> 
    <p style="font-size:16px">Functia care construieste matricea kernelului, aplicand functiile anterioare asupra fiecarui
    element din matrice.</p>
3.  <h3 style="color:lightgreen">cholesky :</h3> 
    <p style="font-size:16px">Functia cholesky a fost adaptata
    pentru a putea rezolva eficient taskul din punct de vedere al timpului. Aceasta a fost adaptata dupa sursa publica: 
    <a>https://github.com/Iulian277/Numerical-Methods-Labs/blob/main/lu/cholesky.m.</a> </p>
4.  <h3 style="color:lightgreen">conjugate_gradient :</h3> 
    <p style="font-size:16px">Functia implementeaza pseudocodul furnizat in cerinta taskului.</p>
5.  <h3 style="color:lightgreen">eval_value :</h3> 
    <p style="font-size:16px">Evaluam predictia in functie de
    vectorul coloana a si functia de kernel data ca parametru.</p>
6.  <h3 style="color:lightgreen">get_lower_inverse :</h3> 
    <p style="font-size:16px">Functia calculeaza inversa unei matrice inferior triunghiulare folosind metoda eliminarii gaussiene. Functia returneaza matricea inversa
    in matricea P initializata cu matricea identitate.</p>
7.  <h3 style="color:lightgreen">get_prediction_params :</h3> 
    <p style="font-size:16px">Functia calculeaza parametrii de predictie folosind
    metoda Cholesky implementata anterior. Se foloseste o metoda neiterativa.</p>
8.  <h3 style="color:lightgreen">get_prediction_params_iterative :</h3> 
    <p style="font-size:16px">Functia calculeaza parametrii de predictie folosind
    metoda Gradientului Conjugat implementata anterior. Se foloseste o metoda iterativa.</p>
9.  <h3 style="color:lightgreen">split_dataset :</h3> 
    <p style="font-size:16px">Functia imparte setul de date furnizat in functie de un procentaj. Acesta este impartit
    intr-un set de training si alt set de testing.</p>

<br></br>

# TASK 3 - Stochastic Text Gen

1.  <h3 style="color:#c295fc">distinct_k_secv :</h3> 
    <p style="font-size:16px">Folosim unique pentru a returna secv unice sortate.</p>
2.  <h3 style="color:#c295fc">distinct_words :</h3> 
    <p style="font-size:16px">Folosim unique pentru a returna stringurile unice sortate.</p>
3.  <h3 style="color:#c295fc">k_secv :</h3> 
    <p style="font-size:16px">Functia va genera un vector ce contine secventele
    concatenate de lungime k.</p>
4.  <h3 style="color:#c295fc">k_secv_idx :</h3> 
    <p style="font-size:16px">Folosim map pentru a intoarce un dictionar de perechi (index: element).</p>
5.  <h3 style="color:#c295fc">word_idx :</h3> 
    <p style="font-size:16px">Acelasi proces ca la k_secv_idx.</p>
