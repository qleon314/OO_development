// Brian Malloy        Game Construction
#include "menumanager.h"

int main(int, char*[]) {
   bool reset = false;
   try {
      MenuManager menuManager;
      menuManager.play();
      while(reset) {
      	MenuManager menuManager;
         menuManager.play();
      }
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
