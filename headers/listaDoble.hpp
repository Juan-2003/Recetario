#ifndef LISTADOBLE_HPP
#define LISTADOBLE_HPP
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include "nodeDoble.hpp"

template <class T>
class ListDoble{
    private:
        NodeDoble<T>* anchor;

        void copyAll(const ListDoble&);
        bool isValid(NodeDoble<T>*)const;
        void swap(NodeDoble<T>*, NodeDoble<T>*);
        NodeDoble<T>* partition(NodeDoble<T>*, NodeDoble<T>*, int);
        void quickSort(NodeDoble<T>*, NodeDoble<T>*, int);


    public:
        class Exception: public std::exception{
                    private:
                        std::string msg;
                    public:
                        explicit Exception(const char* message):msg(message){}
                        explicit Exception(const std::string& message):msg(message){}
                        virtual ~Exception()throw(){}
                        virtual const char* what() const throw(){
                            return msg.c_str();
                            }
                    };
        ListDoble();
        ListDoble(const ListDoble&);
        ~ListDoble();

        bool isEmpty()const;
        void insertData(NodeDoble<T>*, const T&);
        void deleteData(NodeDoble<T>*);
        NodeDoble<T>* getFirstPos();
        NodeDoble<T>* getLastPos();
        NodeDoble<T>* getPrevPos(NodeDoble<T>*);
        NodeDoble<T>* getNextPos(NodeDoble<T>*);
        NodeDoble<T>* findData(const T&, int);

        T& retrieve(NodeDoble<T>*);
        std::string toString()const;
        void deleteAll();
        NodeDoble<T>* busqLineal(const T&e, int option);
        void quickSort(int);
        ListDoble& operator = (const ListDoble&);

        template <class U>
        friend std::ostream& operator<<(std::ostream&, const ListDoble<U>&);
        template <class U>
        friend std::istream& operator>>(std::istream&, ListDoble<U>&);
        void writeToDisk(const std::string& fileName);
        void readFromDisk(const std::string& fileName);
    };



using namespace std;

template <class T>
void ListDoble<T>::copyAll(const ListDoble<T>& l){
    NodeDoble<T>* aux(l.anchor);
    NodeDoble<T>* last(nullptr);
    NodeDoble<T>* newNode;

    while(aux != nullptr){
        if(newNode = new NodeDoble(aux->getData()) == nullptr){
            throw Exception("Error, memoria no disponible");
            }
        if(last == nullptr){
            anchor == newNode;
        }
        else{
            newNode->setPrev(last);
            last->setNext(newNode);
            }

        last = newNode;
        aux = aux->getNext();
        }
    }

template <class T>
bool ListDoble<T>::isValid(NodeDoble<T>* p)const{
    NodeDoble<T>* aux(anchor);

    while(aux != nullptr){
        if(aux == p){
            return true;
            }
        aux = aux->getNext();
        } 
    return false;
    }
 
template <class T>
ListDoble<T>::ListDoble(): anchor(nullptr){}

template <class T>
ListDoble<T>::ListDoble(const ListDoble<T>& l): anchor(nullptr){
    copyAll(l);
    }

template <class T>
ListDoble<T>::~ListDoble(){
    deleteAll();
    }

template <class T>
bool ListDoble<T>::isEmpty()const{
    return this->anchor == nullptr;
    }

template <class T>
void ListDoble<T>::insertData(NodeDoble<T>* p, const T& e){
    if(p != nullptr && !isValid(p)){
        throw Exception("Posicion Invalida, insertData");
        }

    NodeDoble<T>* aux(new NodeDoble(e));
    if(aux == nullptr){
        throw Exception("Memoria no disponible, insertData");
        }

    if(p == nullptr){//Insertar al principio
        aux->setNext(anchor);

        if(anchor != nullptr){//Si hay nodo al principio
            anchor->setPrev(aux);
            }
        anchor = aux;
        }
    else{//No al principio
        aux->setPrev(p);
        aux->setNext(p->getNext());

        if(p->getNext() != nullptr){//Si hay un nodo adelante
            p->getNext()->setPrev(aux);
            }
        p->setNext(aux);
        }
    }

template <class T>
void ListDoble<T>::deleteData(NodeDoble<T>* p){
    if(!isValid(p)){
        throw Exception("Posicion Invalida, deleteData");
        }

    if(p->getPrev() != nullptr){//Si hay nodo anterior
        p->getPrev()->setNext(p->getNext());
        }

    if(p->getNext() != nullptr){//Si hay nodo siguiente
        p->getNext()->setPrev(p->getPrev());
        }

    if(p == anchor){//Eliminar primera posicion
        anchor = anchor->getNext();
        }
    delete p;
    }

template <class T>
NodeDoble<T>* ListDoble<T>::getFirstPos(){
    return this->anchor;
    }

template <class T>
NodeDoble<T>* ListDoble<T>::getLastPos(){
    if(isEmpty()){
        return nullptr;
        }

    NodeDoble<T>* aux(anchor);
    while(aux->getNext() != nullptr){
        aux = aux->getNext();
        }
    return aux;
    }

template <class T>
NodeDoble<T>* ListDoble<T>::getPrevPos(NodeDoble<T>* p){
    if(!isValid(p)){
        return nullptr;
        }

    return p->getPrev();
    }

template <class T>
NodeDoble<T>* ListDoble<T>::getNextPos(NodeDoble<T>* p){
    if(!isValid(p)){
        return nullptr;
        }

    return p->getNext();
    }

template <class T>
NodeDoble<T>* ListDoble<T>::findData(const T& e, int type){
    NodeDoble<T>* aux(anchor);
    T search(aux->getData());

    switch(type){
    case 1:
            while (aux != nullptr and search.getName() != e.getName()) {
                aux = aux->getNext();
                search = aux->getData();
                }
            break;
        case 2:
            while (aux != nullptr and search.getCategory() != e.getCategory()) {
                aux = aux->getNext();
                search = aux->getData();
                }
            break;
        }

    return aux;
    }

template <class T>
T& ListDoble<T>::retrieve(NodeDoble<T>* p){
    if(!isValid(p)){
        throw Exception("Posicion Invalida, retrive");
        }
    return p->getData();
    }

template <class T>
string ListDoble<T>::toString()const{
    string result;
    NodeDoble<T>* aux(anchor);

    while(aux != nullptr){
        result += aux->getData().toString()+"\n";
        aux = aux->getNext();
        }

    return result;
    }

template <class T>
void ListDoble<T>::deleteAll(){
    NodeDoble<T>* aux;

    while(anchor != nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
        }
    }

template <class T>
NodeDoble<T>* ListDoble<T>::busqLineal(const T& e, int option){
    T cancion;
    NodeDoble<T>* aux(anchor);
    
    if(option == 1){
        while(aux != nullptr){
            T cancion = aux->getData();
            if(cancion.getSongName() == e.getSongName()){
                return aux;
                }
            aux = aux->getNext();
            }
        }

    if(option == 2){
        while(aux != nullptr){
            T cancion = aux->getData();
            if(cancion.getSinger() == e.getSinger()){
                return aux;
                }
            aux = aux->getNext();
            }
        }
    return nullptr;
    }

template <class T>
void ListDoble<T>::quickSort(int option) {//Quick Sort publico
    quickSort(getFirstPos(), getLastPos(), option);
    }

template <class T>
void ListDoble<T>::quickSort(NodeDoble<T>* low, NodeDoble<T>* high, int option) {
    if (low != nullptr && high != nullptr && low != high && isValid(low) && isValid(high) && low != high->getNext()) {
        NodeDoble<T>* p = partition(low, high, option);

        // Ordenar las dos mitades
        quickSort(low, getPrevPos(p), option);
        quickSort(getNextPos(p), high, option);
        }
    }

template <class T>
NodeDoble<T>* ListDoble<T>::partition(NodeDoble<T>* low, NodeDoble<T>* high, int option) {
    NodeDoble<T>* i = getPrevPos(low);
    NodeDoble<T>* pivot = high;
    NodeDoble<T>* j = low;

    for (j; j != high; j = getNextPos(j)) {
        bool compResult = false;
        if (option == 1) {
            // Comparar por nombre
            compResult = j->getData() < pivot->getData();
        } else if (option == 2) {
            // Comparar por tiempo de preparación
            compResult = pivot->getData() > j->getData();
        }

        if (compResult) {
            i = (i == nullptr) ? anchor : getNextPos(i);
            swap(i, j);
        }
    }

    i = (i == nullptr) ? anchor : getNextPos(i);
    swap(i, pivot);

    return i;
}

template <class T>
void ListDoble<T>::swap(NodeDoble<T>* node1, NodeDoble<T>* node2) {
    if (node1 != nullptr && node2 != nullptr && isValid(node1) && isValid(node2)) {
        T tmp = node1->getData();
        node1->setData(node2->getData());
        node2->setData(tmp);
    }
}


template <class T>
ListDoble<T>& ListDoble<T>::operator = (const ListDoble<T>& l){
    deleteAll();
    copyAll(l);
    return *this;    
    }

template <class U>
std::ostream& operator<<(std::ostream& os, const ListDoble<U>& list) {
        typename ListDoble<U>::NodeDoble* current = list.anchor->getNext();
        while (current != nullptr) {
            os << current->getData() <<endl;
            current = current->getNext();
        }
        return os;
    }

template <class U>
std::istream& operator>>(std::istream& is, ListDoble<U>& l){
    typename ListDoble<U>::NodeDoble* current = l.anchor;
    while(current != nullptr){
        is >> current->getData();
        current = current->getNext();
    }
    return is;
    }

template <class T>
void ListDoble<T>::writeToDisk(const std::string& fileName){
    ofstream file;

    file.open(fileName, ios_base::trunc);

    if(!file.is_open()){
        throw Exception("No se pudo abrir archivo para escritura, writeToDisk");
        }

    NodeDoble<T>* current = anchor;
    while(current != nullptr){
        file << current->getData();
        current = current->getNext();
        }
    file.close();
    }

template <class T>
void ListDoble<T>::readFromDisk(const std::string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    deleteAll();

    T data;
    while (file >> data) {
        NodeDoble<T>* newNode = new NodeDoble<T>(data);
        insertData(getLastPos(), data);
    }

    file.close();
}

#endif
