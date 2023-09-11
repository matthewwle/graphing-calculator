#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <assert.h>
#include "../node/node.h"
#include <iostream>
using namespace std;

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head);

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key);


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                            ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE> *after_this,
                                ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE>* before_this,
                                ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                        node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                ITEM_TYPE item,
                                bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                        ITEM_TYPE item,
                                        bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                ITEM_TYPE item,
                                bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function.



template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* p = head;
    while (p != nullptr)
    {
        cout << *p;
        p = p->_next;
    }
    cout << endl;
}

template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr)
    {
        if (walker->_item == key)
            return walker;
        else
            walker = walker->_next;
    }
    return nullptr;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this, head);
    head = temp;
    return temp;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
    if (head == nullptr){
        _insert_head(head, insert_this);
        return head;
    }
    node<ITEM_TYPE>* store = after_this->_next;
    node<ITEM_TYPE>* result = new node<ITEM_TYPE> (insert_this, store);
    after_this->_next = result;
    return result;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this){
    node<ITEM_TYPE>* before = _previous_node(head, before_this); 
    if (before == nullptr){
        return _insert_head(head, insert_this);
    }   
    return _insert_after(head, before, insert_this);
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
    node<ITEM_TYPE>*walker = head;
    if (head == prev_to_this)
        return nullptr;
    while (walker != nullptr){
        if (walker->_next == prev_to_this)
            return walker;
        else
            walker = walker->_next;
    }
    assert(0);
    
}

template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
    //assert(head!= nullptr);
    ITEM_TYPE val = delete_this->_item;
    if (head == delete_this){
        node<ITEM_TYPE>* hold = head->_next;
        delete head;
        head = hold;
    }
    else
    {
        node<ITEM_TYPE>* before = _previous_node(head, delete_this);
        node<ITEM_TYPE>* after = delete_this->_next;
        delete delete_this;
        before->_next = after;
    }
    return val;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* newHead = nullptr;
    _copy_list(newHead, head);
    return newHead;
}


template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
if (src == nullptr)
        return nullptr;

    _clear_list<T>(dest);
    node<T>* walker = src;
    node<T>* destWalk = dest;
    while (walker != nullptr){
        destWalk = _insert_after(dest, destWalk, walker->_item);
        walker = walker->_next;
    }
    return destWalk;

}


template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
    while (head != nullptr){
        _delete_node(head, head);
    }
    
}


template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
    for (int i = 0; i < pos; i++){
        head = head->_next;
    }
    return head->_item;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
    node<ITEM_TYPE>* insertHere = _where_this_goes(head, item, ascending);
    if (insertHere == nullptr){
        return _insert_head(head, item);
    }
    node<ITEM_TYPE>* result = _insert_after(head, insertHere, item);
    return result;  
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
    node<ITEM_TYPE>* insertHere= _search_list(head, item);
    if (insertHere){
        insertHere->_item = insertHere->_item + item;
    }
    else
    insertHere = _insert_sorted(head, item ,ascending);
    
    return insertHere;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending){
    if(head == nullptr){
        return nullptr;
    }
    node<ITEM_TYPE>* current = head;
    node<ITEM_TYPE>* next = head->_next;
    if(ascending){
        if (current->_item > item)
            return nullptr;
        while(next != nullptr){
            if (current->_item <= item && next->_item > item)
                return current;
            else{
                current=current->_next;
                next = next->_next;
            }
        }
    }
    else{
        if(current->_item < item)
            return nullptr;
        while(next != nullptr){
            if (current->_item >= item && next->_item < item){
                return current;
        }
        else{
            current = current->_next;
            next = next->_next;
        }
        
    }
    }
    return current;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
    while (head->_next != nullptr){
        head = head->_next;
    }
    return head;
}


#endif
