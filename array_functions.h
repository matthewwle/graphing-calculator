#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <iostream>

using namespace std;

const int MINIMUM_CAPACITY = 3;


template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);            
/*
Precondition: no precondition
Postcondition: the pointer that points to dynamic array is returned
Purpose: to create a dynamic array of size capacity
Arguements: capacity
Return Value: pointer that points to the start of the dynamic array created
*/
template<class T>
T* reallocate(T* a, int size, int capacity);  
//Precondition: a is declared and intitialized correctly, size is correct
//Postcondition: the pointer that points to the new array is returned and the old array is deleted
//Purpose: to "resize" an array by making a new one with the new size and copying and deleting the old one
//Arguements: old array, size of old array and capacity of new array
//Return Value: new array pointer
template<class T>
void print_array(T* a, int size, int capacity = 0);
//PRINT ARRAYS
//Precondition: array and size are correct
//Postcondition: the array is printed for print function and the array is printed along
//               with size and capacity for print_array function
//Purpose: to display the array in the output
//Arguements: array, size, and capacity (for print array function )
//Return Value: none
template <class T>
void print(T* a, unsigned int how_many);

template<class T>
T* search_entry(T* a, int size, const T& find_me);
//Search Functions
//Precondition: a and size is correct
//Postcondition: the pointer pointing to the value, or the index of the value is returned
//               or -1 or nullptr if not found
//Purpose: the see if the find_me value is in the array
//Arguements: array, size and value that is to be found
//Return Value: the index of the value, pointer pointing to the value, or -1 or nullptr
template <class T>
int search(T* a, int size, const T& find_me);

template <class T>
void shift_left(T* a, int& size, int shift_here);

template <class T>
void shift_left(T* a, int& size, T* shift_here); 
//Shift Functions
//Precondition: array and size are correct
//Postcondition: the array is shifted at the shift here pointer or index
//Purpose: to shift the array to the right or to the left
//Arguements: array, size and index/pointer where to shift
//Return Value: no return value
template <class T>
void shift_right(T *a, int &size, int shift_here);

template <class T>
void shift_right(T *a, int &size, T* shift_here);

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy);
//Copy Array
//Precondition: arrays and size are correct
//Postcondition: the array is copied into the new array, pointer of new array is returned
//Purpose: to copy an array into a new array
//Arguements: destination array, original array, size
//Return Value: pointer of the new array
template <class T>
T* copy_array(const T *src, int size);

template <class T>
string array_string(const T *a, int size);
//Precondition: array and size are correct
//Postcondition: string with array is returned
//Purpose: to turn an array into a string
//Arguements: array, size
//Return Value: string of the array

template <class T> 
void append(T* a, int& size, T* append_me);

template<class T>
T* allocate(int capacity){
    T* pointer = new T[capacity];//declaring dynamic array with size capacity

    return pointer;
}

template<class T>
T* reallocate(T* a, int size, int capacity){
    // T* newArray = allocate<T>(capacity);//making new array with new size
    T *newArray = new T [capacity];
    copy_array(newArray, a, size);//copying old array into new array
    delete[] a;//deleting old array

    return newArray;
}

template <class T>
void print(T* a, unsigned int how_many){//prints array by walking through array and cout'ing
    T* walker = a;
    cout << "[ ";
    for (int i = 0; i < how_many; i++){
        if (i != how_many -1)
        cout << *walker << ", ";
        else
        cout << *walker;
        walker++;
    }
    cout << " ]" ;
}

template<class T>
void print_array(T* a, int size, int capacity){//prints array with size and capacity
    print(a,size);
    cout <<"("<< size << "/" <<  capacity << ")"<<endl;
}

template<class T>
T* search_entry(T* a, int size, const T& find_me){
    int val = search(a, size, find_me);//gets index of find_me
    T* returnVal = a;
    returnVal += val;//adds the index to the starting pointer to get the pointer to the index val
    if (val == -1)//if find_me is not found the nullptr is returned
    return nullptr;
    else
    return returnVal;//returns the pointer pointing to the find_me num
}

template <class T>
int search(T* a, int size, const T& find_me){
    T* walker = a;
    for(int i = 0; i < size; i++){
        if(*walker == find_me){//checks if each value in a array is equal to find me
            return i;//returns index if numbers are equal
        }
        walker++;
    }
    return -1;
}

template <class T>
void shift_left(T* a, int& size, int shift_here){
T* walker = a + shift_here;
T* nextVal = walker +1;
for (int i = shift_here; i < size-1; i++){//sets each value equal to the value after that starting at shift_here
    *walker = *nextVal;
    walker++;
    nextVal++;
}
size--;//decrements size because the size decreases
}

template <class T>
void shift_left(T* a, int& size, T* shift_here){
int b = shift_here-a;//turns pointer into an index and calls shift_left
shift_left(a, size, b);
}

template <class T>
void shift_right(T *a, int &size, int shift_here){
T* walker = a + size;
T* prevVal = walker -1;
for (int i = size; i > shift_here; i--){//sets each value to the one before it but starts at index size
    *walker = *prevVal;
    walker--;
    prevVal--;
}
size++;//size increases by 1
}

template <class T>
void shift_right(T *a, int &size, T* shift_here){
int b = shift_here - a;//turns shift_here into an index and calls shift_right
shift_right(a, size, b);
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy){
    T* walker = dest;
    for (int i = 0; i < many_to_copy; i++){//copies the src array into the dest array
        *walker = *src;
        walker++;
        src++;
    }
}

template <class T>
T* copy_array(const T *src, int size){
T* array = new T[size];
T* walker = array;
for (int i = 0; i < size; i++){//makes a new array and copies src into it and returns the pointer
    *walker = *src;
    walker++;
    src++;
}
return array;
}

template <class T>
string array_string(const T *a, int size){
string array = "[ ";
const T* walker = a;
for (int i = 0; i < size; i ++){
    if (i == size-1)
    array += to_string(*walker);
    else
    array += to_string(*walker) + ", ";
    walker++;
}
array += " ]";
return array;
}

template <class T> 
void append(T* a, int& size, T append_me){
    a += size;
    *a = append_me;
    size++;
}

#endif