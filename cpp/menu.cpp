#include "Menu.hpp"
#include "list.hpp"
#include "listaDoble.hpp"
#include "nodeDoble.hpp"


using namespace std;

void Menu::showMenu(){
    int option;
    do{
        //showList();
        cout<<"\nINGRESA LA OPCION A EJECUTAR\n";
        cout<<"1.Mostrar lista de recetas\n2.Nueva Receta\n"<<
                "3.Buscar Receta\n4.Eliminar Receta\n"<<
                "5.Eliminar lista de recetas\n6.Eliminar Ingrediente\n"<<
                "7.Eliminar lista de Ingredientes\n8.Editar cantidad de Ingrediente\n"<<
                "9.Editar procedimiento\n10.Ordenar lista\n"<<
                "11.Añadir Ingrediente\n12.Escribir en el disco\n"<<
                "13.Leer del disco\n14.Salir\nOpcion:";
        cin>>option;

        switch(option){
            case 1: showList();
                    break;
            case 2: askData();
                    break;
            case 3: searchRecipe();
                    break;
            case 4: deleteRecipe();
                    break; 
            case 5:deleteRecipeList();
                    break;
            case 6:deleteIngredient();
                    break;
            case 7: deleteIngredientList();
                    break;
            case 8: modifyIngredientQuantity();
                    break;
            case 9: modifyProcedure();
                    break;
            case 10: sort();
                    break; 
            case 11: addIngredient();
                    break;
            case 12: writeToDisk(); 
                    break;
            case 13: readFromDisk();
                    break;
            case 14:break;
            default: 
                cout<<"OPCION NO VALIDA\n";
                break;
            }
        }while(option != 14);
    cout<<"SALISTE";
    }

void Menu::showList(){
    cout<<"\nLISTA DE RECETAS\n";
    cout<<endl<<recipeList.toString();
    }

void Menu::askData(){
    string name, category, prepTime, procedure, autorName, autorLastName; 
    string ingredientName;
    string quantity;
    int numIngredients;
    cout<<"\nNUEVA RECETA\n";
    cout<<"Ingresa los siguientes datos\n\n";
    
    cout<<"Nombre de Receta: ";
    cin.ignore();
    getline(cin,name);

    do{
        cout<<"Categoria(desayuno, comida, cena, navideño): ";
        cin>>category;
        cin.ignore();
        }while(category != "desayuno" && category != "comida" && category != "cena" && category != "navideno");

    cout<<"Tiempo de Preparacion(minutos): ";
    cin>>prepTime;
    cout<<"Procedimiento: ";
    cin.ignore();
    getline(cin,procedure);
    cout<<"Primer nombre del autor: ";
    cin>>autorName;
    cout<<"Apellido del autor: ";
    cin>>autorLastName;

    Receta receta = Receta(name, category, prepTime, procedure);
    receta.getAutor().setFirstName(autorName);
    receta.getAutor().setLastName(autorLastName);
    
    cout<<"\nINGREDIENTES\n";
    cout<<"¿Cuantos ingredientes necesita?\n";
    cout<<"Cantidad: ";
    cin>>numIngredients;
    cin.ignore();
    
    List<Ingrediente>& listI = receta.retrieveList();
    int i = 1;
    do{
        cout<<"INGREDIENTE "<<i<<endl;
        cout<<"Nombre: "; 
        getline(cin, ingredientName);
        cout<<"Cantidad: ";
        getline(cin, quantity);
        Ingrediente ingredient = Ingrediente(ingredientName, quantity);
        listI.insertData(listI.getLastPos(), ingredient);
        //receta.retrieveList().insertData(listI.getLastPos(), ingredient);
        listI.mergeSort();
        i++;
        }while(i <= numIngredients);
    
    int pos;
    cout<<"Posicion a Insertar: ";
    cin>>pos;

    NodeDoble<Receta>* pos2 = recipeList.getFirstPos();

    if(pos >= 0){
        for (int i = 0; i < pos-1; i++) {
            if (pos2 != nullptr) {
                pos2 = pos2->getNext();
                }
            }
        }
    else if(pos == -1){
        pos2 = nullptr;
        }
    recipeList.insertData(pos2, receta);
    cout<<"\nNUEVA RECETA AÑADIDA\n";
    }

void Menu::searchRecipe(){
    int searchType = 0;
    string name;
    Receta receta;
    cout<<"\nBUSCAR RECETA\n";

    do{
        cout<<"\n¿Como quieras buscar la receta?\n1.Nombre de la receta\n2.Categoria\nOpcion:";
        cin>>searchType;
        cin.ignore();
        switch(searchType){
            case 1: cout<<"\nIngrese el nombre de la receta: ";
                    getline(cin, name);
                    receta.setName(name);
                    break;
            case 2:cout<<"\nIngrese la categoria: ";
                    cin>>name;
                    receta.setCategory(name);
                    break;
            default:
                cout<<"OPCION NO VALIDA";
            }
        }while(searchType != 1 && searchType != 2);

    NodeDoble<Receta>* pos = recipeList.findData(receta,searchType);
    cout<<"Posicion: "<<pos<<endl;
    cout<<endl<<recipeList.retrieve(pos).toString();
    }

void Menu::deleteRecipe(){
    string name;
    int option;
    cout<<"\nELIMINAR RECETA\n";
    cout<<"Ingresa el nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();
    
    while(tmp != nullptr){ //Corrimiento para encontrar el valor deseado
        if(tmp->getData().getName() == name){ 
            cout<<endl<<recipeList.retrieve(tmp).toString()<<endl;
            cout<<"Seguro que quieres eliminar la receta?\n1.Si\n2.No\nOpcion:";
            cin>>option;
            if(option == 1){
                recipeList.deleteData(tmp);
                cout<<"\nSE HA ELIMINADO CORRECTAMENTE\n";
                }
            break;
            }
        tmp = tmp->getNext();
        }
    }

void Menu::deleteRecipeList(){
    int option;
    cout<<"\nELIMINAR LISTA DE RECETAS\n";

    do{
        cout<<"\nSeguro que quieres eliminar la lista de Recetas?\n1.Si\n2.No\nOpcion:";
        cin>>option;
        option = (option == 1)? 1 : 2;
        }while(option != 1 && option != 2); 

    if(option == 1){
        cout<<"\nSE HA ELIMINADO LA LISTA DE RECETAS\n";
        recipeList.~ListDoble();
        }
    }

void Menu::sort(){
    int option;
    cout<<"\nORDENAR LISTA DE RECETAS\n";
    do{
        cout<<"Por cual metodo desea ordenar?\n1.Nombre de receta\n"<<
            "2.Tiempo de preparacion\nOpcion:";
        cin>>option;
        }while(option != 1 && option != 2);

    recipeList.quickSort(option);
    cout<<"\nLISTA ORDENADA\n";
    }

void Menu::deleteIngredient(){
    string name, ingredient;
    cout<<"\nELIMINAR UN INGREDIENTE\n";
    cout<<"Nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    while(tmp <= recipeList.getLastPos()){
        if(tmp->getData().getName() == name){
            break;
            }
        tmp = recipeList.getNextPos(tmp);
        }
    
    Receta& receta = recipeList.retrieve(tmp);
    cout<<endl<<receta.toString();
    cout<<"\nNombre del ingrediente: ";
    getline(cin,ingredient);

    List<Ingrediente>&listTemp = receta.retrieveList();
    Node<Ingrediente>* pos = listTemp.getFirstPos();

    while(pos != nullptr){ //Corrimiento para encontrar el valor deseado
        if(pos->getData().getIngredientName() == ingredient){ 
            cout<<"\nINGREDIENTE ELIMINADO\n";
            listTemp.deleteData(pos);
            break;
            }
        pos = pos->getNext();
        }
    }

void Menu::modifyIngredientQuantity(){
    string name, ingredientName, quantity;
    cout<<"\nMODIFICAR CANTIDAD DE INGREDIENTE\n";
    cout<<"Nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    while(tmp <= recipeList.getLastPos()){
        if(tmp->getData().getName() == name){
            break;
            }
        tmp = recipeList.getNextPos(tmp);
        }
    
    Receta& receta = recipeList.retrieve(tmp);
    cout<<endl<<receta.toString();
    cout<<endl<<"Nombre del ingrediente: ";
    getline(cin,ingredientName);
    cout<<"Cantidad: ";
    getline(cin, quantity);

    List<Ingrediente>&listTemp = receta.retrieveList();
    Node<Ingrediente>* pos = listTemp.getFirstPos();

    while(pos != nullptr){
        if(pos->getData().getIngredientName() == ingredientName){ 
            break;
            }
        pos = pos->getNext();
        }
    Ingrediente& ingredient = listTemp.retrieve(pos);
    ingredient.setQuantity(quantity);
    cout<<"\nCANTIDAD ACTUALIZADA\n";
    }

void Menu::deleteIngredientList(){
    string name;
    cout<<"\nELIMINAR LISTA DE INGREDIENTES\n";
    cout<<"Nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    while(tmp != nullptr){
        if(tmp->getData().getName() == name){
            break;
            }
        tmp = recipeList.getNextPos(tmp);
        }
    
    Receta& receta = recipeList.retrieve(tmp);
    receta.retrieveList().~List();
    cout<<endl<<receta.toString();
    cout<<"\nLISTA DE INGREDIENTES ELIMINADA\n";
    }

void Menu::modifyProcedure(){
    string name, procedure;
    cout<<"\nMODIFICAR PROCEDIMIENTO\n";
    cout<<"Nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    while(tmp <= recipeList.getLastPos()){
        if(tmp->getData().getName() == name){
            break;
            }
        tmp = recipeList.getNextPos(tmp);
        }
    
    Receta& receta = recipeList.retrieve(tmp);
    cout<<endl<<receta.toString();
    cout<<"\nIngrese el procedimiento\nProcedimiento:";
    getline(cin, procedure);
    receta.setProcedure(procedure);
    cout<<"\nPROCEDIMIENTO ACTUALIZADO\n";

    }

void Menu::addIngredient(){
     string name, ingredient, quantity;
    cout<<"\nAÑADIR UN INGREDIENTE\n";
    cout<<"Nombre de la receta: ";
    cin.ignore();
    getline(cin, name);

    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    while(tmp <= recipeList.getLastPos()){
        if(tmp->getData().getName() == name){
            break;
            }
        tmp = recipeList.getNextPos(tmp);
        }
    
    Receta& receta = recipeList.retrieve(tmp);
    cout<<endl<<receta.toString();
    cout<<endl<<"Nombre del ingrediente: ";
    getline(cin,ingredient);
    cout<<"Cantidad: ";
    getline(cin,quantity);

    List<Ingrediente>&listTemp = receta.retrieveList();
    Ingrediente newIngredient = Ingrediente(ingredient, quantity);
    listTemp.insertData(listTemp.getLastPos(), newIngredient);
    cout<<"\nINGREDIENTE AÑADIDO\n";
    }

NodeDoble<Receta>* Menu::getRecipePosition(int pos){
    NodeDoble<Receta>* tmp = recipeList.getFirstPos();

    for(int i = 0; i < pos; i++){
        if(tmp == nullptr){
            return nullptr;
            }
        tmp = tmp->getNext();
        }
    return tmp;
    }

void Menu::writeToDisk(){
    recipeList.writeToDisk("listaRecetas.txt");
    cout<<"\nSE HA ESCRITO EN EL ARCHIVO listaRecetas.txt\n";
    }

void Menu::readFromDisk(){
    cout<<"\nLEER DEL DISCO\n";
    int option;
    cout<<"\nEstas seguro de querer leer del disco?";
    cout<<"La lista de recetas actual se eliminara.\n1.Si\n2.No\nOpcion:";
    cin>>option;

    if(option == 2){
        showMenu();
    }
    
    string fileName;
    cin.ignore();
    cout<<"Ingrese el nombre del archivo a leer: ";
    getline(cin, fileName);
    recipeList.~ListDoble();
    ifstream file(fileName);

    if(file.is_open()){
        string line;
        Receta recipe;
        Ingrediente ingredient;

        while(getline(file, line)){
            if(line.empty()){
                recipeList.insertData(recipeList.getLastPos(), recipe);
                recipe = Receta();
                ingredient = Ingrediente(); 
                continue;
                }
            if(line.find("Nombre de la receta:") != string::npos){
                line = line.substr(21);
                recipe.setName(line);
                }
            else if(line.find("Categoria:") != string::npos){
                line = line.substr(11);
                recipe.setCategory(line);
                }
             else if(line.find("Tiempo:") != string::npos){
                line = line.substr(8);
                recipe.setPrepTime(line);
                }
            else if(line.find("Procedimiento:") != string::npos){
                line = line.substr(15);
                recipe.setProcedure(line);
                }
            else if(line.find("Primer nombre del autor:") != string::npos){
                line = line.substr(25);
                recipe.getAutor().setFirstName(line);
                }
            else if(line.find("Apellido del autor:") != string::npos){
                line = line.substr(20);
                recipe.getAutor().setLastName(line);
                }
            else if(line.find("Nombre de ingrediente:") != string::npos){
                string nameIn = line.substr(23);
                string quantity;
                if(getline(file,line) && line.find("Cantidad:") != string::npos){
                    quantity = line.substr(10);
                    }
                ingredient.setIngredientName(nameIn);
                ingredient.setQuantity(quantity);
                recipe.retrieveList().insertData(recipe.retrieveList().getLastPos(), ingredient);
                }
            }
        recipeList.insertData(recipeList.getLastPos(), recipe);        
        }
    else{
        cout<<"\nNO EXISTE ESE ARCHIVO\n";
        }
    cout<<recipeList.toString();
    }
