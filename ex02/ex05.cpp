#include <iostream>
using namespace std;

class Player
{
  protected:
    string myname;
  public:
    Player(const string &n)
    {
      myname = n;
    }

    virtual ~Player()
    {
      myname.clear();
    }

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player)
    {
      out << player.getType() << " player " << player.myname;
      return out;
    }
};

class GreedyPlayer : public Player
{
  private :
    string type;
  public:
    GreedyPlayer(const string &n)
      : Player(n), type("Greedy"){}
    const string & getType() const override
    {
      return type;
    }

    Move play(const State &s) override
    {
      int max = 0;
      int thesi;
      for(int i = 0; i < s.getHeaps(); i++)
        if(s.getCoins(i) > max)
        {
          max = s.getCoins(i);
          thesi = i;
        }
      return Move(thesi, max, thesi, 0);
    }
};

class SpartanPlayer : public Player
{
  private:
    string type;
  public:
    SpartanPlayer(const string &n):
      Player(n), type("Spartan") {}
    const string &getType() const override
    {
      return type;
    }

    Move play(const State &s) override
    {
      int max = 0;
      int thesi = 0;
      for(int i = 0; i < s.getHeaps(); i++)
        if(s.getCoins(i)>max)
        {
          max = s.getCoins(i);
          thesi = i;
        }
      return Move(thesi, 1, thesi, 0);
    }
};

class SneakyPlayer : public Player
{
  private:
    string type;
  public:
    SneakyPlayer(const string &n):
      Player(n), type("Sneaky") {}
    const string &getType() const override
    {
      return type;
    }

    Move play(const State &s) override
    {
      int min, thesi;
      for(int i = 0; i < s.getHeaps(); i++)
        if(s.getCoins(i)!=0)
        {
          thesi = i;
          min = s.getCoins(i);
          break;
        }
      for(int i = 0; i < s.getHeaps(); i++)
      {
        if (s.getCoins(i) < min and s.getCoins(i)!=0)
        {
          min = s.getCoins(i);
          thesi = i;
        }
      }
      return Move(thesi, min, thesi, 0);
    }
};

class RighteousPlayer : public Player
{
  private:
    string type;
  public:
    RighteousPlayer(const string &n):
      Player(n), type("Righteous") {}
    const string &getType() const override
    {
      return type;
    }

    Move play(const State &s) override
    {
      int max = 0;
      int min = s.getCoins(0);
      int thesi_max;
      int thesi_min = 0;
      for(int i = 0; i < s.getHeaps(); i++)
      {
        if(s.getCoins(i)>max)
        {
          max = s.getCoins(i);
          thesi_max = i;
        }
        else if (s.getCoins(i) < min)
        {
          min = s.getCoins(i);
          thesi_min = i;
        }
    }
    return Move(thesi_max, max-(max/2), thesi_min, (max-(max/2))-1);
    }
};
