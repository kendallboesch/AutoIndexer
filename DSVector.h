//
// Created by Kendalll Boesch on 2/15/22.
//
// ALL CODE IN HERE
/**********
 *      - resize - grow as needed
 *      - add
 *      -access
 *      -search
 *      -iterator -- keep track of where you are in your vector
 *      -
 *
 *
 */
#ifndef INC_21F_PA02_DSVECTOR_H
#define INC_21F_PA02_DSVECTOR_H
#include <iostream>
#include <stdexcept>
#include <ostream>
#include "DSIterator.h"
using namespace std;

template <typename T>       // above any implementation of a function that uses T
class DSVector
        {
        private:
            T* data;
            int size;       // HOW MANY ELEMENTS ARE IN THE VECTOR
            int cap;        // VECTOR CAPACITY
            int available;  // HOW MANY AVAILABLE SPACES LEFT IN ARRAY


            void resize();

        public:

            DSVector();
            DSVector(const DSVector<T>&);
            ~DSVector();
            T& operator[](int) const;
            T& at(int) const;
            DSVector& operator=(const DSVector<T>&);
            bool operator ==(const DSVector<T>&) const;
            DSVector& operator+(const DSVector<T>&);
            int getSize();
            int getCap();
            T* getData();
            int getAvailable();
            void updateAvailability();
            T& push_back(T);
            T pop_back();
            T& insertAt(const T&, int);
            T remove(int);
            T& push_front(const T&);
            bool autoAdjust();
            int generateCap(const int) const;
            int search(const T) const;
            void empty();
            int search(const T&);
            T& begin();
            T& end();
            T* at(const int);
            void swap(T&, T&);
};
/*********
 * DEFAULT CONSTRUCTOR
 *
 * INITIALIZED CAP TO 10, SIZE TO 0, AND
 *
 * @tparam T
 *********/
template <typename T>
DSVector<T>::DSVector()
{
    size = 0;
    cap = 10;
    data = new T[cap];
    updateAvailability();

}
/**************
 *      COPY CONSTRUCTOR
 *
 * @tparam T
 * @param arg
 */
template <typename T>
DSVector<T>::DSVector(const DSVector<T>& arg)
{
    size = arg.size;
    cap = arg.cap;
    updateAvailability();
    autoAdjust();
    data = new T[cap];
    for(int i = 0; i < size; i++)
    {
        data[i] = arg[i];
    }
   // DSIterator<T> itr(this->beginning(), data->end(), data->beginning());
    updateAvailability();
}
/*************
 *      DESTRUCTOR
 * @tparam T
 */
template<typename T>
DSVector<T>::~DSVector()
{
    delete [] data;
    size = 0;
    cap = 0;
    available = 0;
}
/************
 *      OVERLOADED INDEX OPERATOR
 * @tparam T
 * @param index
 * @return
 */
template <typename T>
T& DSVector<T>::operator[](int index) const
{
    if(index >= 0 && index < size)      // IF INDEX IS IN BOUNDS
    {
        return data[index];     // RETURN ELEMENT AT REQUESTED INDEX
    }
    else    // IF THE INDEX WAS OUT OF BOUNDS
    {
        throw std::runtime_error("ERROR - VECTOR INDEX OUT OF BOUNDS"); //THROW AN ERROR
    }
}
/***************
 *  AT
 *
 *  RETERNS ELEMENT AT INDEX
 *
 * @tparam T
 * @param index
 * @return
 */
template <typename T>
T& DSVector<T>::at(int index) const
{
    if(index >= 0 && index < size)      // IF INDEX IS IN BOUNDS
    {
        return data[index];     // RETURN ELEMENT AT REQUESTED INDEX
    }
    else    // IF THE INDEX WAS OUT OF BOUNDS
    {
        throw std::runtime_error("ERROR - VECTOR INDEX OUT OF BOUNDS"); //THROW AN ERROR
    }
}
/****************
 *      OVERLOADED ASSIGNMENT OPERATOR
 *
 * @tparam T
 * @param arg
 * @return
 */
template <typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& arg)
{

    size = arg.size;
    cap = arg.cap;
    autoAdjust();       // ENSURE CAP > SIZE && CAP > SIZE + 1

    delete [] data;
    data = new T[arg.cap];
    for(int i = 0; i < size; i++)
    {
        data[i] = arg[i];       // COPY EACH ELEMENT
    }
    updateAvailability();       // UPDATE AVAILABLE SPACES
    return *this;
}

/*******************
 *      RESIZE
 *
 *    RETURNS A VECTOR CONTAINING THE ORIGINAL
 *    ELEMENTS, BUT WITH DOUBLE THE CAPACITY
 * @tparam T
 */
template <typename T>
void DSVector<T>::resize()
{
   T* temp = new T[this->cap * 2];        // CREATE THE SPACE
   cap = cap *2;
   for(int i = 0; i < size; i++)
   {
       temp[i] = data[i];           // TRANSFER ORIGINAL DATA
   }
   delete [] data;                  // DELETE OLD VECTOR DATA
   data = temp;                         // REASSIN
  updateAvailability();     // UPDATE AVAILABLE SPACES
  cout << "resized" << endl;
}
/**********
 *      OVERLOADED COMPARISON OPERATOR
 *
 * @tparam T
 * @param arg
 * @return
 */
template <typename T>
bool DSVector<T>::operator==(const DSVector<T>& arg) const
{
    if (size != arg.size)       // IF THE TWO VECTORS ARE DIFFERENT SIZES THEN
    {                               // THEY ARE AUTOMATICALLY NOT EQUIVALENT
        return false;
    }
    else
    {
        for(int i = 0; i <size; i++)        // ITERATE THROUGH VECTOR
        {
            if(data[i] != arg.data[i])  // COMPARE THE ELEMENTS AT EACH INDEX
            {
                // IF THEY ARE NOT THE SAME
                return false;
            }
        }
    }
    return true;
}
/***********************
 *      GET SIZE
 *
 *   RETURNS VECTOR SIZE
 * @tparam T
 * @return
 */
template <typename T>
int DSVector<T>::getSize()
{
    return size;
}
/************************
 *      GET CAPACITY
 *
 *     RETURNS TOTAL VECTOR CAPACITY
 *
 * @tparam T
 * @return
 */
template <typename T>
int DSVector<T>::getCap()
{
    return cap;
}
/************
 *      PUSH_BACK
 *
 *      ADDS A NEW ELEMENT TO THE INDEX AT SIZE;
 *      UPDATES VECTOR ATTRIBUTES ACCORDINGLY
 *
 * @tparam T
 * @param arg
 * @return
 */
template <typename T>
T& DSVector<T>::push_back(T arg)
{
    autoAdjust();       // ENSURE THERE IS SPACE TO ADD
    data[size] = arg;   // ADD THE ELEMENT TO THE ENDING INDEX OF THE VECTOR
    size = size + 1;        // INCREMENT SIZE
    //cout << "Size: " << size << endl;
    updateAvailability();       // UPDATE AVAILABLE SPACES
    //cout << "pushed" << endl;
    return data[size - 1];      // RETURN LAST ELEMENT OF VECTOR -- THE ELEMENT JUST PUSHED
}
/***************
 *          POP_BACK
 *
 *       REMOVES THE LAST ELEMENT OF THE VECTOR
 *       & UPDATES ATTRIBUTES ACCORDINGLY.
 *       RETURNS POPPED ELEMENT
 * @tparam T
 * @return
 */
template <typename T>
T DSVector<T>::pop_back()
{
    T* returnVal = data[size];
    this->remove(data->size);   // CALL DSVECTOR::REMOVE()
    --size;             //INCREMENT SIZE
    updateAvailability();       // UPDATE AVAILABLE SPACES
    cout << "popped!" << endl;
    return returnVal;       // RETURN THE POPPED ELEMENT
}
/*******************
 *      INSERT AT
 *
 *    IN TAKES AN OBJECT AND AN INDEX FOR
 *    THE OBJECT TO BE INSERTED INTO THE ARRY.
 *    INSERTS PASSED OBJECT INTO THE INDEX & MOVES
 *    SUCEEDING ELEMENTS BACK
 * @tparam T
 * @param arg
 * @param insertIndex
 * @return
 */
template <typename T>
T& DSVector<T>::insertAt(const T& arg, int insertIndex)
{
    autoAdjust();
    if(insertIndex == size || insertIndex > size) // IF THE REQUESTED INDEX IS NOT IN T
    {                                               // IN INDEX 0 -> SIZE
        this->push_back(arg);       // ADD TO  INDEX SIZE

    }
    else
    {
        T *temp = new T[cap];
        for (int i = 0; i < insertIndex; i++)   // COPY OVER ELEMENTS BEFORE INSERT INDEX
        {
            temp[i] = data[i];
        }
        temp[insertIndex] = arg;        // ARG IS INSERTED AT THE REQUESTED INDEX
        for (int u = insertIndex + 1; u < size + 1; u++) {
            temp[u] = data[u - 1];      // COPY OVER ELEMENTS AFTER INSERT INDEX
        }

        delete[] data; // DELETE OLD DATA
        data = temp;    // ASSIGN NEW DATA
        ++size;     // INCREMENT SIZE
    }

    //delete [] temp;
    updateAvailability();       // UPDATE AVAILABLE SPACES
    return data[size -1];       // RETURN THE LAST ELEMENT
}
/*************
 *      REMOVE
 *
 *      REMOVE ELEMENT AT REQUESTED INDEX
 *      AND SHIFT SUCCEEDING ELEMENTS
 *      OVER ONE TO FILL GAP
 *
 * @tparam T
 * @param freedIndex
 * @return
 */
template <typename T>
T DSVector<T>::remove(int freedIndex)
{
    T* temp = new T[cap];
    T r;
    for(int i = 0; i < size; i++)       // ITERATE THROUGH
    {
       if(i < freedIndex)       // IF THE INDEX IS BEFORE THE ELEMENT TO BE REMOVED
       {
           temp[i] = data[i];
       }
       else if(i > freedIndex)  // IF THE ELEMENT IS AFTER THE ELEMENT TO BE REMOVED
       {
           temp[i - 1] = data[i];
       }
       else // IF THE ELEMENT IS THAT TO BE REMOVED
       {
           r = data[i]; // DO NOT COPY OVER TO TEMP, BUT SAVE IN 'REMOVE'
       }
    }
    delete [] data;     // DELETE OLD DATA
    data = temp;    // ASSIGN NEW DATA
    --size; // UPDATE SIZE
    updateAvailability();       // UPDATE AVAILABLE SPACES
    return r;
}
/****************
 *      PUSH_FRONT
 *
 *      ADDS ELEMENT TO STARTING INDEX OF VECTOR
 *      AND SHIFTS ALL SUCCEEDING ELEMENTS OVER ONE.
 *
 * @tparam T
 * @param arg
 * @return
 */
template <typename T>
T& DSVector<T>::push_front(const T& arg)
{
    autoAdjust();       // ENSURE THERE IS ENOUGH SPACE TO ADD
   T* temp = new T[cap];
   temp[0] = arg;   // INSERT ARG AT FIRST INDEX
   for(int i = 0; i < size ; i++)   // ITERATE THROUGH VECTOR
   {
       temp[i + 1] = data[i];   // ADD ORIGINCAL ELEMENTS AFTER NEW ONE
   }
    size = size + 1;        // UPDATE VECTOR SIZE
   delete [] data;      // DELETE ORIGINAL DATA
   data = temp;     // ASSIGN NEW DATA

    // UPDATE AVAILABLE SPACES
   updateAvailability();
   cout << "Pushed to front" << endl;
   // RETURN ELEMENT ADDED TO BEGINNING INDEX
   return data[0];

}
/*********************
 *      AUTOADJUST
 *
 *     IF VECTOR SIZE + 1 IS LARGER THAN OR EQUAL
 *     TO VECTOR CAPACITY, DOUBLE VECTOR CAPACITY
 *
 * @tparam T
 * @return
 */
template <typename T>
bool DSVector<T>::autoAdjust()
{
    if (size + 1 >= cap)    // CHECK IF SIZE + 1 IS GREATER THAN OR EQUAL TO CAPACITY
    {
        resize();   // DOUBLE CAPACITY
        cout << "adjusted" << endl;
        return true;
    }
    return false;
}
/**********
 *          GET AVAILABLE
 *
 *         RETURN AVAILABLE VECTOR SPOTS
 *
 * @tparam T
 * @return
 */
template <typename T>
int DSVector<T>::getAvailable()
{
    return available;   // RETURN AVAILABLE SPACES
}
/***********
 *  UPDATE AVAILABILITY
 *
 * @tparam T
 */
template <typename T>
void DSVector<T>::updateAvailability()
{
    available = cap - size;     // UPDATE AVAILABLE SPACES
}
/**************
 *
 * @tparam T
 * @param arg
 * @return
 */
template <typename T>
int DSVector<T>::search(const T arg) const
{
    for(int i = 0; i < size; i++)
    {
        if (data[i] == arg)
        {
            return i;
        }
    }
    return -1;
}
/*****
 *      EMPTY
 *
 * REMOVE ALL ELEMENTS FROM VECTOR
 * BY ITERATING THROUGH
 *
 * @tparam T
 */
template <typename T>
void DSVector<T>::empty()
{
    for(int i = 0; i < size; i++)
    {
        this->remove(i);
    }
    size = 0;               // UPDATE VECTOR ATTRIBUTES
    updateAvailability();

}

/**********
 *      SEARCH
 *
 *      ITEERATES THROUGH DSVECTOR TO FIND KEY
 *      IF KEY EXISTS IN VECTOR RETURN INDEX OF
 *      KEY, IF NOT RETURN -1
 * @tparam T
 * @param key
 * @return
 */
template <typename T>
int DSVector<T>::search(const T& key)
{
    for(int i = 0; i < size; i++)
    {
        if (data[i] == key)
        {
            return i;
        }
    }
    return -1;
}
/***********
 *      GET DATA
 *
 *      RETURNS POINETR TO FIRST ELEMENT  OF VECTOR DATA
 *
 * @tparam T
 * @return
 */
template <typename T>
T* DSVector<T>::getData()
{
    T* allData = new T[cap];
    for(int i = 0; i < size; i++)
    {
        allData[i] = data[i];
    }
    return allData;
}
/*******
 *      BEGIN()
 *
 *      RETURNS  FIRST ELEMENT
 *      IN DSVECTOR
 * @tparam T
 * @return
 */
template <typename T>
T& DSVector<T>::begin()
{
    return data[0];
}
/********
 *      END
 *
 *     RETURNS   END
 *     ELEMENT IN DSVECTOR
 *
 * @tparam T
 * @return
 */
template <typename T>
T& DSVector<T>::end()
{
   return data[size - 1];
}
/********
 *  SWAP
 *
 *  SWITCH ELEMENTS AT INDEX
 *  A AND INDEX B
 *
 * @tparam T
 * @param a
 * @param b
 */
template <typename T>
void DSVector<T>::swap(T &a, T &b)
{
    swap(a, b);
}
/***********
 *              AT
 *           RETURNS POINTER TO
 *           ELEMENT AT INDEX
 * @tparam T
 * @param index
 * @return
 */
template <typename T>
T* DSVector<T>::at(const int index)
{
    return &(this->data[index]);
}
#endif //INC_21F_PA02_DSVECTOR_H
