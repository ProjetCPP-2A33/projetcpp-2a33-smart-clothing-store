#include "produit.h"

class produitData : public QSharedData
{
public:

};

produit::produit() : data(new produitData)
{

}

produit::produit(const produit &rhs) : data(rhs.data)
{

}

produit &produit::operator=(const produit &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

produit::~produit()
{

}
