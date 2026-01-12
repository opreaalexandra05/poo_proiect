#include "Gestiune.h"
#include <iostream>
#include <algorithm>

MagazinManager* MagazinManager::instanta = nullptr;

template<>
void Gestiune<ProdusCosmetic*>::curata()         //sterge fiecare produs din memorie=> evit memory leak; auto isi da seama singur de ce tip de obiect e=> cod mai curat si eficient
{
    for (auto p: lista)
    {
        delete p;  // eliberam memoria alocata dinamic (heap)
    }
    lista.clear();
}

template<>
int Gestiune<ProdusCosmetic*>::numaraElementeScumpe(float prag) const
{
    return std::count_if(lista.begin(), lista.end(),[prag](ProdusCosmetic* p)
    {
        return p != nullptr && p->getPret() > prag;
    });
}

MagazinManager::MagazinManager(){}

MagazinManager* MagazinManager::getInstanta()
{
    if (!instanta) instanta = new MagazinManager();
    return instanta;
}

void MagazinManager::afiseazaMeniu() const
{
    std::cout<<"\n --- MENIU GESTIUNE COSMETICE ---";
    std::cout<<"\n1. Afisare Stoc";
    std::cout<<"\n2. Cumpara Produs";
    std::cout<<"\n3. Statistici";
    std::cout<<"\n0. Iesire";
    std::cout<<"\nSelectie: ";
}