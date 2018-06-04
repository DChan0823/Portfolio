// File HashQP.h
// Template definitions for HashQP.
// Quadratic Probing Hash Table
#ifndef HASHQP_H
#define HASHQP_H
#include <cmath>
#include <vector>
#include "HashTable.h"

using namespace std;

// ---------------------- HashQP Prototype --------------------------
template <class Object>
class HashQP : public HashTable <Object>
{
protected:
   static const int INIT_TABLE_SIZE = 97;
   static const float INIT_MAX_LAMBDA;

   enum ElementState { ACTIVE, EMPTY, DELETED };
   class HashEntry;

   vector<HashEntry> mArray;
   int mSize;
   int mLoadSize;
   int mTableSize;
   float mMaxLambda;
   static int numCollisions;
   static int longestCollision;

public:
   HashQP(int (hCCode)(const Object &pcolor), int (comp)(const Object &left, const Object &right), int tableSize = INIT_TABLE_SIZE);
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

protected:
   void rehash();
   int myHash(const Object & x) const;
   int findPos( const Object & x ) const;
};

template <class Object>
const float HashQP<Object>::INIT_MAX_LAMBDA = 0.49F;

template <class Object>
int HashQP<Object>::numCollisions = 0;

template <class Object>
int HashQP<Object>::longestCollision = 0;

// definition of nested HashQP<Object>::HashEntry class ----------------
template <class Object>
class HashQP<Object>::HashEntry
{
public:
   Object data;
   ElementState state;
   HashEntry( const Object & d = Object(), ElementState st = EMPTY )
      : data(d), state(st)
   { }
};

// HashQP method definitions -------------------
template <class Object>
HashQP<Object>::HashQP(int (hCCode)(const Object &pcolor), int (comp)(const Object &left, const Object &right), 
	int tableSize = INIT_TABLE_SIZE) : mSize(0), mLoadSize(0), HashTable(hCCode, comp)
{
   if (tableSize < INIT_TABLE_SIZE)
      mTableSize = INIT_TABLE_SIZE;
   else
      mTableSize = nextPrime(tableSize);
   mArray.resize(mTableSize);
   makeEmpty();
   mMaxLambda = INIT_MAX_LAMBDA;
}

template <class Object>
int HashQP<Object>::myHash(const Object & x) const
{
   int hashVal;

   hashVal = this->Hash(x) % mTableSize;
   if(hashVal < 0)
      hashVal += mTableSize;

   return hashVal;
}

template <class Object>
void HashQP<Object>::makeEmpty()
{
   int k, size = mArray.size();

   for (k = 0; k < size; k++)
   {
	   mArray[k].state = EMPTY;
	   delete mArray[k].data;
   }

   mSize = mLoadSize = 0;
}

template <class Object>
bool HashQP<Object>::contains(const Object & x) const
{
   return mArray[findPos(x)].state == ACTIVE;
}

template <class Object>
bool HashQP<Object>::remove(const Object & x)
{
   int bucket = findPos(x);

   if ( mArray[bucket].state != ACTIVE )
      return false;

   mArray[bucket].state = DELETED;
   mSize--;      // mLoadSize not dec'd because it counts any non-EMP location
   return true;
}

template <class Object>
bool HashQP<Object>::insert(const Object & x)
{
   int bucket = findPos(x);

   if (mArray[bucket].state == ACTIVE)
   {
	   
	   return false;
   }

   mArray[bucket].data = x;
   mArray[bucket].state = ACTIVE;
   mSize++;

   // check load factor
   if( ++mLoadSize > mMaxLambda * mTableSize )
      rehash();

   return true;
}
template <class Object>
int HashQP<Object>::findPos( const Object & x ) const
{
   int kthOddNum = 1;
   int index = myHash(x);
   int collisionPathCount = 0;

   while ( mArray[index].state != EMPTY
      && /*mArray[index].data != x*/ Compare(mArray[index].data, x) != 0 )
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if ( index >= mTableSize )
         index -= mTableSize;

	  collisionPathCount++;
   }

   numCollisions++;

   if (longestCollision > collisionPathCount)
   {
	   longestCollision = collisionPathCount;
   }

   return index;
}

template <class Object>
bool HashQP<Object>::getEntry(const Object & target, Object & returnedItem) const
{
	// FINISH THIS (should be like remove, but assign to returnedItem if found)

	int bucket = findPos(target);

	if (mArray[bucket].state != ACTIVE)
		return false;

		returnedItem = mArray[bucket].data;
		return true;
}

template <class Object>
void HashQP<Object>::rehash()
{
   vector<HashEntry> oldArray = mArray;
   int k, oldTableSize = mTableSize;

   mTableSize = nextPrime(2*oldTableSize);
   mArray.resize( mTableSize );
   for(k = 0; k < mTableSize; k++)
      mArray[k].state = EMPTY;

   mSize = mLoadSize = 0;
   for(k = 0; k < oldTableSize; k++)
      if (oldArray[k].state == ACTIVE)
         insert( oldArray[k].data );
}
template <class Object>
bool HashQP<Object>::setMaxLambda(float lam)
{
   if (lam < .1 || lam > .49)
      return false;
   mMaxLambda = lam;
   return true;
}

template <class Object>
long HashQP<Object>::nextPrime(long n)
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
void HashQP<Object>::displayStatistics() const
{
	cout << "\n\nIn the Hash Offset class:\n";
	cout << "Load factor = " << setprecision(6) << fixed << dec << (double)mSize / mTableSize << endl;
	cout << "Number of collisions = " << dec << numCollisions << endl;
	cout << "Longest Collision Path = " << dec << longestCollision << endl << endl;
}

template <class Object>
void HashQP<Object>::displayHashTable() const
{
	cout << "Hash QP Contents\n";
	HashEntry tempEntry;
	Object tempObj;

	if (mTableSize == 0)
	{
		return;
	}

	for (int i = 0; i < mTableSize; i++)
	{		
		//tempEntry = mArray[i].data;
		//tempObj = tempEntry.getItem(i + 1, tempObj);
		tempObj = mArray[i].data;

		cout << "Array #" << i << " : " << endl;

		tempObj->write(cout);
	}
}

template <class Object>
void HashQP<Object>::displayHashTable(ostream &out) const
{
	out << "Hash QP Contents\n";
	HashEntry tempEntry;
	Object tempObj;
	for (int i = 0; i < mTableSize; i++)
	{
		tempObj = mArray[i].data;

		out << "Array #" << i << " : " << endl;

		tempObj->write(out);
	}
}

#endif
