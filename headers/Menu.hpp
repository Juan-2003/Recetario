#include "ingrediente.hpp"
#include "receta.hpp"
#include "list.hpp"
#include "listaDoble.hpp"
#include "nodeDoble.hpp"

#ifndef MENU_HPP
#define MENU_HPP

class Menu{
    private:
        ListDoble<Receta>recipeList;
    
    public:
        void showMenu();
        void showList();
        void askData();
        void searchRecipe();
        void deleteRecipe();
        void deleteRecipeList();
        void deleteIngredient();
        void deleteIngredientList();
        void modifyIngredientQuantity();
        void modifyProcedure();
        void sort();
        void addIngredient();
        void writeToDisk();
        void readFromDisk();

        NodeDoble<Receta>* getRecipePosition(int);
    };  

#endif