#include "io.h"

namespace io{

void print(char* ptr){
  static uint8_t x=0, y=0;
  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  for(int i=0; ptr[i]!= '\0'; i++){
    if(ptr[i] == '\n'){
      y++;
      x=0;
    }
    else{
      VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ptr[i];
      x++;
    }

    if(x >= 80){
      y++;
      x = 0;
    }

    if(y >= 25){
      for(y=0; y<25; y++)
        for(x=0; x<80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

      x=0;
      y=0;
    }
  }
}

}
