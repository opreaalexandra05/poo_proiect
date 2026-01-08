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
    void adauga(const T& element);
    const std::vector<T>& getToate() const;
    int numaraElementeScumpe(float prag) const;
    void curata();
};

template <typename T>
void Gestiune<T>::adauga(const T& element)
{
    lista.push_back(element);
}
template <typename T>
const std::vector<T>& Gestiune<T>::getToate() const
{
    return lista;
}

template <typename T>
int Gestiune<T>::numaraElementeScumpe(float prag) const
{
    return std::count_if(lista.begin(), lista.end(),[prag](const T& x)
    {
        return (float)x > prag;
    });
}
template <typename T>
void Gestiune<T>::curata()
{
    lista.clear();
}
template<>
void Gestiune<ProdusCosmetic*>::curata();

template<>
int Gestiune<ProdusCosmetic*>::numaraElementeScumpe(float prag) const;
class MagazinManager
{
private:
    MagazinManager();
    static MagazinManager* instanta;
public:
    static MagazinManager* getInstanta();

    void afiseazaMeniu() const;

};

#endif //OOP_GESTIUNE_H