# TEMA 2

- <h3 style="color:#ffd752">AUTOR : Avramoniu Calin-Stefan</h3>
- <h3 style="color:#ffd752">GRUPA : 312CC</h3>
- <h3 style="color:#ffd752">PUNCTAJ : <span style="color:lightgreen">69</span> puncte</h3>

<br></br>
<hr></hr>

# TASK 1 - Numerical Music

1.  <h3 style="color:lightblue">stereo_to_mono :</h3> 
    <p style="font-size:16px">Functia intoarce un vector coloana cu semnalul mono si are ca input matricea cu semnalele stereo. Folosim 'mean' asa cum spune in cerinta.</p>
2.  <h3 style="color:lightblue">apply_reverb :</h3> 
    <p style="font-size:16px">In cadrul functiei de reverb vom urma pasii indicati de cerinta pentru rezolvarea taskului. Astfel prima data vom folosi functia definita mai sus 'stereo_to_mono', apoi vom lua semnalul folosind fftconv si vom normaliza acest semnal.</p>

<br></br>
<hr></hr>

# TASK 2 - Robotzii

1.  <h3 style="color:lightgreen">parse_data:</h3> 
    <p style="font-size:16px">Se foloseste sintaxa clasica codului c (fscanf) pentru a citi datele.</p>
2.  <h3 style="color:lightgreen">spline_c2:</h3> 
    <p style="font-size:16px">Spline-ul trebuie sa treaca printoate punctele de suport date. Astfel se urmareste construirea matricei reprezentative pentru sistemul de ecuatii si se rezolva acest sistem pentru a afla coeficientii a,b,c,d ai fiecarui polinom cubic. In implementare se urmeaza pasii dati in structura initiala a functiei cerute. Astfel se verifica continuitatile atat pentru spline cat si pentru derivatele de ordinul 1 si 2 si se construieste matricea asemenea celei din enuntul problemei. La final se rezolva sistemul de ecuatii pentru a obtine vectorul de coeficienti.</p>
3.  <h3 style="color:lightgreen">P_spline:</h3> 
    <p style="font-size:16px">Vom vedea prima data numarul de intervale si numarul de puncte de interpolare, iar apoi pentru fiecare punct de interpolare vom extrage coeficientii si vom evalua spline-ul in punctul respectiv.Dupa ce gasim intervalul bun iesim din loop.</p>
4.  <h3 style="color:lightgreen">vandermonde:</h3> 
    <p style="font-size:16px">Prima data vom vedea numarul de puncte pentru interpolare, iar apoi vom construi matricea vandermond. Apoi, vom rezolva sistemul de ecuatii si vom gasi coeficientii polinomului de interpolare.</p>
5.  <h3 style="color:lightgreen">P_vandermonde:</h3> 
    <p style="font-size:16px">In aceasta functie vom calcula pentru fiecare punct de interpolare valorile polinomului de interpolare, folosindu-ne de coeficientii obtinuti in functia precedenta.</p>

<br></br>
<hr></hr>

# TASK 3 - Recommendations

1.  <h3 style="color:#c295fc">read_mat:</h3> 
    <p style="font-size:16px">Functia citeste matricea din fisierul csv.</p>
2.  <h3 style="color:#c295fc">preprocess:</h3> 
    <p style="font-size:16px">Functia preproceseaza matricea citita si scoate din aceasta toate randurile care au mai putine reviewuri decat paramaterul dat 'min_reviews'.</p>
3.  <h3 style="color:#c295fc">cosine_similarity:</h3> 
    <p style="font-size:16px">Functia implementeaza formula data in enunt, pentru a afla similaritatea dintre 2 vectori.</p>
4.  <h3 style="color:#c295fc">recommendations:</h3> 
    <p style="font-size:16px">Utilizam functiile precedente pentru a citi, a preprocesa matricea si pentru a genera vectorul de similaritate intre teme si tema apreciata. Se urmeaza algoritmul din cerinta si se implementeaza pasii in ordine. La final returnam indicii temelor recomandate.</p>