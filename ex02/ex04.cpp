#include <iostream>
#include <stdexcept>

using namespace std;

class Move
{
  protected:
    int source, sourcecoins, target, targetcoins;
  public:
    Move(int sh, int sc, int th, int tc): source(sh), sourcecoins(sc), target(th), targetcoins(tc){}

    int getSource() const
    {
      return source;
    }

    int getSourceCoins() const
    {
      return sourcecoins;
    }

    int getTarget() const
    {
      return target;
    }

    int getTargetCoins() const
    {
      return targetcoins;
    }

    friend ostream & operator << (ostream &out, const Move &move)
    {
      out << "takes " << move.sourcecoins << " coins from heap " << move.source << " and puts ";
      if(move.targetcoins==0)
        out << "nothing";
      else
        out << move.targetcoins << " coins to heap " << move.target;
      return out;
    }
};

class State
{
  private:
    int heapnum;
    int *p;
  public:
    State(int h, const int c[])
    {
      heapnum = h;
      p = new int[heapnum];
      for (int i = 0; i < heapnum; i++)
      {
        p[i] = i;
        p[i] = c[i];
      }
    }

~State()
    {
      delete [] p;
    }

    void next(const Move &move) throw(logic_error)
    {
      if (move.getTarget()>=heapnum || move.getSource()<0 || move.getSource()>=heapnum || move.getTarget()<0)
        throw logic_error("invalid heap");
      else if(move.getSourceCoins()>p[move.getSource()] or move.getSourceCoins()<1 or move.getTargetCoins()>=move.getSourceCoins() or move.getTargetCoins()<0)
        throw logic_error("invalid action");
      else
      {
        p[move.getSource()] -= move.getSourceCoins();
        p[move.getTarget()] += move.getTargetCoins();
      }
    }

    bool winning() const
    {
      for(int i = 0; i < heapnum; i++)
      {
        if(p[i]!=0) return false;
      }
      return true;
    }

    int getHeaps() const
    {
      return heapnum;
    }
    int getCoins(int h) const throw(logic_error)
    {
      int heapcur = h;
      if(heapcur<0 || heapcur >= heapnum) throw logic_error("invalid heap");
      return p[heapcur];
    }

    friend ostream & operator << (ostream &out, const State &state)
    {
      for (int i = 0; i < state.heapnum-1; i++)
      {
        out << state.p[i] << ", ";
      }
      out << state.p[state.heapnum-1];
      return out;
    }
};
