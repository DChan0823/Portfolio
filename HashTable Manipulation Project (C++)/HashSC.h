// File HashSC.h
// Template definitions for HashSC.
// Separate Chaining Hash Table
#ifndef HASHSC_H
#define HASHSC_H
#include "List.h"
#include "HashTable.h"
#include <cmath>
#include <iomanip>
using namespace std;

// ---------------------- HashSC Prototype --------------------------
template <class Object>
class HashSC : public HashTable <Object>
{
   static const int INIT_TABLE_SIZE = 97;
   static const float INIT_MAX_LAMBDA;
private:
   List<Object> * mLists; // for array of linked lists
   int mSize;  // number of entries
   int mTableSize; // array size
   float mMaxLambda; // max. load factor
   static int numCollisions;
   static int longestList;

public:
	HashSC(int (hCCode)(const Object &pcolor), int (comp)(const Object &left, const Object &right), int tableSize = INIT_TABLE_SIZE);
   ~HashSC();
   bool contains(const Object & x) const;
   void makeEmpty();
   bool insert(const Object & x);
   bool remove(const Object & x);
   static long nextPrime(long n);
   int size() const { return mSize; }
   bool setMaxLambda( float lm );
   void displayStatistics() const;
   bool getEntry(const Object & target, Object & returnedItem) const;
   void displayHashTable(ostream &out) const;
   void displayHashTable() const;

private:
   void rehash();
   int myHash(const Object & x) const;
};

template <class Object>
const float HashSC<Object>::INIT_MAX_LAMBDA = 1.5;

template <class Object>
int HashSC<Object>::numCollisions = 0;

template <class Object>
int HashSC<Object>::longestList = 0;

// HashSC method definitions -------------------
template <class Object>
HashSC<Object>::HashSC(int (hCCode)(const Object &pcolor), int (comp)(const Object &left, const Object &right), int tableSize)
	: mSize(0), HashTable(hCCode, comp)
{
   if (tableSize < INIT_TABLE_SIZE)
      mTableSize = INIT_TABLE_SIZE;
   else
      mTableSize = nextPrime(tableSize);

   mLists = new List<Object>[mTableSize];
   mMaxLambda = INIT_MAX_LAMBDA;
}

template <class Object>
HashSC<Object>::~HashSC()
{
//    for( int i=0; i < mTableSize; ++i )//FIXED******************
//        delete mLists[i];//FIXED******************
    delete [] mLists;
}

template <class Object>
int HashSC<Object>::myHash(const Object & x) const
{
   int hashVal;

   hashVal = this->Hash(x) % mTableSize;
   if(hashVal < 0)
      hashVal += mTableSize;

   return hashVal;
}

template <class Object>
void HashSC<Object>::makeEmpty()
{
   int k;

   for(k = 0; k < mTableSize; k++)
      mLists[k].clear();
   mSize = 0;
}

template <class Object>
bool HashSC<Object>::contains(const Object & x) const
{
   const List<Object> & theList = mLists[myHash(x)];
   Object tempObj;					// ADDED**********************

   for (int i=0; i < theList.size() ; i++)
   {
	  theList.getEntry((i+1), tempObj);//FIXED******************
	  if (this->Compare(tempObj, x) == 0)		//FIXED******************
         return true;
   }

   // not found
   return false;
}

template <class Object>
bool HashSC<Object>::remove(const Object & x)
{
   List<Object> &theList = mLists[myHash(x)];
   Object tempObj;					// ADDED**********************

  for (int i=0; i < theList.size() ; i++)
  {
	  theList.getEntry((i+1), tempObj);//FIXED******************
      if (/*tempObj==x*/ Compare(tempObj, x) == 0 )		//FIXED******************
      {
         theList.remove(i+1);
         mSize--;
         return true;
      }
  }
   // not found
   return false;
}

template <class Object>
bool HashSC<Object>::insert(const Object & x)
{
   List<Object> &theList = mLists[myHash(x)];
   int listSize= theList.size();
   Object tempObj;					// ADDED**********************

  for (int i=0; i < listSize ; i++)
  {
	  theList.getEntry((i+1), tempObj);//FIXED******************
	  if (Compare(tempObj, x) == 0)		//FIXED******************
         return false;
  }

  if (theList.size() > 0)
  {
	  numCollisions++;
  }

   // not found so we insert at the beginning
   theList.insert(x);
   //cout << "Inserted: "; // << x.write(cout);

   if (longestList < theList.size())
   {
	   longestList = theList.size();
   }

   // check load factor
   if( ++mSize > mMaxLambda * mTableSize )
      rehash();

   return true;
}

template <class Object>
bool HashSC<Object>::getEntry(const Object & target, Object & returnedItem) const
{
	// FINISH THIS (should be like remove, but assign to returnedItem if found)
	List<Object> &theList = mLists[myHash(target)];
	Object tempObj;

	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);
		if (this->Compare(tempObj, target) == 0)		// CHANGE TO USE this->Compare function
		{
			returnedItem = tempObj;
			return true;
		}
	}
	// not found
	return false;
}

template <class Object>
void HashSC<Object>::rehash()
{
   List<Object> *oldLists = mLists;
   int k, oldTableSize = mTableSize;
   List<Object> *currList;           // CHANGED********************
   Object tempObj;

   mTableSize = nextPrime(2*oldTableSize);
   mLists = new List<Object>[mTableSize];

   mSize = 0;
   for(k = 0; k < oldTableSize; k++)
   {
       currList = &oldLists[k];
       for( int i=0; i < currList->size(); ++i )//updated***************
	   {
		   currList->getEntry((i+1), tempObj);//updated***************
           insert(tempObj);
	   }

   }
   delete [] oldLists;
}

template <class Object>
bool HashSC<Object>::setMaxLambda(float lam)
{
   if (lam < .1 || lam > 100)
      return false;
   mMaxLambda = lam;
   return true;
}

template <class Object>
long HashSC<Object>::nextPrime(long n)
{
   long k, candidate, loopLim;

   // loop doesn't work for 2 or 3
   if (n <= 2 )
      return 2;
   else if (n == 3)
      return 3;

   for (candidate = (n%2 == 0)? n+1 : n ; true ; candidate += 2)
   {
      // all primes > 3 are of the form 6k +/- 1
      loopLim = (long)( (sqrt((float)candidate) + 1)/6 );

      // we know it is odd.  check for divisibility by 3
      if (candidate%3 == 0)
         continue;

      // now we can check for divisibility of 6k +/- 1 up to sqrt
      for (k = 1; k <= loopLim; k++)
      {
         if (candidate % (6*k - 1) == 0)
            break;
         if (candidate % (6*k + 1) == 0)
            break;
      }
      if (k > loopLim)
         return candidate;
   }
}

template <class Object>
void HashSC<Object>::displayStatistics() const
{
	cout << "\n\nIn the Hash SC class:\n";
	cout << "Load factor = " << setprecision(6) << fixed << dec << (double)mSize / mTableSize << endl;
	cout << "Number of collisions = " << dec << numCollisions << endl;
	cout << "Longest Linked List = " << dec << longestList << endl << endl;
}

template <class Object>
void HashSC<Object>::displayHashTable() const
{
	cout << "Hash SC Contents\n";
	for (int i = 0; i < mTableSize; i++)
	{
		if (mLists[i].size() > 0)
		{
			List<Object> bList = mLists[i];
			Object tempObj;
			
			cout << "List #" << i << " : " << endl;
			for (int b = 0; b < bList.size(); b++)
			{
				bList.getEntry(b + 1, tempObj);
				
				tempObj->write(cout);
			}
		}
	}
}

template <class Object>
void HashSC<Object>::displayHashTable(ostream &out) const
{
	out << "Hash SC Contents\n";
	for (int i = 0; i < mTableSize; i++)
	{
		if (mLists[i].size() > 0)
		{
			List<Object> bList = mLists[i];
			Object tempObj;

			out << "List #" << i << " : " << endl;
			for (int b = 0; b < bList.size(); b++)
			{
				bList.getEntry(b + 1, tempObj);
				
				tempObj->write(out);
			}
		}
	}
}

// NOTE (A): Our LinkedList nor List classes have an iterator
//     but we could write our own (you could try), so that
//     the iterator would be a separate class that would
//     have a function to return if it hasMore() (bool) and
//     another function to return the next element in the list
// You will learn about C++ iterators in Adv. C++, but you don't
//     need that here.
#endif
