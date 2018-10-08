#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity){
   if(new_capacity<used) {
           new_capacity=used;
   }
   if(new_capacity < DEFAULT_CAPACITY)
           new_capacity = DEFAULT_CAPACITY;
   capacity = new_capacity;
   int * nArr = new int[capacity];
   for(int i=0;i<used;++i)
           nArr[i] = data[i];
   delete []data;
   data = nArr;
}

IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0){
   if(capacity < 1) capacity = DEFAULT_CAPACITY;
   data = new int[capacity];
}

IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used){
   data = new int[capacity];
   for(int i=0;i<used;++i){
        data[i] = src.data[i];
   }
}


IntSet::~IntSet(){delete []data;}

IntSet& IntSet::operator=(const IntSet& rhs){
    if(this != &rhs){
        int *nArr = new int[rhs.capacity];
        for(int i=0;i<rhs.used;++i){
            nArr[i]=rhs.data[i];
            }
        delete []data;
        used=rhs.used;
        capacity=rhs.capacity;
        data=nArr;
        }
   return *this;
}

int IntSet::size() const{return used;}

bool IntSet::isEmpty() const{return !size();}

bool IntSet::contains(int anInt) const{
   for(int i=0;i<used;++i){
           if(data[i]==anInt) return true;
   }
   return false; // dummy value returned
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const{
   for(int i=0;i<used;++i){
           if(!otherIntSet.contains(data[i])) return false;
   }
   return true; // dummy value returned
}

void IntSet::DumpData(ostream& out) const{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const{
   IntSet dummy = *this;
   for(int i=0;i<otherIntSet.size();++i){
       if(!contains(otherIntSet.data[i])) dummy.add(otherIntSet.data[i]);
   }
   return dummy; // dummy IntSet object returned
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const{
   IntSet dummy;
   dummy.reset();

   for(int i=0; i<size(); ++i){
       if(otherIntSet.contains(data[i])){
           dummy.add(data[i]);
       }
   }

  return dummy;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const{
   IntSet dummy = *this;
   for(int i=0;i<otherIntSet.size();++i){
       dummy.remove(otherIntSet.data[i]);
       }
   return dummy; // dummy IntSet object returned//
   return IntSet();
}

void IntSet::reset(){
        resize(0);
        used = 0;
}

bool IntSet::add(int anInt){
   if(contains(anInt)) return false;
   if(used + 1 > capacity) resize((capacity *1.5)+1);
   data[used++]=anInt;
   return true;
}

bool IntSet::remove(int anInt){
   if(contains(anInt)){
        int *nArr = new int[used];
        int j=0;
        for(int i=0;i<used;++i){
            if(data[i]!=anInt){
                nArr[j++]=data[i];
                }
           }
        used = j;
        delete []data;
        data=nArr;
        return true;
   }
   return false; // dummy value returned
}

bool operator==(const IntSet& is1, const IntSet& is2){
    if (is1.size()!=is2.size()) return false;

    IntSet dummy;
    dummy = is1.intersect(is2);
    if (dummy.size() == is1.size()) return true;
    return false; // dummy value returned
}

