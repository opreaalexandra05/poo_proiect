#include <iostream>
#include <fstream>
#include <set>
#include "Produse.h"
#include "Persoana.h"
#include "Gestiune.h"

MagazinManager* MagazinManager::instanta = nullptr;
int main() {
    Gestiune<ProdusCosmetic*> magazin;
    Gestiune<int> logCoduri;


    std::ifstream fStoc("produse_stoc.txt");
    int n;
    if (fStoc>>n)
    {
        for (int i=0; i<n; ++i)
        {
            std::string nume, ten;
            float pret, spf;
            fStoc>>nume>>pret>>ten>>spf;
            magazin.adauga(ProdusFactory:: creeazaCrema(nume, pret, ten, spf));
        }
    }
    fStoc.close();

    std::ifstream fTastatura("tastatura.txt");
    if (!fTastatura)
    {
        std::cout<< "Eroare: Lipseste fisierul de intrare tastatura.txt!\n";
        return 1;
    }

    Client c("", 0);
    fTastatura >> c;
    std::cout<< "\n=================================="<<std::endl;
    c.afiseazaRol();
    std::cout<<"\n Buget client: "<<c.getBuget()<<" RON"<< std::endl;

    int optiune = -1;
    while (optiune != 0)
    {
        MagazinManager::afiseazaMeniu();
        if (!(fTastatura>>optiune)) break;
        std::cout<< optiune << "\n";

        switch (optiune)
        {
        case 1:
            std::cout<<"\n--- LISTA PRODUSE ---\n";
            for (auto p: magazin.getToate())
            {
                std::cout<<*p<<"\n";
            }
            break;
        case 2:
            try
            {
                if (!magazin.getToate().empty())
                {
                    ProdusCosmetic* p = magazin.getToate()[0];
                    std::cout<<"\n[CUMPARARE] "<<c.getNume()<<" a ales: "<<p->getNume()<<"("<<p->getPret()<<" RON) \n";
                    c-= p->getPret();

                    std::cout<<"[INFO] Tranzactie reusita pentru "<<c.getNume()<<".\n";
                    std::cout<<"[INFO] Buget actualizat: "<<c.getBuget()<<" RON\n";

                }
            } catch (const ErroareMagazin& e)
            {
                std::cout<<"FAIL!"<<c.getNume()<<" nu poate cumpara: "<<e.what()<<"\n";
            }
            break;
        case 3:
            {
                std::set<std::string> categoriiTen;
                for (auto p: magazin.getToate())
                {
                    if (Skincare* s = dynamic_cast<Skincare*>(p))
                    {
                        categoriiTen.insert(s->getTipTen());
                    }
                }
                std::cout<<"\n Tipuri de ten identificate: ";
                for (const auto& t: categoriiTen) std::cout<<"["<<t<<"]";
                std::cout<<"\n";

                int nr= magazin.numaraProduseCuProtectie(10.0);
                std::cout<<"\n Produse peste 10 RON: "<<nr<<"\n";
            }
            break;
        case 0:
            std::cout<<"EXIT";
            break;
        }
    }
    fTastatura.close();

    for (auto p: magazin.getToate()) delete p;
    magazin.curata();

    return 0;
}
