#ifndef _OFFER_HPP_
#define _OFFER_HPP_

#include "test.hpp"
class Offer
{
public:
    Offer(string _ingredient_, double _price_, double _packaging_, int _count_, shared_ptr<Supplier> _origin_supplier_);
    ~Offer();
    string get_ingredient();
    void edit_price(double _price_, int _count_);
    double get_price();
    bool has_balance();
    shared_ptr<Supplier> get_supplier();
    void decrease_balance();
    int get_count();
private:
    string ingredient;
    double price;
    double packaging;
    int count;
    shared_ptr<Supplier> origin_supplier;
};

#endif