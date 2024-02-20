#ifndef NODEDOBLE_HPP
#define NODEDOBLE_HPP

template <class T>
class NodeDoble{
    private:
        T data;
        NodeDoble* prev;
        NodeDoble* next;

    public:
        NodeDoble();
        NodeDoble(const T&);

        T& getData();
        NodeDoble* getPrev();
        NodeDoble* getNext();

        void setData(const T&);
        void setPrev(NodeDoble*);
        void setNext(NodeDoble*);
    };


template<class T>
NodeDoble<T>::NodeDoble(): prev(nullptr), next(nullptr){}

template<class T>
NodeDoble<T>::NodeDoble(const T& e):data(e),prev(nullptr), next(nullptr){}

template<class T>
T& NodeDoble<T>::getData(){
    return data;
    }

template<class T>
NodeDoble<T>* NodeDoble<T>::getPrev(){
    return prev;
    }

template<class T>
NodeDoble<T>* NodeDoble<T>::getNext(){
    return next;
    }

template<class T>
void NodeDoble<T>::setData(const T& e){
    data = e;
    }

template<class T>
void NodeDoble<T>::setPrev(NodeDoble* p){
    prev = p;
    }

template<class T>
void NodeDoble<T>::setNext(NodeDoble* p){
    next = p;
    }

#endif

