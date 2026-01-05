#include "Produse.h"

// cppcheck-suppress unusedFunction
int ProdusCosmetic::nrProduse = 0;

ProdusCosmetic::ProdusCosmetic(const std::string& nume, float pret): nume(nume), pret(pret)
{
    nrProduse++;
}

ProdusCosmetic::~ProdusCosmetic()
{
    nrProduse--;
}

ProdusCosmetic::ProdusCosmetic(const ProdusCosmetic& altProd): nume(altProd.nume), pret(altProd.pret)
{
    nrProduse++;
}

ProdusCosmetic& ProdusCosmetic::operator=(const ProdusCosmetic& altProd)
{
    if (this != &altProd){ nume= altProd.nume; pret= altProd.pret; }
    return *this;
}

void ProdusCosmetic::afisare(std::ostream& os) const
{
    os<<"Produs: "<<nume<<"| Pret:"<<pret<<" RON"<<std::endl;
}

Skincare::Skincare(const std::string& nume, float pret, const std::string& ten): ProdusCosmetic(nume, pret), tipTen(ten){}

void Skincare::afisare(std::ostream& os) const
{
    ProdusCosmetic::afisare(os);
    os<<" | Tip Ten:"<<tipTen<<std::endl;
}

Crema:: Crema(const std::string& nume, float pret, const std::string& ten, float spf): Skincare(nume, pret, ten), spf(spf){}

void Crema::aplica()
{
    std::cout<< "Se aplica crema cu SPF "<<spf<<"prin masaj circular. \n";
}

void Crema::afisare(std::ostream& os) const
{
    Skincare::afisare(os);
    os<< " | SPF: "<< spf<<std::endl;
}

std::ostream& operator<<(std::ostream& os, const ProdusCosmetic& p)
{
    p.afisare(os);
    return os;
}

