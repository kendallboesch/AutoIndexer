////
//// Created by Kendalll Boesch on 3/2/22.
////
//
//#ifndef INC_21F_PA02_DSITERATOR_H
//#define INC_21F_PA02_DSITERATOR_H
//using namespace std;
//template <typename T>
//class DSIterator {
//private:
//
//    T *first;
//    T *last;
//    T *curr;
//    T *next;
//    void setNext(T* inNext)
//    {
//        next = inNext;
//    }
//
//public:
//
//    bool atBeginning;
//    bool reachedEnd;
//    bool nextAvailable;
//    bool empty;
//
////};
//
//    DSIterator()
//    {
//
//        empty = true;
//        atBeginning = true;
//        nextAvailable = false;
//        first = new T;
//        next = nullptr;
//    }
//    DSIterator(T *fIn, T *lIn)
//    {
//        first = fIn;
//        last = lIn;
//        curr = first;
//        if(!isEmpty())
//        {
//            next = curr + 1;
//        }
//    }
//
//
//    DSIterator(T *eF, T *eL, T *eC)
//    {
//        first = eF;
//        last = eL;
//        curr = eC;
//        next = eC + 1;
//
//        empty = isEmpty();
//        atBeginning = atStart();
//
//        nextAvailable = nextExists();
//
//    }
//
//    ~DSIterator()
//    {
//        delete [] first;
//        delete [] last;
//        delete [] curr;
//        delete [] next;
//    }
//    DSIterator(const DSIterator<T>& toCopy)
//    {
//        first = toCopy->first;
//        last = toCopy->last;
//        curr = toCopy->curr;
//        next = toCopy->next;
//        empty = toCopy->isEmpty();
//        atBeginning = atStart();
//        nextAvailable = nextExists();
//
//        if(empty || !nextAvailable)
//        {
//            next = nullptr;
//        }
//    }
//    T* getFirst()
//    {
//        return first;
//    }
//    T* getLast()
//    {
//        return last;
//    }
//    T* get()
//    {
//        return curr;
//    }
//    T* getNext()
//    {
//        return next;
//    }
//    void setFirst(T* firstIn)
//    {
//        first = firstIn;
//    }
//    void setLast(T* lastIn)
//    {
//        last = lastIn;
//    }
//    void setCurr(T* currIn)
//    {
//        curr = currIn;
//        if(nextExists())
//        {
//            next = curr + 1;
//        }
//        else
//        {
//            next = nullptr;
//        }
//    }
//    bool nextExists()
//    {
//        return !(curr == last);
//    }
//    bool isEmpty()
//    {
//        return first == last;
//    }
//    bool atStart()
//    {
//        return first == curr;
//    }
//    bool atEnd()
//    {
//        return curr == last;
//    }
//    void operator++()
//    {
//       if (isEmpty())
//       {
//           cout << "CANNOT INCREMENT; ITERATOR IS EMPTY" << endl;
//       }
//       else if(atEnd())
//       {
//            curr = next;
//            next = nullptr;
//       }
//       else
//       {
//           curr = next;
//           next = next + 1;
//       }
//    }
//
//
//
//};
//#endif //INC_21F_PA02_DSITERATOR_H
