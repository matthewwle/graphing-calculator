#ifndef MY_QUEUE_H
#define MY_QUEUE_H
#include <iostream>
using namespace std;

#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator(){
            _ptr = nullptr;
        }                                     //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }                   //Point Iterator to where p is pointing to
        operator bool(){
            return (!(_ptr));
        }                                //casting operator: true if _ptr not NULL
                                                        //      this turned out to be a pain!


        T& operator *(){
            return (_ptr->_item);
        }                        //dereference operator
        T* operator ->(){
            return &(_ptr->_item);
        }                       //member access operator

        bool is_null(){
            return !(_ptr);
        }                                 //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right){
            return !(left._ptr == right._ptr);
        } //true if left != right

        friend bool operator ==(const Iterator& left, const Iterator& right){
            return (left._ptr == right._ptr);
        } //true if left == right

        Iterator& operator++(){
            _ptr = _ptr->_next;
            return *this;
        }                         //member operator: ++it; or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused){
            Iterator hold(it._ptr);
            ++it;
            return hold;
        }         //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        node<TT>* walk = printMe._front;
        while (walk != printMe._rear){
        outs << *walk;
        walk = walk->_next;
    }
    outs << *walk << endl;
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};
template <typename T>
Queue<T> ::Queue(){//default ctor
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}
template <typename T>
Queue<T> ::Queue(const Queue<T>& copyMe):_front(nullptr){//sets front to nullptr and rear to the last node
    _rear = _copy_list(_front,copyMe._front);
    _size = copyMe._size;
}
template <typename T>
Queue<T> :: ~Queue(){//destructor
_clear_list(_front);
}
template <typename T>
Queue<T>& Queue<T> ::operator=(const Queue<T>& RHS){//copy constructor
    _clear_list(_front);//clears front incase theres anything inside
    _front = nullptr;//sets it to nullptr
    _rear = _copy_list(_front,RHS._front);//copies
    _size = RHS._size;
    return *this;
}
template <typename T>

bool Queue<T> :: empty(){//returns if empty
 return (_size == 0);
}
template<typename T>
T Queue<T> ::front(){//returns front
    return _front->_item;
}
template<typename T>
T Queue<T> ::back(){//returns back 
    return _rear->_item;
}
template<typename T>
void Queue<T> :: push(T item){//adds item to end of queue
    if(_rear == nullptr){
        _rear = _insert_head(_front, item);
    }
    else
        _rear = _insert_after(_front, _rear, item);
    _size++;
}
template<typename T>
T Queue<T> :: pop(){// gets item from front of queue
    T item = _front->_item;
    _delete_node(_front,_front);
    _size--;
    return item;
}
template <typename T>

typename Queue<T> :: Iterator Queue<T> :: begin() const{
    Iterator a(_front);
    return a;
}            //Iterator to the head node
template <typename T>
typename Queue<T> :: Iterator Queue<T> :: end() const{
    Iterator a(nullptr);
    return a;
}              //Iterator to NULL

template<typename T>
void Queue<T> :: print_pointers(){
    node<T>* walk = _front;
    while (walk != _rear){
        cout << *walk << "|";
        walk = walk->_next;
    }
    cout << *walk << endl;
}


#endif