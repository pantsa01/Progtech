class Game
{
  private:
    int gameHeaps, currentHeap;
    int coins;
    int gamePlayers, currentPlayer;
    int *allheaps;
    Player **allplayers;

  public:
    Game(int heaps, int players):
      gameHeaps(heaps), gamePlayers(players)
  {
    allheaps = new int[heaps];
    allplayers = new Player*[players];
    currentHeap = 0;
    currentPlayer = 0;
  }

    ~Game()
    {
      delete [] allheaps;
      delete [] allplayers;
    }

    void addHeap(int coins) throw(logic_error)
    {
      if(currentHeap>gameHeaps)
        throw logic_error("Every heap is full");
      else if(coins<0)
        throw logic_error("No coins");
      else
      {
        allheaps[currentHeap] = coins;
        currentHeap++;
      }
    }

    void addPlayer(Player *player) throw(logic_error)
    {
      if(currentPlayer>gamePlayers)
        throw logic_error("There are no other players");
      else
      {
        allplayers[currentPlayer] = player;
        currentPlayer++;
      }
    }

void play(ostream &out) throw(logic_error){
      try
      {
        State state(gameHeaps,allheaps);
        while(true)
        {
          for(int i=0; i<gamePlayers; i++)
          {
            out<< "State: " << state <<endl;
            Move move = allplayers[i]->play(state);
            out << *allplayers[i] << " " << move <<endl;
            state.next(move);
            if(state.winning())
            {
              out << "State: " << state <<endl;
              out << *allplayers[i]<< " wins" << endl;
              return;
            }
          }
        }
      }
      catch(logic_error &e)
      {
        cout << "Exception:" << e.what() << endl;
      }
    }
};
