#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>
#include <exception>

class ErroareMagazin: public std::exception
{
public:
    virtual const char* what() const throw() override;
};

class ErroareBuget: public ErroareMagazin
{
public:
    const char* what() const throw() override;
};

class Persoana
{
protected:
    std::string nume;
public:
    Persoana(const std::string& n);
    virtual ~Persoana();
    virtual void afiseazaRol() const = 0;
    const std::string& getNume() const;
};

class Client: public Persoana
{
private:
    float buget;
public:
    Client(const std::string& n, float b);
    void afiseazaRol() const override;
    float getBuget() const;

    Client& operator -=(float suma);

    friend std::istream& operator >>(std::istream& is, Client& c);

};

float operator+(const Client& c, float bonus);

#endif //OOP_PERSOANA_H