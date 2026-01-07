# Sistem de Gestiune Produse Cosmetice (Cosmetic Management System)

## 1. Descrierea Proiectului

Acest proiect reprezintă o aplicație de gestiune pentru un magazin de produse cosmetice, dezvoltată în C++ utilizând principiile programării orientate pe obiect (POO). Sistemul permite administrarea unui stoc de produse (creme, seruri etc.), gestionarea bugetului clienților și procesarea tranzacțiilor.

## 2. Caracteristici Tehnice (Cerințe Implementate)

### A. Ierarhia de Clase și Polimorfism
-> Clasa de Bază Abstractă: ProdusCosmetic – definește interfața comună (metoda virtuală pură aplica()).

-> Clase Derivate:

~ Skincare (moștenește ProdusCosmetic) – adaugă atribute specifice precum tipTen.

~ Crema (moștenește Skincare) – implementează metoda aplica(), demonstrând polimorfismul la rulare.

### B. Design Patterns
-> Singleton Pattern: Clasa MagazinManager – asigură existența unei singure instanțe care gestionează meniul și fluxul aplicației.

-> Factory Pattern: Clasa ProdusFactory – centralizează logica de creare a obiectelor, oferind o metodă statică pentru instanțierea produselor fără a expune logica de construcție direct în main.

### C. Programare Generică (Templates)
-> Clasa Template Gestiune<T>: Utilizată pentru a stoca diferite tipuri de date (obiecte de tip ProdusCosmetic* pentru magazin și tipuri primitive int pentru log-ul de comenzi).

-> Specializarea Template-ului: Implementarea de logici diferite pentru metodele curata() și numaraProduseCuProtectie() în funcție de tipul de date stocat (pointeri vs. întregi), asigurând compatibilitate și eficiență.

### D. Gestiunea Memoriei și Siguranță
-> Gestionarea riguroasă a constantelor: Utilizarea extinsă a cuvântului cheie const pentru metode, parametri (referințe constante) și pointeri, garantând integritatea datelor.

-> Gestiunea dinamică: Alocarea obiectelor cu new și eliberarea riguroasă a acestora prin metoda curata(), verificată prin tool-uri de analiză (Valgrind) pentru a preveni memory leak-urile.

### E. Operatori și Excepții
-> Supraîncărcarea Operatorilor:

~ operator<< pentru afișarea polimorfică a produselor.

~ operator>> pentru citirea datelor clientului.

~ operator-= pentru actualizarea bugetului clientului.

-> Tratarea Excepțiilor: Utilizarea blocurilor try-catch și a unei clase custom ErroareMagazin (derivată din std::exception) pentru a gestiona situații precum bugetul insuficient.

## 3. Fluxul Aplicației
-> Inițializare: Se încarcă stocul de produse dintr-un fișier extern (produse_stoc.txt) și se afișează numărul de obiecte create prin variabila statică nrTotalProduse.

-> Interacțiune: Utilizatorul (Clientul) poate vedea stocul, cumpăra produse sau vizualiza statistici (ex: tipuri de ten identificate prin dynamic_cast).

-> Finalizare: Se afișează istoricul comenzilor folosind clasa template și se eliberează memoria.
