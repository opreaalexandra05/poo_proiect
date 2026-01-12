#ifndef PRODUSE_H
#define PRODUSE_H

#include<string>
#include <iostream>

class ProdusCosmetic //clasa abstracta
{
protected:
    std::string nume;
    float pret;
    static int nrTotalProduse; //membru static comun tuturor obiectelor
public:
    ProdusCosmetic( const std::string& nume, float pret);
    virtual ~ProdusCosmetic();

    ProdusCosmetic(const ProdusCosmetic& altProd);
    ProdusCosmetic& operator=(const ProdusCosmetic& altProd);

    static int getNrTotalProduse();

    const std::string& getNume() const;
    float getPret() const;

    virtual void afisare(std::ostream& os) const;
    virtual void aplica() const = 0;  //polimorfism->fiecare produs se aplica diferit

};

class Skincare: public ProdusCosmetic
{
protected:
    std::string tipTen;

public:
    Skincare(const std::string& nume, float pret, const std::string& ten);
    void afisare(std::ostream& os) const override;
    const std::string& getTipTen() const;
};

class Crema : public Skincare
{
protected:
    float spf;
public:
    Crema(const std::string& nume, float pret, const std::string& ten, float spf);
    void aplica() const override; //implementare specifica (polimorfism)
    void afisare(std::ostream& os) const override;
};

class ProdusFactory  //Factory Pattern -> creeaza obiecte fara sa stim tipul concret, este usor de extins, sanse mai mici sa ne apara errori, ascunde new
{
public:
    static ProdusCosmetic* creeazaCrema(const std::string& nume, float pret, const std::string& ten, float spf);  //returneaza pointer la clasa de baza
};

std::ostream& operator<<(std::ostream& os, const ProdusCosmetic& p);

#endif
