#ifndef RECETA_HPP
#define RECETA_HPP
#include <string>
#include <iostream>
#include "ingrediente.hpp"
#include "list.hpp"
#include "autor.hpp"
#define TAMMAX 20

class Receta{
    private:
        List<Ingrediente>ingredientsList;
        Autor autor;
        std::string name;
        std::string category;
        std::string prepTime;
        std::string procedure;

    public:
        Receta();
        Receta(std::string name);
        Receta(std::string name, std::string category, std::string prepTime, std::string procedure);
        void setName(std::string name);
        void setCategory(std::string category);
        void setPrepTime(std::string prepTime);
        void setProcedure(std::string procedure);

        std::string getName()const;
        std::string getCategory()const;
        std::string getPrepTime()const;
        std::string getProcedure()const;
        std::string toString();

        Autor& getAutor();
        bool compName(const string&)const;
        List<Ingrediente>& retrieveList();

        //---------------------------------------------------------//
        Receta& operator =(const Receta& e);
        bool operator==(const Receta& e);
        bool operator <(const Receta& e)const;
        bool operator >(const Receta& e)const;
        bool operator <=(const Receta& e)const;
        bool operator >=(const Receta& e)const;
        friend std::ostream& operator <<(std::ostream&, Receta&);
        friend std::istream& operator >>(std::istream&, Receta&);


    };
#endif