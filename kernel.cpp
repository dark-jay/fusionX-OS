#include "libc/types.h"
#include "gdt.h"
#include "IO/io.h"


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++){
    (*i)();
  }
}

extern "C" void kMain(void* mutiboot_structure, uint32_t){
  io::print("Welcome to FusionX.\n");
  io::print("created by- Jay Nath, Arindom Bora and Subham Choudhury\n");

  io::print("\nInitializing Kernel-\nloading GDT...");
  init_gdt();
  io::print("  Done");

  while (1);
}
