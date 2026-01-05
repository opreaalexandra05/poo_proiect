#ifndef GESTIUNE_H
#define GESTIUNE_H
#include<vector>
template <typename T>
class Gestiune
{
private:
    std::vector<T> lista;
public:
    ~Gestiune()
    {
        curata();
    }
    void adauga(T element)
    {
        lista.push_back(element);
    }
    const std::vector<T>& getToate() const
    {
        return lista;
    }
    void curata()
    {
        for (auto e: lista)
        {
            delete e;
        }
        lista.clear();
    }
};

#endif //OOP_GESTIUNE_H