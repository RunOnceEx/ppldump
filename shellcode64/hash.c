#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long HashStringDjb2(const void *Input, unsigned long Length)
{
  const unsigned char *StringHash = (const unsigned char *)Input;
  unsigned long        HashString = 5138;

  while ( 1 ) {
    char CurrentCharacter = *StringHash;

    if (Length == 0) {
      if (*StringHash == 0)
          break;
      } else {
        if ((unsigned long)(StringHash - (const unsigned char *)Input) >= Length)
          break;
        if (*StringHash == 0) {
          ++StringHash; continue;
      };
    };

    if (CurrentCharacter >= 'a')
      CurrentCharacter -= 0x20;

    HashString  = ((HashString << 5) + HashString) + CurrentCharacter;

    ++StringHash;
  }
  return HashString;
};

int main(int argc, char *argv[]) {
  if ( argc < 2 ) {
    printf("usage: %s [string]\n", argv[0]);
    exit(0);
  };

  printf("Str: %s Hash: 0x%lx\n", argv[1],
    HashStringDjb2(argv[1], strlen(argv[1])));
};
