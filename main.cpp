#include <iostream>
#include <fstream>
#include "Produse.h"
#include "Persoana.h"
#include "Gestiune.h"

int main() {
    Gestiune<ProdusCosmetic*> stocProduse;
    std::ifstream f("produse_stoc.txt");
    int n;
    if (f>>n)
    {
        for (int i=0; i<n; ++i)
        {
            std::string nume, ten;
            float pret, spf;
            f>>nume>>pret>>ten>>spf;
            stocProduse.adauga(new Crema(nume, pret, ten, spf));
        }
    }
    f.close();

    Client clienta("Maria", 150.0);
    const ProdusCosmetic* recomandareCurenta = nullptr;
    int optiune;

    std::cout<<"---BINE ATI VENIT LA MAGAZINUL NOSTRU---\n";

    while (true)
    {
        std::cout<<"\nBuget disponibil: "<<clienta.getBuget()<<" RON";
        std::cout<<"\n 1.Cumpara | 2.Consultant Beauty | 3.Vezi cos | 0.Exit \n Alege: ";
        std::cin>>optiune;
        std::cout<<optiune<<"\n";
        if (optiune==0)
        {
           std::cout<<"Va multumim ca ati folosit serviciile noastre!\n";
            break;
        }
        try
       {
           if (optiune==1)
           {
               if (recomandareCurenta != nullptr)
               {
                   clienta.cumparaProdus(recomandareCurenta->getNume(), recomandareCurenta->getPret());
                   recomandareCurenta = nullptr;
               } else
               {
                   std::cout<<"Cereti alt sfat consultantului (optiunea 2) inainte de a cumpara! \n";
               }
           }
           else if (optiune==2)
           {
               std::string tipCautat;
               std::cout<<"Introduceti tipul de ten: ";
               std::cin>>tipCautat;
               std::cout<<tipCautat<<":\n";

               bool gasit = false;
               for (auto p: stocProduse.getToate())
               {
                   Skincare* s = dynamic_cast<Skincare*>(p);
                   if (s&& s->getTipTen()==tipCautat)
                   {
                       Crema* cPtr = dynamic_cast<Crema*>(s);
                       if (cPtr) cPtr->aplica();

                       std::cout<<"Consultantul recomanda: "<<*s<<"\n";
                       recomandareCurenta = p;
                       gasit = true;
                       break;
                   }
               }
               if (!gasit)
               {
                   std::cout<<"Nu am gasit produse pentrul tenul dumneavoastra "<<tipCautat<<"\n";
                   recomandareCurenta = nullptr;
               }
           }
           else if (optiune==3)
           {
               clienta.afiseazaIstoric();
           }
       } catch (const ErroareBuget& e)
       {
           std::cout<<"FONDURI INSUFICIENTE"<<e.what()<<"\n";
       }
    }
    stocProduse.curata();
    std::cout<<"Total produse verificate astazi: "<<ProdusCosmetic::getNrTotalProduse()<<"\n";
    return 0;
}
