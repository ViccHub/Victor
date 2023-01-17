#include "./client/client.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void set_up(){
  // we are printing unicode characters, so in windows we need to change pagination
  // to allow it.
  system("chcp 65001");
}
#else
void set_up(){}
#endif


int main(int argc, char const *argv[])
{
  set_up();
  Client c;

  char mode;
  bool invalid = true;
  while (invalid){
    cout << "Please input a game mode. (1,2,3)" << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs Machine" << endl;
    cout << "3. Machine vs Machine" << endl;
    cout << ">> ";
    cin >> mode;
    try
    {
      switch (mode)
      {
      case '1':
        c.play(playerPlay,playerPlay);
        invalid = false;
        break;
      case '2':
        c.play(playerPlay,pcPlay);
        invalid = false;
        break;
      case '3':
        c.play(pcPlay,pcPlay);
        invalid = false;
        break;
      default:
        cout << "Invalid choice, try again." << endl;
        break;
      }
    }
    catch(...)
    {
      invalid = false;
    }
    
    
  }
  cout << "Thanks for playing!" << endl;
  return 0;
}
