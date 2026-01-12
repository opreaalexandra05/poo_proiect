#include <iostream>
#include <fstream>
#include <set>
#include "Produse.h"
#include "Persoana.h"
#include "Gestiune.h"

int main() {
    Gestiune<ProdusCosmetic*> magazin;
    Gestiune<int> logCoduri;   //aceeasi cls template -> tipuri diferite

    const MagazinManager* manager = MagazinManager::getInstanta();  //folosim singleton
    std::cout<<"[SISTEM] Obiecte inregistrate initial: "<< ProdusCosmetic::getNrTotalProduse() << "\n";

    std::ifstream fStoc("produse_stoc.txt");
    int nrProd;
    if (fStoc>>nrProd)
    {
        for (int i=0; i<nrProd; ++i)
        {
            std::string nume, ten;
            float pret, spf;
            fStoc>>nume>>pret>>ten>>spf;
            magazin.adauga(ProdusFactory:: creeazaCrema(nume, pret, ten, spf)); //factory+alocare dinamica+polimorfism
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
        manager->afiseazaMeniu();
        if (!(fTastatura>>optiune)) break;
        logCoduri.adauga(optiune);
        std::cout<< optiune << "\n";

        switch (optiune)
        {
        case 1:
            std::cout<<"\n--- LISTA PRODUSE ---\n";
            for (const auto* p: magazin.getToate())
            {
                std::cout<<*p<<"\n";
            }
            break;
        case 2:
            try
            {
                if (magazin.getToate().empty())
                {
                    throw ErroareSToc();
                }
                int indexProdus;
                std::cout<<"Introduceti indexul produsului(0-"<<magazin.getToate().size() - 1 <<"): ";
                if (!(fTastatura>>indexProdus))break;
                std::cout<<indexProdus<<"\n";
                if (indexProdus< 0 || (size_t)indexProdus >= magazin.getToate().size())
                {
                    throw ErroareSToc();
                }
                const ProdusCosmetic* p = magazin.getToate()[indexProdus];
                std::cout<<"\n[CUMPARARE] "<<c.getNume()<<" a ales: "<< p->getNume() <<"\n";
                c-= p->getPret();
                c.incrementareAchizitii();
                std::cout<<"\n[INFO] Achizitie finalizata pentru "<<p->getNume()<<"\n";
                p->aplica();

                Persoana* pPers = &c;
                pPers->aplicaDiscountFidelitate(5.0);

                std::cout<<"[INFO] Buget actualizat: "<<c.getBuget()<<" RON\n";

            } catch (const ErroareMagazin& e)
            {
                std::cout<<"FAIL!"<<c.getNume()<<" nu poate cumpara: "<<e.what()<<"\n"; //prindem exceptia si afisam mesajul, aici se intampla UPCASTING
            }
            break;
        case 3:
            {
                std::set<std::string> categoriiTen;
                for (const auto* p: magazin.getToate())
                {
                    if (const Skincare* s = dynamic_cast<const Skincare*>(p))
                    {
                        categoriiTen.insert(s->getTipTen());
                    }
                }
                std::cout<<"\n Tipuri de ten identificate: ";
                for (const auto& t: categoriiTen) std::cout<<"["<<t<<"]";
                std::cout<<"\n";

                int nrScumpe= magazin.numaraElementeScumpe(10.0);
                std::cout<<"\n Produse cu pret peste 10 RON: "<<nrScumpe<<"\n";
            }
            break;
        case 0:
            std::cout<<"EXIT";
            break;
        }
    }
    std::cout<<"\n[SISTEM] Istoric comenzi procesate: ";
    for (int cod: logCoduri.getToate()) std::cout<<cod<<" ";
    fTastatura.close();

    magazin.curata();  //stergerea corecta a memoriei alocate dinamic
    logCoduri.curata();

    return 0;
}

//proiectul simuleaza un sistem real de gestiune a produselor cosmetice prin concepte POO: incapsulare, mostenire, polimorfism, template, STL, exceptii si design patterns -> factory pattern.
