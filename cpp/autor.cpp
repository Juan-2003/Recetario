#include <string>
#include "autor.hpp"
#include <iostream>

using namespace std;

Autor::Autor():firstName("-----"), lastName("-----"){

    }

Autor::Autor(string firstName, string lastName):firstName(firstName), lastName(lastName){

    }

void Autor::setFirstName(string firstName){
    this->firstName = firstName;
    }

void Autor::setLastName(string lastName){
    this->lastName = lastName;
    }

string Autor::getFirstName(){
    return this->firstName;
    }

string Autor::getLastName(){
    return this->lastName;
    }

string Autor::toString(){
    return "Nombre: "+this->firstName+"\n"+
           "Apellido: "+this->lastName;
    }

Autor& Autor::operator=(const Autor& e) {
    if (this != &e) {
        this->firstName = e.firstName;
        this->lastName = e.lastName;
        }
    return *this;
    }

bool Autor::operator==(const Autor& e) {
    return (firstName == e.firstName) && (lastName == e.lastName);
    }

bool Autor::operator<(const Autor& e) {
    if (lastName != e.lastName) {
        return lastName < e.lastName;
        } 
    else {
        return firstName < e.firstName;
        }
    }

bool Autor::operator>(const Autor& e) {
    if (lastName != e.lastName) {
        return lastName > e.lastName;
        } 
    else {
        return firstName > e.firstName;
        }
    }

bool Autor::operator<=(const Autor& e) {
    return (*this < e) || (*this == e);
    }

bool Autor::operator>=(const Autor& e) {
    return (*this > e) || (*this == e);
    }

ostream& operator <<(ostream& os, Autor& a){
    os << a.firstName << endl;
    os << a.lastName;

    return os;
    }
istream& operator >>(istream& is, Autor& a){
    getline(is, a.firstName);
    getline(is, a.lastName);

    return is;
    }

