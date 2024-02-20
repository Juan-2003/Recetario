#include <string>
#include <iostream>
#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

class Ingrediente{
    private:
        std::string ingredientName;
        std::string quantity;

    public:
        Ingrediente();
        Ingrediente(std::string ingredientName, std::string quantity);
        Ingrediente(std::string ingredientName);

        void setIngredientName(std::string ingredientName);
        void setQuantity(std::string quantity);

        std::string getIngredientName()const;
        std::string getQuantity();

        std::string toString();
        Ingrediente& operator=(const Ingrediente& e);
        bool operator==(const Ingrediente& e)const;
        bool operator <(Ingrediente& e);
        bool operator >(Ingrediente& e);
        bool operator <=(Ingrediente& e);
        bool operator >=(Ingrediente& e);

        friend std::ostream& operator <<(std::ostream&, Ingrediente&);
        friend std::istream& operator >>(std::istream&, Ingrediente&);
    };
#endif
