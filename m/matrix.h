#ifndef _MATRIX_H
#define _MATRIX_H

#include "mlist.h"
#include <iostream>
using namespace std;


template <class itemType>
class matrix
{
  public:

  // constructors/destructor
    matrix( );                                      // default size 0 x 0
    matrix( int rows, int cols );                   // size rows x cols
    matrix( int rows, int cols,
            const itemType & fillValue );           // all entries == fillValue
    matrix( const matrix & mat );                   // copy constructor
    ~matrix( );                                     // destructor

  // assignment
    const matrix & operator = ( const matrix & rhs );

  // accessors
    int numRows( ) const;                             // number of rows
    int numCols( ) const;                             // number of columns

  // indexing
    const mlist<itemType> & operator [ ] ( int k ) const;  // range-checked indexing
    mlist<itemType> & operator [ ] ( int k );              // range-checked indexing

  // modifiers
    void resize( int newRows, int newCols );   // resizes matrix to newRows x newCols
                                               // (can result in losing values)
  private:

    int myRows;                             // # of rows (capacity)
    int myCols;                             // # of cols (capacity)
    mlist<mlist<itemType> > myMatrix; // the matrix of items
};


// *******************************************************************
// Specifications for matrix functions
//
// To use this class, itemType must satisfy the same constraints
// as formlist class.
//
// Any violation of a function's precondition will result in an error  message
// followed by a call to exit.
//
// constructors/destructor
//
//  matrix( );
//     postcondition: matrix of size 0x0 is constructed, and therefore
//                    will need to be resized later
//
//  matrix( int rows, int cols );
//     precondition: 0 <= rows and 0 <= cols
//     postcondition: matrix of size rows x cols is constructed
//
//  matrix( int rows, int cols, const itemType & fillValue );
//     precondition: 0 <= rows and 0 <= cols
//     postcondition: matrix of size rows x cols is constructed
//                    all entries are set by assignment to fillValue after
//                    default construction
//
//  matrix( const matrix<itemType> & mat );
//     postcondition: matrix is a copy of mat
//
//  ~matrix( );
//     postcondition: matrix is destroyed
//
// assignment
//
//  const matrix & operator = ( const matrix & rhs );
//     postcondition: normal assignment via copying has been performed
//                    (if matrix and rhs were different sizes, matrix has 
//                    been resized to match the size of rhs)
//
// accessors
//
//  int numRows( ) const;
//     postcondition: returns number of rows
//
//  int numCols( ) const;
//     postcondition: returns number of columns
//
// indexing
//
//  const mlist<itemType> & operator [ ] ( int k ) const;
//     precondition: 0 <= k < number of rows
//     postcondition: returns k-th row
//
//  mlist<itemType> & operator [ ] ( int k );
//     precondition: 0 <= k < number of rows
//     postcondition: returns k-th row
//
// modifiers
//
//  void resize( int newRows, int newCols );
//     precondition: matrix size is rows X cols,
//                   0 <= newRows and 0 <= newCols
//     postcondition: matrix size is newRows X newCols;
//                    for each 0 <= j <= min(rows,newRows) and
//                    for each 0 <= k <= min(cols,newCols), matrix[j][k] is
//                    a copy of the original; other elements of matrix are
//                    initialized using the default constructor for itemType
//                    Note: if newRows < rows or newCols < cols,
//                          elements may be lost
//
//  Examples of use:
//
//     matrix<double> dmat( 100, 80 );       // 100 x 80 matrix of doubles
//     matrix<double> dzmat( 100, 80, 0.0 ); // initialized to 0.0
//     matrix<apstring> smat( 300, 1 );      // 300 strings
//     matrix<int> imat;                     // has room for 0 ints

template <class itemType>
matrix<itemType>::matrix()
		  : myRows(0),
			 myCols(0),
			 myMatrix(0)

// postcondition: matrix of size 0x0 is constructed, and therefore
//                will need to be resized later
{

}
template <class itemType>
matrix<itemType>::matrix(int rows,int cols)
		  : myRows(rows),
			 myCols(cols),
			 myMatrix(rows)
     
// precondition: 0 <= rows and 0 <= cols
// postcondition: matrix of size rows x cols is constructed
{
    int k;
    for(k=0; k < rows; k++)
    {
        myMatrix[k].resize(cols);
    }
}

template <class itemType>
matrix<itemType>::matrix(int rows, int cols, const itemType & fillValue)
        : myRows(rows),
          myCols(cols),
          myMatrix(rows)
     
// precondition: 0 <= rows and 0 <= cols
// postcondition: matrix of size rows x cols is constructed
//                all entries are set by assignment to fillValue after
//                default construction
//     
{
    int j,k;
    for(j=0; j < rows; j++)
    {
        myMatrix[j].resize(cols);
        for(k=0; k < cols; k++)
        {
            myMatrix[j][k] = fillValue;
        }
    }
}

template <class itemType>
matrix<itemType>::matrix(const matrix<itemType> & mat)
    : myRows(mat.myRows),
      myCols(mat.myCols),
      myMatrix(mat.myRows)
     
// postcondition: matrix is a copy of mat
{
    int k;
    // copy elements
    for(k = 0; k < myRows; k++)
    {
        // cast to avoid const problems (const -> non-const)
        myMatrix[k] = (mlist<itemType> &) mat.myMatrix[k];
    }   
}

template <class itemType>
matrix<itemType>::~matrix ()
// postcondition: matrix is destroyed
{
    // mlist destructor frees everything
}

template <class itemType>
const matrix<itemType> &
matrix<itemType>::operator = (const matrix<itemType> & rhs)
// postcondition: normal assignment via copying has been performed
//                (if matrix and rhs were different sizes, matrix has 
//                been resized to match the size of rhs)     
{
    if (this != &rhs)                    // don't assign to self!
    {
        myMatrix.resize(rhs.myRows);     // resize to proper # of rows
        myRows = rhs.myRows;             // set dimensions
        myCols = rhs.myCols;
        
        // copy rhs
        int k;
        for(k=0; k < myRows; k++)
        {
	    myMatrix[k] = rhs.myMatrix[k];
        }
    }
    return *this;       
}

template <class itemType>
int matrix<itemType>::numRows() const
// postcondition: returns number of rows
{
    return myRows;
}

template <class itemType>
int matrix<itemType>::numCols() const
// postcondition: returns number of columns
{
    return myCols;
}


template <class itemType>
void matrix<itemType>::resize(int newRows, int newCols)
// precondition: matrix size is rows X cols,
//               0 <= newRows and 0 <= newCols
// postcondition: matrix size is newRows X newCols;
//                for each 0 <= j <= min(rows,newRows) and
//                for each 0 <= k <= min(cols,newCols), matrix[j][k] is
//                a copy of the original; other elements of matrix are
//                initialized using the default constructor for itemType
//                Note: if newRows < rows or newCols < cols,
//                      elements may be lost
//
{
    int k;
    myMatrix.resize(newRows);

    for(k=0; k < newRows; k++)
    {
        myMatrix[k].resize(newCols);
    }
    myRows = newRows;
    myCols = newCols;
}

template <class itemType>
const mlist<itemType> &
matrix<itemType>::operator [] (int k) const
// precondition: 0 <= k < number of rows
// postcondition: returns k-th row
{
	 if (k < 0 || myRows <= k)
	 {
		  cerr << "Illegal matrix index: " << k << " max index = ";
		  cerr << (myRows-1) << endl;
		  exit(1);
	 }
	 return myMatrix[k];
}

template <class itemType>
mlist<itemType> &
matrix<itemType>::operator [] (int k)
// precondition: 0 <= k < number of rows
// postcondition: returns k-th row
{
	 if (k < 0 || myRows <= k)
	 {
		  cerr << "Illegal matrix index: " << k << " max index = ";
		  cerr << (myRows-1) << endl;
        exit(1);
    }    
    return myMatrix[k];
}
#endif


