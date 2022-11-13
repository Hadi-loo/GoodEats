#include "offer.hpp"

Offer::Offer(string _ingredient_, double _price_, double _packaging_, int _count_, shared_ptr<Supplier> _origin_supplier_)
{
    ingredient = _ingredient_;
    price = _price_;
    packaging = _packaging_;
    count = _count_;
    origin_supplier = _origin_supplier_;
}

Offer::~Offer()
{

}

string Offer::get_ingredient()
{
    return ingredient;
}

void Offer::edit_price(double _price_, int _count_)
{
    price = _price_;
    count = _count_;
}

double Offer::get_price()
{
    return (price + packaging);
}

bool Offer::has_balance()
{
    if (count <= 0)
    {
        return false; 
    }
    return true;
}

shared_ptr<Supplier> Offer::get_supplier()
{
    return origin_supplier;
}

void Offer::decrease_balance()
{
    count--;
}

int Offer::get_count()
{
    return count;
}