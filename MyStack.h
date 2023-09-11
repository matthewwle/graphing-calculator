#ifndef MY_STACK_H
#define MY_STACK_H
#include <iostream>
using namespace std;

#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
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

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe){
        node<TT>* walker = printMe._top;
        while(walker != nullptr){
            outs << *walker;
            walker = walker->_next;
        }
        return outs;
     }

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};
template <typename T>
Stack<T> :: Stack(){//default ctor
    _top = nullptr;
    _size = 0;
}
template <typename T>
Stack<T> ::Stack(const Stack<T>& copyMe): _size(copyMe._size){//sets arguements to member vars
    _top = _copy_List(copyMe._top);
}
template <typename T>
Stack<T> ::~Stack(){//deletes the _top
    delete _top;
}
template <typename T>
Stack<T>& Stack<T> :: operator=(const Stack<T>& RHS){//copy consturctor
    delete _top;
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}
template <typename T>//returns top
T Stack<T> ::top(){
    return _top->_item;
}
template <typename T>//returns if empty
bool Stack<T> :: empty(){
    return (_size == 0);
}
template <typename T>
void Stack<T> :: push(T item){//adds item to stack 
    _insert_head(_top, item);
    _size++;
}
template <typename T>
T Stack<T> :: pop(){//takes item off stack
    T item = _top->_item;
    _delete_node(_top,_top);
    _size--;
    return item;
}
template <typename T>
typename Stack<T> :: Iterator Stack<T> :: begin() const{
    Iterator a(_top);
    return a;
}     
template <typename T>        //Iterator to the head node
typename Stack<T> :: Iterator Stack<T> :: end() const{
    Iterator a(nullptr);
    return a;
}                //Iterator to NULL


#endif