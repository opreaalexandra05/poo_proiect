#ifndef GESTIUNE_H
#define GESTIUNE_H

#include<vector>
#include<algorithm>
#include<iostream>
#include "Produse.h"


template <typename T>
class Gestiune
{
private:
    std::vector<T> lista;
public:
    void adauga(const T& element);  //adauga elem in container
    const std::vector<T>& getToate() const; //acces controlat la datele private
    int numaraElementeScumpe(float prag) const;  //functie generica numara elem care trec peste un prag
    void curata(); // curata containerul
};

template <typename T>
void Gestiune<T>::adauga(const T& element)
{
    lista.push_back(element);  //folosim STL vector
}
template <typename T>
const std::vector<T>& Gestiune<T>::getToate() const
{
    return lista; // returneaza referinta constanta -> eficient
}

template <typename T>
int Gestiune<T>::numaraElementeScumpe(float prag) const
{
    return std::count_if(lista.begin(), lista.end(),[prag](const T& x) // folosim stl+lambda, count_if parcurge containerul automat, lambda defineste conditia de numarare
    {
        return (float)x > prag;
    });
}
template <typename T>
void Gestiune<T>::curata()
{
    lista.clear(); //pt tipuri simple: int, float etc
}
template<>
void Gestiune<ProdusCosmetic*>::curata();    //specializare template -> stergere corecta a obiectelor de pe heap (Pt pointeri la produse cosmetice, curatarea se face diferit)

template<>
int Gestiune<ProdusCosmetic*>::numaraElementeScumpe(float prag) const;
class MagazinManager  // singleton= o singura instanta in program
{
private:
    MagazinManager();  //constructor privat -> nu poti crea obiecte din exterior
    static MagazinManager* instanta;  //pointer static -> o singura instanta in program
public:
    static MagazinManager* getInstanta();  //metoda statica -> returneaza instanta unica

    void afiseazaMeniu() const; //afiseaza meniul instantei

};

#endif //OOP_GESTIUNE_H