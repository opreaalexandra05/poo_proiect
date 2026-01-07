#ifndef GESTIUNE_H
#define GESTIUNE_H

#include<vector>
#include<iostream>
#include "Produse.h"


template <typename T>
class Gestiune
{
private:
    std::vector<T> lista;
public:
    void adauga(const T& element)
    {
        lista.push_back(element);
    }
    const std::vector<T>& getToate() const
    {
        return lista;
    }
    int numaraProduseCuProtectie(float pragSPF) const;
    void curata();
};

template <>
int Gestiune<int>::numaraProduseCuProtectie(float pragSPF) const
{
    int nr = 0;
    for (size_t i = 0; i<lista.size(); ++i)
    {
        if ((float)lista[i] > pragSPF)
        {
            nr++;
        }
    }
    return  nr;
}

template <>
void Gestiune<int>::curata()
{
    lista.clear();
}

template <>
int Gestiune<ProdusCosmetic*>::numaraProduseCuProtectie(float pragSPF) const
{
    int nr = 0;
    for (size_t i = 0; i<lista.size(); ++i)
    {
        if (lista[i] != nullptr && lista[i]->getPret()>pragSPF)
        {
            nr++;
        }
    }
    return nr;
}

template <>
void Gestiune<ProdusCosmetic*>::curata()
{
    for (size_t i = 0; i<lista.size(); ++i)
    {
        if (lista[i] != nullptr)
        {
            delete lista[i];
            lista[i] = nullptr;
        }
    }
    lista.clear();
}
class MagazinManager
{
private:
    MagazinManager(){}
    static MagazinManager* instanta;
public:
    static MagazinManager* getInstanta()
    {
        if (!instanta) instanta = new MagazinManager();
        return instanta;
    }
    static void afiseazaMeniu()
    {
        std::cout<<"\n --- MENIU GESTIUNE COSMETICE ---";
        std::cout<<"\n1. Afisare Stoc";
        std::cout<<"\n2. Cumpara Produs";
        std::cout<<"\n3. Statistici";
        std::cout<<"\n0. Iesire";
        std::cout<<"\nSelectie: ";
    }
};

#endif //OOP_GESTIUNE_H