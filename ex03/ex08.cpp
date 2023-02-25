#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class ChessBoardArray
{
  protected:
    class Row
    {
      private:
        ChessBoardArray &myarray;
        int row;
      public:
        Row(ChessBoardArray &a, int i):
          myarray(a), row(i){}

        int & operator [] (int i) const
        {
          if(myarray.ifblack(row,i))
            throw out_of_range("invalid key");
          return myarray.select(row,i);
        }
    };

    class ConstRow
    {
      private:
        const ChessBoardArray &myarray;
        int row;
      public:
        ConstRow(const ChessBoardArray &a, int i):
          myarray(a),row(i){}
        int operator [] (int i) const
        {
          return myarray.select(row,i);
        }
    };
public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0)
    {
      arraysz = size;
      arraybase = base;
      if(arraysz%2==0)
      {
        data = new int[(arraysz*arraysz)/2];
        for(unsigned i = 0; i < arraysz*arraysz/2; i++)
          data[i] = 0;
      }
      else
      {
        data = new int[(arraysz*arraysz)/2+1];
        for (unsigned i = 0; i <(arraysz*arraysz)/2+1; i++)
          data[i] = 0;
      }
    }

    ChessBoardArray(const ChessBoardArray &a)
    {
      arraysz = a.arraysz;
      arraybase = a.arraybase;
      if(a.arraysz%2==0)
      {
        data = new int[(a.arraysz*a.arraysz)/2];
        for (unsigned i = 0; i < a.arraysz*a.arraysz/2; i++)
          data[i] = a.data[i];
      }
      else
      {
        data = new int[(a.arraysz*a.arraysz)/2+1];
        for(unsigned i = 0; i < (a.arraysz*a.arraysz)/2+1; i++)
          data[i] = a.data[i];
      }
    }
~ChessBoardArray()
    {
      delete []data;
    }

    ChessBoardArray & operator = (const ChessBoardArray &a)
    {
      delete []data;
      arraysz = a.arraysz;
      arraybase = a.arraybase;
      if(a.arraysz%2 == 0)
      {
        data = new int[(a.arraysz*a.arraysz)/2];
        for(unsigned i = 0; i < a.arraysz*a.arraysz/2; i++)
          data[i]=a.data[i];
      }
      else
      {
        data = new int[(a.arraysz*a.arraysz)/2+1];
        for(unsigned i = 0; i < (a.arraysz*a.arraysz)/2+1; i++)
          data[i] = a.data[i];
      }
      return *this;
    }

    int & select (int i, int j)
    {
      return data[loc(i,j)];
    }
    int select(int i, int j) const
    {
      return data[loc(i,j)];
    }

    const Row operator [] (int i)
    {
      return Row(*this,i);
    }
    const ConstRow operator [] (int i) const
    {
      return ConstRow(*this, i);
    }

    friend ostream & operator << (ostream &out, const ChessBoardArray &a);
private:
    unsigned arraysz;
    unsigned arraybase;
    int *data;
    bool ifblack(unsigned a, unsigned b) const
    {
      if((a-arraybase)%2 == 0)
      {
        for(unsigned i = arraybase; i <= arraybase+arraysz; i+=2)
          if(b==i+1)
            return true;
      }
      else if((a-arraybase)%2!=0)
      {
        for(unsigned i=arraybase; i <= arraybase+arraysz; i+=2)
          if(b==i)
            return true;
      }
      return false;
    }

    unsigned int loc(unsigned int i, unsigned int j) const throw(out_of_range)
    {
      unsigned k=i;
      unsigned l=j;
      if(i-arraybase<0 or i-arraybase>=arraysz or j-arraybase>=arraysz or j-arraybase<0 or ifblack(k,l))
        throw out_of_range("invalid");
      else
      {
        if(arraysz%2 == 0)
          return (i-arraybase)*(arraysz/2)+(j-arraybase)/2;
        else if(arraysz%2!=0)
        {
          if((i-arraybase)%2==0)
            return(i-arraybase)*(arraysz)/2+(j-arraybase)/2;
          else if((i-arraybase)%2!=0)
            return (i-arraybase)*(arraysz)/2+1+(j-arraybase)/2;
        }
      }
    }
};

ostream& operator << (ostream &out, const ChessBoardArray &a)
{
  for(unsigned i = a.arraybase; i < a.arraysz+a.arraybase; i++)
    for(unsigned j = a.arraybase; j < a.arraysz+a.arraybase; j++)
    {
      if (j==a.arraysz+a.arraybase-1)
      {
        if(a.ifblack(i,j))
          out << setw(4) << "0" << endl;
        else
          out << setw(4) << a.data[a.loc(i,j)] << endl;
      }
      else
        if(a.ifblack(i,j))
          out << setw(4) << "0";
        else
          out << setw(4) << a.data[a.loc(i,j)];
    }
  return out;
}
