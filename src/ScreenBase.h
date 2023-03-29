#include "header.h"

#ifndef SCREEN_BASE
#define SCREEN_BASE
class ScreenBase{
    public:
   virtual void initScreen(){};
   virtual void deleteScreen(){};
   virtual void scereenUpdate(){};
};

#endif