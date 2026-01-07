#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>

class ErroareMagazin: public std::exception
{
public:
    virtual const char* what() const throw() override
    {
        return "Eroare generala magazin!";
    }
};

class ErroareBuget: public ErroareMagazin
{
public:
    const char* what() const throw() override
    {
        return "Fonduri insuficiente in contul clientului!";
    }
};

class Persoana
{
protected:
    std::string nume;
public:
    Persoana(const std::string& n): nume(n) {}
    virtual ~Persoana(){}
    const std::string& getNume() const
    {
        return nume;
    }
    virtual void afiseazaRol() const = 0;
};

class Client: public Persoana
{
private:
    float buget;
public:
    Client(const std::string& n, float b): Persoana(n), buget(b){}
    void afiseazaRol() const override {std::cout <<"Rol: Client | Nume: "<<nume<<"\n";}
    float getBuget() const
    {
        return buget;
    }

    Client& operator -=(float suma)
    {
        if (suma>buget) throw ErroareBuget();
        buget-=suma;
        return *this;
    }

    friend std::istream& operator >>(std::istream& is, Client& c)
    {
        is>>c.nume;
        is>>c.buget;
        return is;
    }
};

float operator+(const Client& c, float bonus);

#endif //OOP_PERSOANA_H