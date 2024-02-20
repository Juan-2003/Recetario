
#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <fstream>
#include "node.hpp"

class Exception : public std::exception {
private:
    std::string msg;

public:
    Exception() noexcept : msg("Error indefinido") {}
    Exception(const Exception& ex) noexcept : msg(ex.msg) {}
    Exception(const std::string& m) : msg(m) {}
    Exception& operator = (const Exception& ex) noexcept {
        msg = ex.msg;
        return *this;
        }
    virtual ~Exception() {}
    virtual const char* what() const noexcept {
        return msg.c_str();
        }
    };

//DEFINICION DE LA LISTA SIMPLEMENTE LIGADA
template <class T>
class List {
private:
    Node<T>* anchor;

    void copyAll(const List&);

    bool isValidPos(Node<T>*) const;
    void mergeSort(Node<T>*&);
    Node<T>* merge(Node<T>*, Node<T>*);
    Node<T>* getMiddle(Node<T>*);

public:
    List();
    List(const List&);
    ~List();

    bool isEmpty() const;

    void insertData(Node<T>*, const T&);

    void deleteData(Node<T>*);

    Node<T>* getFirstPos();
    Node<T>* getLastPos();
    Node<T>* getPrevPos(Node<T>*);
    Node<T>* getNextPos(Node<T>*);

    Node<T>* findData(const T&, const int);

    T& retrieve(Node<T>*);
    std::string toString();
    void deleteAll();
    void mergeSort();

    List& operator =(const List&);
    template<class U>
    friend std::ostream& operator<<(std::ostream&, const List<U>&);
    template <class U>
    friend std::istream& operator>>(std::istream&, List<U>&);
    void writeToDisk(const std::string& fileName);
    void readFromDisk(const std::string&);

    };

//IMPLEMENTACION
using namespace std;

template<class T>
List<T>::List() : anchor(nullptr) {}

template<class T>
List<T>::List(const List& l) : List() {
    copyAll(l);
    }

template<class T>
List<T>::~List() {
    deleteAll();
    }

template<class T>
void List<T>::copyAll(const List& l) {
    Node<T>* aux(l.anchor);
    Node<T>* lastInserted(nullptr);
    Node<T>* newNode;

    while (aux != nullptr){
        if ((newNode = new Node(aux->getData())) == nullptr) {
            Exception("Memoria no disponible, copyAll");
            }
        if (lastInserted  == nullptr) {
            anchor = newNode;
        } else {
            lastInserted->setNext(newNode);
            }
        lastInserted = newNode;
        aux = aux->getNext();
        }
    }

template<class T>
bool List<T>::isValidPos(Node<T>* p) const {
    Node<T>* aux(anchor);

    while(aux != nullptr){
        if (aux == p){
            return true;
            }
        aux = aux->getNext();
        }
    return false;
    }

template<class T>
bool List<T>::isEmpty() const {
    return anchor == nullptr;
    }

template<class T>
void List<T>::insertData(Node<T>* p, const T& e) {
    if(p!= nullptr and !isValidPos(p)){
        throw Exception("Posicion invalida, insertData");
        }

    Node<T>* aux(new Node(e));

    if (aux == nullptr){
        throw Exception("Memoria no disponible, insertData");
        }
    if (p == nullptr){ //al principio
        aux->setNext(anchor);
        anchor = aux;
    } else { //no al principio
        aux->setNext(p->getNext());
        p->setNext(aux);
        }
    }

template<class T>
void List<T>::deleteData(Node<T>* p) {
    if (!isValidPos(p)){
        throw Exception("Posicion invalida, deleteData");
        }
    if (p == anchor){ //eliminar primero
        anchor = p->getNext();
    } else { //eliminar cualquier otro
        getPrevPos(p)->setNext(p->getNext());
        }
    delete p;
    }

template<class T>
Node<T>* List<T>::getFirstPos(){
        return anchor;
    }

template<class T>
Node<T>* List<T>::getLastPos() {
    if (isEmpty()){
        return nullptr;
        }
    Node<T>* aux(anchor);
    while (aux->getNext() != nullptr){
        aux = aux->getNext();
        }
    return aux;
    }

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) {
    if (isEmpty() or p == anchor){
        return nullptr;
        }
    Node<T>* aux(anchor);
    while(aux != nullptr and aux->getNext() != p){
        aux = aux->getNext();
        }
    return aux;
    }

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if (!isValidPos(p)){
        return nullptr;
        }
    return p->getNext();
    }

template<class T>
Node<T>* List<T>::findData(const T& e, const int tipo) {
    Node<T>* aux(anchor);
    T search(aux->getData());

    switch (tipo) {
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

template<class T>
T& List<T>::retrieve(Node<T>* p){
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
        }
    return p->getData();
    }

template<class T>
std::string List<T>::toString() {
    string result;
    Node<T>* aux(anchor);

    while (aux != nullptr){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
        }
    return result;
    }

template<class T>
void List<T>::deleteAll() {
    Node<T>* aux;

    while (anchor != nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
        }
    }

template<class T>
void List<T>::mergeSort(){ //Merge sort publico
    mergeSort(anchor);
}
template<class T>
void List<T>::mergeSort(Node<T>*& head) {
    if (head == nullptr || head->getNext() == nullptr) {// Lista vacía o con un solo elemento, ya está ordenada
        return; 
    }

    // Dividir la lista en dos mitades
    Node<T>* middle = getMiddle(head);
    Node<T>* middle2 = middle->getNext();

    middle->setNext(nullptr); // Separar las dos mitades

    // Ordenar recursivamente ambas mitades
    mergeSort(head);
    mergeSort(middle2);

    // Combinar las mitades ordenadas
    head = merge(head, middle2);
}

template<class T>
Node<T>* List<T>::merge(Node<T>* left, Node<T>* right) {
    Node<T>* result = nullptr;

    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    // Comparar los elementos de ambas listas y combinar en orden
    if (left->getData() <= right->getData()) {
        result = left;
        result->setNext(merge(left->getNext(), right));
    } else {
        result = right;
        result->setNext(merge(left, right->getNext()));
    }

    return result;
}

template<class T>
Node<T>* List<T>::getMiddle(Node<T>* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node<T>* slow = head;
    Node<T>* fast = head->getNext();

    while (fast != nullptr && fast->getNext() != nullptr) {//Se detendra cuando llegue al final de la lista
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    return slow;
}

template<class T>
List<T>& List<T>::operator=(const List& l) {
    deleteAll();
    copyAll(l);
    return *this;
    }


template <class U>
std::istream& operator>>(std::istream& is, List<U>& l) {
    Node<U>* current = l.getFirstPos();
    while (current != nullptr) {
        is >> l.retrieve(current);
        current = l.getNextPos(current);
    }
    return is;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const List<U>& list) {
    Node<U>* current = const_cast<List<U>&>(list).getFirstPos();
    while (current != nullptr) {
        os << const_cast<List<U>&>(list).retrieve(current) << std::endl;
        current = const_cast<List<U>&>(list).getNextPos(current);
    }
    return os;
}

template <class T>
void List<T>::writeToDisk(const string& fileName){
    ofstream file;

    file.open(fileName, ios_base::trunc);

    if(!file.is_open()){
        throw Exception("No se pudo abrir archivo para escritura, writeToDisk");
        cout<<"error";
        return;
        }

    Node<T>* current = anchor;
    while(current != nullptr){
        file<<current->getData()<<endl;
        current = current->getNext();
        }

    file.close();
    }

template <class T>
void List<T>::readFromDisk(const string& fileName){
    ifstream myFile;
    T data;

    myFile.open(fileName);

    if(!myFile.is_open()){
        throw Exception("No se puedo abrir el archivo para lectura, readFromDisk");
        }
    deleteAll();

    while(myFile>>data){
        insertData(nullptr, data);
        }
    myFile.close();
    
}

#endif
