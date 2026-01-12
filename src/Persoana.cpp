#include "Persoana.h"

 const char* ErroareMagazin::what() const throw()
{
    return "Erroare generala magazin!";
}
const char* ErroareBuget::what() const throw()
{
    return "Fonduri insuficiente!";
}
const char* ErroareSToc::what() const throw()
 {
     return "Produsul selectat nu exista in stoc(index invalid)!";
 }
Persoana::Persoana(const std::string& n): nume(n){}
Persoana::~Persoana()
 {

 }
const std::string& Persoana::getNume() const
 {
     return nume;
 }

Client::Client(const std::string& n, float b): Persoana(n), buget(b), nrAchizitii(0) {}

void Client::afiseazaRol() const
{
    std::cout<<"Rol: Client | Nume: "<<nume;
}
float Client::getBuget() const
 {
     return buget;
 }

void Client::incrementareAchizitii()
{
    nrAchizitii++;
}

bool Client::esteFidel() const
{
   return nrAchizitii>=3;
}

void Client::aplicaDiscountFidelitate(float procent)
{
    if (this->esteFidel())
    {
        if (procent>0 && procent<100)
        {
            float valbonus = (getBuget() * procent)/ 100;
            this->buget = (*this) + valbonus;

            std::cout<< "\n [FIDELITATE] Clientul "<< getNume()<<" a primit un bonus de "<<valbonus<<" RON(Achizitii totale: "<<nrAchizitii<<" ).\n";
        }
    } else
    {
        std::cout<<"[INFO] "<<getNume()<< " nu este inca client fidel. Achizitii necesare: "<<(3-nrAchizitii)<<".\n";
    }
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