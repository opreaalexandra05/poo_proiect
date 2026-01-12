# Sistem de Gestiune Produse Cosmetice (Cosmetic Management System)

## 1. Descrierea Proiectului
Acest proiect implementează o soluție software pentru gestiunea stocurilor și procesarea tranzacțiilor într-un magazin de produse cosmetice. Dezvoltată în standardul C++23, aplicația demonstrează aplicarea corectă a principiilor fundamentale ale Programării Orientate pe Obiect (POO) într-un context de business simulat.

## 2. Arhitectura Sistemului și Mecanisme POO

### A. Polimorfism Dinamic și Ierarhii de Clase
Proiectul utilizează mecanismul de Late Binding pentru a asigura extensibilitatea și flexibilitatea sistemului:
* **Metode Virtuale Pure**: Clasele de bază `Persoana` și `ProdusCosmetic` definesc interfețe abstracte. Metoda `virtual void aplicaDiscountFidelitate(float procent)` este pilonul central al polimorfismului în ierarhia de persoane.
* **Logica de Business Polimorfică**: Implementarea metodei de discount în clasa `Client` nu se rezumă la afișare, ci realizează interogarea stării interne (`esteFidel()`), calcule matematice de precizie și actualizarea atributelor prin interacțiunea cu operatorii supraîncărcați.
* **Upcasting**: Procesarea clienților în funcția `main` se realizează prin pointeri la clasa de bază (`Persoana*`), permițând tratarea uniformă a diferitelor tipuri de utilizatori ai sistemului.



### B. Design Patterns
* **Singleton Pattern**: Clasa `MagazinManager` garantează existența unei instanțe unice la nivel de aplicație pentru coordonarea meniului și a fluxului de execuție.
* **Factory Pattern**: Clasa `ProdusFactory` încapsulează logica de instanțiere a obiectelor din ierarhia de produse, izolând restul aplicației de detaliile de construcție a obiectelor pe Heap.

### C. Programare Generică și STL
* **Clase Template**: `Gestiune<T>` asigură un container abstract utilizat atât pentru obiecte complexe (pointeri), cât și pentru tipuri primitive.
* **Specializarea Template-ului**: Metodele `curata()` și `numaraElementeScumpe()` sunt specializate pentru tipul `ProdusCosmetic*` pentru a asigura gestionarea corectă a memoriei și accesul la metodele specifice clasei.
* **Algoritmi STL și Lambda**: Integrarea algoritmului `std::count_if` cu funcții anonime (Lambda) pentru procesarea eficientă a colecțiilor de date.

### D. Gestiunea Memoriei și Regula celor Trei
* **Destructori Virtuali**: Implementați în toate clasele de bază pentru a asigura eliberarea completă a resurselor și apelarea corectă a destructorilor claselor derivate.
* **Memory Safety**: Eliberarea riguroasă a obiectelor alocate dinamic prin specializarea metodei `curata()` în clasa template, eliminând riscul apariției memory leak-urilor.

## 3. Supraîncărcarea Operatorilor și Tratarea Excepțiilor

### Supraîncărcarea Operatorilor
* **Operatorul -=**: Implementat ca funcție membră pentru procesarea decrementării bugetului în urma achizițiilor.
* **Operatorul +**: Implementat ca funcție non-membră pentru calculul bonusurilor bugetare, asigurând o sintaxă matematică naturală în logica de fidelizare.
* **Operatorii de Stream (<<, >>)**: Supraîncărcați pentru a facilita serializarea și deserializarea obiectelor de tip Client și ProdusCosmetic.

### Gestiunea Erorilor
Aplicația implementează o ierarhie proprie de excepții derivată din `std::exception`:
* **ErroareMagazin**: Clasa de bază pentru tratarea unitară a erorilor.
* **ErroareBuget și ErroareStoc**: Excepții specializate pentru gestionarea fondurilor insuficiente, respectiv a accesului la indici nevalizi în stoc.
* **Upcasting în blocurile Catch**: Demonstrează capacitatea sistemului de a intercepta polimorfic diferite tipuri de erori printr-o singură referință la clasa de bază.



## 4. Structura Fișierelor și Fluxul de Date
1. **produse_stoc.txt**: Sursa de date pentru popularea inventarului (Nume, Preț, Proprietăți specifice).
2. **tastatura.txt**: Simulează datele de intrare ale utilizatorului și succesiunea operațiunilor de testare a sistemului.
