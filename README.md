# Beauty & Skincare Manager

### Sistem de gestiune și consultanță cosmetică implementat în C++

Acest proiect reprezintă o aplicație modulară pentru administrarea unui portofoliu de produse de îngrijire a tenului și simularea procesului de achiziție pentru clienți. Programul pune accent pe recomandări personalizate bazate pe tipul de ten și demonstrează utilizarea avansată a conceptelor de Programare Orientată pe Obiecte (POO).

## Arhitectura Claselor și Ierarhia POO

A. Ierarhia Produselor

Sistemul utilizează moștenirea pentru a modela specializarea produselor:

-> ProdusCosmetic (Clasa de bază): Este o clasă abstractă. Aceasta forțează toate produsele să aibă un nume și un preț, dar lasă implementarea metodei aplica() pe seama claselor derivate (prin conceptul de interfață).

-> Skincare (Clasă intermediară): Extinde proprietățile de bază prin adăugarea atributului tipTen. Aceasta servește drept punte pentru toate produsele destinate îngrijirii tenului.

-> Crema (Clasă concretă): Reprezintă un produs final care adaugă atributul spf. Aici se implementează logica specifică de utilizare a produsului.

B. Modulul de Clienți (Persoana.h)

Clasa Client gestionează starea utilizatorului. Aceasta include:

-> Încapsularea: Bugetul este privat, putând fi modificat doar prin metoda cumparaProdus, care verifică validitatea tranzacției.

-> Istoric: Folosește un std::vector<std::string> pentru a memora cronologic achizițiile.

## Concepte avansate implementate

### I. Polimorfism la Runtime

Datorită clasei abstracte, putem folosi Polimorfismul. În clasa Gestiune, avem un std::vector<ProdusCosmetic*>. Chiar dacă vectorul conține pointeri la clasa de bază, programul apelează versiunea corectă a funcțiilor (de exemplu, afisare sau aplica) pentru fiecare obiect în parte (Cremă, etc.).

### II. Programare Generică (Templates)

Clasa Gestiune<T> este un motor generic de stocare.

Avantaj: Poate gestiona orice tip de obiect.

Curățarea Memoriei: Include un mecanism automat de tip "Garbage Collection" manual prin metoda curata(), care șterge pointerii pentru a evita pierderile de memorie.

### III. RTTI și Dynamic Cast

În modulul de consultanță, folosim dynamic_cast<Skincare*>(p) pentru a verifica dacă un produs generic are proprietăți de îngrijire a tenului. Dacă cast-ul reușește, putem accesa metode specifice (ca getTipTen()), care nu există în clasa de bază abstractă.

### IV. Tratarea Erourilor (Excepții)

Am implementat clasa ErroareBuget, derivată din std::exception.

Sistemul aruncă (throw) o excepție dacă prețul produsului depășește bugetul clientului.

Logica este izolată într-un bloc try-catch, asigurând o experiență de utilizare fluidă fără prăbușirea programului.


## Detalii de implementare

### Operatorul << (Non-membru)

Am ales să supraîncarc operator<< ca funcție non-membră pentru a respecta convenția standard C++, permițând sintaxa std::cout << *produs. Aceasta apelează intern metoda virtuală afisare, combinând astfel supraîncărcarea cu polimorfismul.

### Rule of Three

Clasa ProdusCosmetic implementează:

~ Destructor Virtual: Esențial pentru curățarea corectă a obiectelor derivate.

~ Constructor de Copiere: Garantează că la copierea unui produs, datele sunt transferate corect.

~ Operator de Atribuire (operator=): Previne auto-atribuirea și gestionează copierea valorilor.

## Detalii de gestiune a memoriei 

### -> Destructor Virtual: 
Clasa abstractă ProdusCosmetic are un destructor virtual. Acest lucru este vital: când ștergem un pointer de tip ProdusCosmetic* care arată către o Crema, destructorul virtual asigură că toate resursele sunt eliberate corect, începând de la clasa derivată spre cea de bază.

### -> Membri Statici: 
Variabila nrTotalProduse (static) monitorizează volumul de date procesat pe parcursul sesiunii, fiind independentă de instanțele individuale.

## Exemplu de flux de date

Input: Programul citește n produse din produse_stoc.txt.

Procesare: Consultantul filtrează stocul comparând tipTen din obiectul de tip Skincare cu input-ul utilizatorului.

Output: Se afișează recomandarea, se scade prețul din buget și se actualizează istoricul.
