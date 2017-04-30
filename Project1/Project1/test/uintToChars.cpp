#include <stdint.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

void uint64ToChars(uint64_t intVal, char numChars, unsigned char *outArray){
  // Cast int to char * so that we can iterate over bytes
  unsigned char *newVal = (unsigned char*) &intVal;
  // We have to copy in reverse order on little endian machines, not sure how
  //   this will be affected on big-endian.  May be problemeatic.
  for (int i = 0; i < numChars; i++){
    memset((&outArray[i]), newVal[numChars - (i+1)],1);
  }
}

int main(int argc, char **argv){
  char numChars = 3;
  unsigned char myChars[numChars];
  uint64_t myInt = 68298;
  uint64ToChars(myInt,numChars, myChars);
  for (int i = 0; i < numChars; i++){
    printf("%d\n", myChars[i]);
  }
}
