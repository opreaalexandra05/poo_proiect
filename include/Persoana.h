#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>
#include <exception>

class ErroareMagazin: public std::exception //clasa de exceptie personalizata
{
public:
    virtual const char* what() const throw() override;
};

class ErroareBuget: public ErroareMagazin
{
public:
    const char* what() const throw() override;  //what() returneaza mesajul erorii
}; //exceptie specializata

class ErroareSToc: public ErroareMagazin
{
public:
    const char* what() const throw() override;
};

class Persoana  //clasa abstracta are metoda pur virtuala
{
protected:
    std::string nume;
public:
    Persoana(const std::string& n);
    virtual ~Persoana();
    virtual void afiseazaRol() const = 0;//functie pur virtuala -> clasa abstracta, forteaza clasele derivate sa o implementeze
    const std::string& getNume() const;
    virtual void aplicaDiscountFidelitate(float procent) = 0;  //noua functie virtuala pura pt a dovedi polimorfismul
};

class Client: public Persoana
{
private:
    float buget;
    int nrAchizitii;
public:
    Client(const std::string& n, float b);
    void afiseazaRol() const override; //polimorfism
    float getBuget() const;
    bool esteFidel() const;
    void incrementareAchizitii();
    void aplicaDiscountFidelitate(float procent) override;  //suprascriere in derivata
    Client& operator -=(float suma); //supraincarcare operator -> scade bani din buget
    friend std::istream& operator >>(std::istream& is, Client& c);

};

float operator+(const Client& c, float bonus);

#endif //OOP_PERSOANA_H