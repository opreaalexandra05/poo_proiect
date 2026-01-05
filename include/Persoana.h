#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>

class ErroareBuget: public std::exception
{
public:
    const char* what() const throw() override
    {
        return "Fonduri insuficiente!";
    }
};

class Client
{
private:
    std::string nume;
    float buget;
    std::vector<std::string> istoricCumparaturi;
public:
    Client(std::string numeClient, float bugetInitial): nume(numeClient), buget(bugetInitial){}

    void cumparaProdus(std::string numeProdus, float pretProdus)
    {
        if (pretProdus > buget)
        {
            throw ErroareBuget();
        }
        buget -= pretProdus;
        istoricCumparaturi.push_back(numeProdus);
        std::cout<<"Felicitari! Ai cumparat: "<<numeProdus<<".Buget ramas: "<<buget<<" RON  \n";
    }

    float getBuget() const
    {
        return buget;
    }

    std::string getNume() const
    {
        return nume;
    }

    void afiseazaIstoric() const
    {
        std::cout<<"Istoric cumparaturi pentru "<<nume<<": ";
        for (const auto& prod : istoricCumparaturi)
        {
            std::cout<<prod<<" | ";
        }
        std::cout<<"\n";
    }
};

#endif //OOP_PERSOANA_H