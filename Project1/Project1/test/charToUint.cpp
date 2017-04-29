#include <stdint.h>
#include <cstdio>

uint64_t charsToUint64(unsigned char *chars, char numChars){
  uint64_t uintVal = 0;
  for(int i = 0; i < numChars; i++){
    uintVal = uintVal | (chars[i] << ((numChars-(i+1))*8));
  }
  return uintVal;
}

int main(int argc, char **argv){
  // In binary: 00000001 00001010 11001010 : should equal 68298
  unsigned char charArray[3] = {1,10,202};
  uint64_t myInt = charsToUint64(charArray, 3);
  printf("%lu\n",myInt);
}
