#include "Persoana.h"

 const char* ErroareMagazin::what() const throw()
{
    return "Erroare generala magazin!";
}
const char* ErroareBuget::what() const throw()
{
    return "Fonduri insuficiente!";
}

Persoana::Persoana(const std::string& n): nume(n){}
Persoana::~Persoana()
 {

 }
const std::string& Persoana::getNume() const
 {
     return nume;
 }

Client::Client(const std::string& n, float b): Persoana(n), buget(b){}

void Client::afiseazaRol() const
{
    std::cout<<"Rol: Client | Nume: "<<nume;
}
float Client::getBuget() const
 {
     return buget;
 }
Client& Client::operator-=(float suma)
 {
     if (suma>buget) throw ErroareBuget();
     buget-=suma;
     return *this;
 }

std::istream& operator >>(std::istream& is, Client& c)
 {
     is>>c.nume>>c.buget;
     return is;
 }
float operator+(const Client& c, float bonus)
{
    return c.getBuget() + bonus;
}