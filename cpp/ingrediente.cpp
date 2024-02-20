#include <string>
#include <iostream>
#include <limits>
#include "ingrediente.hpp"

using namespace std;

Ingrediente::Ingrediente():ingredientName("-----"), quantity("-----"){

    }

Ingrediente::Ingrediente(string ingredientName, string quantity): ingredientName(ingredientName),
                                                                quantity(quantity){

    }
Ingrediente::Ingrediente(string ingredientName): ingredientName(ingredientName), quantity("-----"){}

void Ingrediente::setIngredientName(string ingredientName){
    this->ingredientName = ingredientName;
    }

void Ingrediente::setQuantity(string quantity){
    this->quantity = quantity;
    }

string Ingrediente::getIngredientName()const{
    return this->ingredientName;
    }

string Ingrediente::getQuantity(){
    return this->quantity;
    }

string Ingrediente::toString(){
    return  this->ingredientName+"  "+
            "Cantidad: "+this->quantity;
    }

Ingrediente& Ingrediente::operator=(const Ingrediente& e){
     if (this != &e) {
        this->ingredientName = e.ingredientName;
        this->quantity = e.quantity;
        }
    return *this;
    }

bool Ingrediente::operator==(const Ingrediente& e)const {
    return (ingredientName == e.ingredientName) && (quantity == e.quantity);
    }

bool Ingrediente::operator <(Ingrediente& e){
    return this->ingredientName < e.getIngredientName();
    }

bool Ingrediente::operator >(Ingrediente& e){
    return this->ingredientName > e.getIngredientName();

    }   

bool Ingrediente::operator <=(Ingrediente& e){
    return this->ingredientName <= e.getIngredientName();
    }

bool Ingrediente::operator >=(Ingrediente& e){
    return this->ingredientName >= e.getIngredientName();

    }

ostream& operator <<(ostream& os, Ingrediente& i){
    os << i.ingredientName << endl;
    os << i.quantity;

    return os;
    }

istream& operator >>(istream& is, Ingrediente& i){
    getline(is >> ws, i.ingredientName);
    is >> i.quantity;
    
    return is;
    }


