#include "header.h"

#ifndef HEADER
#define HEADER
class M5ScreenBase{
    public:
   virtual void initScreen() = 0;
   virtual void deleteScreen() = 0;
   virtual void scereenUpdate() = 0;
};

#endif