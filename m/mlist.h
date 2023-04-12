
#ifndef _MLIST_H
#define _MLIST_H
#define explicit
#include <iostream>
using namespace std;

template <class itemType>
class mlist
{
  public:

  // constructors/destructor
	 mlist( );                        // default constructor (size==0)
	 explicit mlist( int size );      // initial size of mlist is size
	 mlist( int size, const itemType & fillValue ); // all entries == fillValue
	 mlist( const mlist & vec );   // copy constructor
	 ~mlist( );                       // destructor

  // assignment
    const mlist & operator = ( const mlist & vec );

  // accessors
    int  size( ) const;                   // capacity of mlist

  // indexing
    itemType &       operator [ ] ( int index );       // indexing with range checking
    const itemType & operator [ ] ( int index ) const; // indexing with range checking

  // modifiers
    void resize( int newSize );             // change size dynamically;
                                            // can result in losing values
  private:

    int  mySize;                            // # elements in array
    itemType * myList;                      // array used for storage
};

// *******************************************************************
//  Specifications for mlist functions
//
//  The template parameter itemType must satisfy the following two conditions:
//   (1) itemType has a 0-argument constructor
//   (2) operator = is defined for itemType
//  Any violation of these conditions may result in compilation failure.
//
//  Any violation of a function's precondition will result in an error message
//  followed by a call to exit.
//
//  constructors/destructor
//
//   mlist( )
//     postcondition: mlist has a capacity of 0 items, and therefore it will
//                    need to be resized
//
//   mlist( int size )
//     precondition: size >= 0
//     postcondition: mlist has a capacity of size items
//
//   mlist( int size, const itemType & fillValue )
//     precondition: size >= 0
//     postcondition: mlist has a capacity of size items, all of which are set
//                    by assignment to fillValue after default construction
//
//   mlist( const mlist & vec )
//     postcondition: mlist is a copy of vec
//
//   ~mlist( )
//     postcondition: mlist is destroyed
//
//  assignment
//
//   const mlist & operator = ( const mlist & rhs )
//     postcondition: normal assignment via copying has been performed;
//                    if mlist and rhs were different sizes, mlist
//                    has been resized to  match the size of rhs
//
//  accessor
//
//   int  size( ) const
//     postcondition: returns mlist's size (number of memory cells
//                    allocated for mlist)
//
//  indexing
//
//   itemType &       operator [ ] ( int k )       -- index into nonconst mlist
//   const itemType & operator [ ] ( int k ) const -- index into const mlist
//     description: range-checked indexing, returning kth item
//     precondition: 0 <= k < size()
//     postcondition: returns the kth item
//
//  modifier
//
//   void resize( int newSize )
//     description:  resizes the mlist to newSize elements
//     precondition: the current capacity of mlist is size; newSize >= 0
//
//     postcondition: the current capacity of mlist is newSize; for each k
//                    such that 0 <= k <= min(size, newSize), mlist[k]
//                    is a copy of the original; other elements of mlist are
//                    initialized using the 0-argument itemType constructor
//                    Note: if newSize < size, elements may be lost
//
//  examples of use
//      mlist<int> v1;         // 0-element mlist
//      mlist<int> v2(4);      // 4-element mlist
//      mlist<int> v3(4, 22);  // 4-element mlist, all elements == 22.

template <class itemType>
mlist<itemType>::mlist()
//postcondition: mlist has a capacity of 0 items, and therefore it will
//               need to be resized
    : mySize(0),
      myList(0)
{

}

template <class itemType>
mlist<itemType>::mlist(int size)
// precondition: size >= 0
// postcondition: mlist has a capacity of size items
   : mySize(size),
     myList(new itemType[size])
{

}

template <class itemType>
mlist<itemType>::mlist(int size, const itemType & fillValue)
// precondition: size >= 0
// postcondition: mlist has a capacity of size items, all of which are set
//                by assignment to fillValue after default construction
    : mySize(size),
      myList(new itemType[size])
{
    int k;
    for(k = 0; k < size; k++)
    {
        myList[k] = fillValue;
    }
}

template <class itemType>
mlist<itemType>::mlist(const mlist<itemType> & vec)
// postcondition: mlist is a copy of vec
    : mySize(vec.size()),
      myList(new itemType[mySize])
{
    int k;
        // copy elements
    for(k = 0; k < mySize; k++){
        myList[k] = vec.myList[k];
    }
}

template <class itemType>
mlist<itemType>::~mlist ()
// postcondition: mlist is destroyed
{
    delete [] myList;
}

template <class itemType>
const mlist<itemType> &
mlist<itemType>::operator = (const mlist<itemType> & rhs)
// postcondition: normal assignment via copying has been performed;
//                if mlist and rhs were different sizes, mlist
//                has been resized to  match the size of rhs
{
    if (this != &rhs)                           // don't assign to self!
    {
        delete [] myList;                       // get rid of old storage
        mySize = rhs.size();
        myList = new itemType [mySize];         // allocate new storage

            // copy rhs
        int k;
        for(k=0; k < mySize; k++)
        {
            myList[k] = rhs.myList[k];
        }
    }
    return *this;                               // permit a = b = c = d
}

template <class itemType>
int mlist<itemType>::size() const
// postcondition: returns mlist's size (number of memory cells
//                allocated for mlist)
{
    return mySize;
}

template <class itemType>
itemType & mlist<itemType>::operator [] (int k)
// description: range-checked indexing, returning kth item
// precondition: 0 <= k < size()
// postcondition: returns the kth item
{

    if (k < 0 || mySize <= k)
    {
        cout << "Illegal mlist index: " << k << " max index = ";
        cout << (mySize-1) << endl;
        exit(1);
    }
    return myList[k];
}

template <class itemType>
const itemType & mlist<itemType>::operator [] (int k) const
// safe indexing, returning const reference to avoid modification
// precondition: 0 <= index < size
// postcondition: return index-th item
// exception: aborts if index is out-of-bounds
{
    if (k < 0 || mySize <= k)
    {
        cerr << "Illegal mlist index: " << k << " max index = ";
        cerr << (mySize-1) << endl;
        exit(1);
    }
	 return myList[k];
}

template <class itemType>
void mlist<itemType>::resize(int newSize)
// description:  resizes the mlist to newSize elements
// precondition: the current capacity of mlist is size(); newSize >= 0
// postcondition: the current capacity of mlist is newSize; for each k
//                such that 0 <= k <= min(size, newSize), mlist[k]
//                is a copy of the original; other elements of mlist are
//                initialized using the 0-argument itemType constructor
//                Note: if newSize < size, elements may be lost
{
    int k;
    int numToCopy = newSize < mySize ? newSize : mySize;

         // allocate new storage and copy element into new storage

    itemType * newList = new itemType[newSize];
    for(k=0; k < numToCopy; k++)
    {
        newList[k] = myList[k];
    }
    delete [] myList;                      // de-allocate old storage
    mySize = newSize;                      // assign new storage/size
    myList = newList;
}

#endif