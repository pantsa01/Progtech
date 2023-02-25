#include <iostream>
using namespace std;

template <typename T>
class stack{
  private:
    int j;
    int megethos;
    T *myarray;

  public:

    stack (int size){
      j=0;
      megethos=size;
      myarray=new T[size];
    }

    stack (const stack &s){
      megethos=s.megethos;
      myarray=new T[megethos];
      for(int i=0; i<s.j; i++)
        myarray[i]=s.myarray[i];
      j = s.j;}

    const stack &operator = (const stack &s){
      delete []myarray;
      megethos=s.megethos;
      myarray=new T[megethos];
      for (int i=0; i<s.j; i++)
        myarray[i]=s.myarray[i];
      j=s.j;
      return *this;}

    ~stack(){
      delete []myarray;
    }

    bool empty(){
      if (j==0)
        return true;
      else
        return false;}

    void push(const T &x){
      myarray[j]=x;
      j++;}

    T pop(){
      T temp=myarray[j-1];
      j--;
      return temp;}

    int size(){
      return j;}
friend ostream &operator << (ostream &out, const stack &s){
      out << "[";
      for (int i=0; i<s.j; i++){
        if (i==(s.j-1))
          out<<s.myarray[i];
        else
          out<<s.myarray[i]<<","<<" ";
      }
      out<<"]";
      return out;
    }
};

#ifndef CONTEST
int main()
{
}
#endif
