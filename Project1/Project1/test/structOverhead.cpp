#include <cstdlib>
#include <cstdio>

#define NPAGECHARS 3
#define NOFFSETCHARS 2


/*******************************************************************************

   The purpose of this file is to provide evidence that the size of the pointer
     struct is simply the sum of the sizes of the arrays within it.

 ******************************************************************************/
struct pointer{
  char page[NPAGECHARS];
  char offset[NOFFSETCHARS];
};

int main(int argc, char **argv){
  pointer testStruct;
  printf("%d\n", sizeof(testStruct));
}
