#ifndef GESTIUNE_H
#define GESTIUNE_H

#include<vector>
#include<algorithm>
#include<iostream>


template <typename T>
class Gestiune
{
private:
    std::vector<T> lista;
public:
    void adauga(T element)
    {
        lista.push_back(element);
    }
    const std::vector<T>& getToate() const
    {
        return lista;
    }
    int numaraProduseCuProtectie(float pragSPF) const
    {
        return std::count_if(lista.begin(), lista.end(), [pragSPF](const T& p)
        {
            return p->getPret() > 0;
        });
    }
    void curata()
    {
        lista.clear();
    }

};

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