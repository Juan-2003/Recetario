#include <iostream>
#include <string>
#include "receta.hpp"
#include "ingrediente.hpp"
#include "list.hpp"

using namespace std;

Receta::Receta(): name("-----"), category("-----"), prepTime("-----"), procedure("-----"){}

Receta::Receta(string name): name(name),category("-----"), prepTime("-----"), procedure("-----"){} 
Receta::Receta(string name, string category, string prepTime, string procedure): 
                name(name),category(category), prepTime(prepTime), procedure(procedure){

    }

void Receta::setName(string name){
    this->name = name;
    }

void Receta::setCategory(string category){
    this->category = category;
    }

void Receta::setPrepTime(string prepTime){
    this->prepTime = prepTime;
    }

void Receta::setProcedure(string procedure){
    this->procedure = procedure;
    }

string Receta::getName()const{
    return this->name;
    }

string Receta::getCategory()const{
    return this->category;
    }
string Receta::getPrepTime()const{
    return this->prepTime;
    }
string Receta::getProcedure()const{
    return this->procedure;
    }

string Receta::toString(){
    return "RECETA "+this->name+"\n"+
    "Categoria: "+this->category+"\n"+
    "Tiempo de Preparacion: "+this->prepTime+" min"+"\n"+
    "Procedimiento: "+this->procedure+"\n"+
    "Autor: "+this->autor.getFirstName() +" "+ this->autor.getLastName()+"\n"+
    "Ingredientes: \n"+this->ingredientsList.toString();
    
    }

Autor& Receta::getAutor(){
    return autor;
    }

bool Receta::compName(const string& name)const{
    return (this->name == name);
    }

List<Ingrediente>& Receta::retrieveList(){
    return ingredientsList;
    }

/*---------- OPERADORES--------------------*/
Receta& Receta::operator =(const Receta& e){
    if (this != &e) {
        this->name = e.name;
        this->category = e.category;
        this->prepTime = e.prepTime;
        this->procedure = e.procedure;
        this->ingredientsList = e.ingredientsList;
        this->autor = e.autor;
        }
    return *this;
    }

bool Receta::operator==(const Receta& e) {
    return (name == e.name) && (category == e.category) && (prepTime == e.prepTime) && (procedure == e.procedure) && (autor == e.autor);
    }

bool Receta::operator <(const Receta& e)const{
    return this->name < e.getName();
    }

bool Receta::operator >(const Receta& e)const{
    return stoi(prepTime) > stoi(e.getPrepTime());
    }

bool Receta::operator <=(const Receta& e)const{
    return this->name <= e.getName();
    }
bool Receta::operator >=(const Receta& e)const{
    return stoi(this->prepTime) >= stoi(e.getPrepTime());
    }

ostream& operator <<(ostream& os, Receta& r){
    os << r.name << endl;
    os << r.category << endl;
    os << r.prepTime << endl;
    os << r.procedure << endl;
    os << r.autor << endl;
    os << r.ingredientsList;

    return os;
    }

istream& operator >>(istream& is, Receta& r){
    getline(is, r.name);
    getline(is, r.category);
    getline(is, r.prepTime);
    getline(is, r.procedure);
    is >> r.autor;

    List<Ingrediente>& tmpList = r.retrieveList();
    is >> tmpList;

    return is;
    } 