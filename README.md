# Sistem de Gestiune Produse Cosmetice (Cosmetic Management System)

## 1. Descrierea Proiectului
Acest proiect reprezintă o aplicație de gestiune pentru un magazin de produse cosmetice, dezvoltată în **C++** utilizând principiile programării orientate pe obiect (**POO**). Sistemul permite administrarea unui stoc de produse (creme, skincare), gestionarea bugetului clienților și procesarea tranzacțiilor într-un mediu sigur și eficient.

## 2. Caracteristici Tehnice (Cerințe Implementate)

### A. Ierarhia de Clase și Polimorfism 
* **Clasa de Bază Abstractă**: `ProdusCosmetic` – definește interfața comună prin metoda virtuală pură `aplica()`. Implementează **Rule of Three** (Constructor de copiere, Operator=, Destructor virtual) pentru gestiunea corectă a resurselor.
* **Clase Derivate**:
    * `Skincare` (moștenește `ProdusCosmetic`) – adaugă atribute specifice precum `tipTen`.
    * `Crema` (moștenește `Skincare`) – implementează metoda `aplica()`, demonstrând polimorfismul la rulare.
* **Mecanisme avansate**: Utilizarea `dynamic_cast` (**Downcasting**) în secțiunea de statistici pentru a accesa proprietăți specifice claselor derivate.



### B. Design Patterns 
* **Singleton Pattern**: Clasa `MagazinManager` – asigură existența unei singure instanțe care gestionează meniul și fluxul aplicației.
* **Factory Pattern**: Clasa `ProdusFactory` – centralizează logica de creare a obiectelor, oferind o metodă statică pentru instanțierea produselor fără a expune logica de construcție direct în `main`.

### C. Programare Generică (Templates) și STL 
* **Clasa Template Gestiune**: Utilizată pentru a stoca diferite tipuri de date: obiecte de tip `ProdusCosmetic*` pentru magazin și tipuri primitive `int` pentru log-ul de comenzi.
* **Specializarea Template-ului**: Implementarea de logici diferite pentru metodele `curata()` și `numaraElementeScumpe()` în funcție de tipul de date stocat (pointeri vs. întregi).
* **Algoritmi STL și Lambda**: Utilizarea algoritmului `std::count_if` împreună cu o funcție **Lambda** pentru a procesa eficient elementele din containerele STL (`std::vector`, `std::set`).

### D. Gestiunea Memoriei și Structura Codului
* **Siguranță (Const-correctness)**: Utilizarea extinsă a `const` pentru metode, parametri și pointeri (ex: `const MagazinManager* manager`), garantând integritatea datelor.
* **Gestiune Dinamică**: Alocarea obiectelor cu `new` și eliberarea lor riguroasă prin metoda `curata()` din clasa template, prevenind memory leak-urile.

### E. Operatori și Excepții 
* **Supraîncărcarea Operatorilor**:
    * `operator<<` pentru afișarea polimorfică a produselor.
    * `operator>>` pentru citirea datelor clientului.
    * `operator-=` (membru) pentru actualizarea bugetului clientului.
    * `operator+` (non-membru) pentru calculul bonusurilor bugetare.
* **Tratarea Excepțiilor**: Utilizarea ierarhiei custom `ErroareMagazin` -> `ErroareBuget` (derivată din `std::exception`). Se demonstrează propagarea excepțiilor și **Upcasting-ul în blocurile catch**.

## 3. Fluxul Aplicației
1.  **Inițializare**: Se încarcă stocul din `produse_stoc.txt` și se afișează numărul de obiecte create prin variabila statică `nrTotalProduse`.
2.  **Interacțiune**: Utilizatorul interacționează prin meniul Singleton, având opțiuni de afișare, cumpărare (procesată cu excepții) sau statistici (procesate cu algoritmi STL).
3.  **Finalizare**: Se afișează istoricul procesat prin clasa template și se eliberează memoria alocată dinamic.
