#ifndef PRODUSE_H
#define PRODUSE_H

#include<string>
#include <iostream>

class ProdusCosmetic
{
protected:
    std::string nume;
    float pret;
    static int nrTotalProduse;
public:
    ProdusCosmetic( const std::string& nume, float pret);
    virtual ~ProdusCosmetic();

    ProdusCosmetic(const ProdusCosmetic& altProd);
    ProdusCosmetic& operator=(const ProdusCosmetic& altProd);

    static int getNrTotalProduse();

    const std::string& getNume() const
    {
        return nume;
    }
    float getPret() const
    {
        return pret;
    }

    virtual void afisare(std::ostream& os) const;
    virtual void aplica() = 0;


};

class Skincare: public ProdusCosmetic
{
protected:
    std::string tipTen;

public:
    Skincare(const std::string& nume, float pret, const std::string& ten);
    void afisare(std::ostream& os) const override;
    const std::string& getTipTen() const { return  tipTen; }
};

class Crema : public Skincare
{
protected:
    float spf;
public:
    Crema(const std::string& nume, float pret, const std::string& ten, float spf);
    void aplica() override;
    void afisare(std::ostream& os) const override;
};

class ProdusFactory
{
public:
    static ProdusCosmetic* creeazaCrema(std::string nume, float pret, std::string ten, float spf)
    {
       return new Crema(nume, pret, ten, spf);
    }
};

std::ostream& operator<<(std::ostream& os, const ProdusCosmetic& p);

#endif
