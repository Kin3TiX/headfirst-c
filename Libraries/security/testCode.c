#include <stdio.h>
#include <encrypt.h>
#include <checksum.h>

int main()
{
  char s[] = "Speak friend and enter";

  encrypt(s);
  printf("Encrypted string: %s\n", s);
  printf("Checksum: %i\n", checksum(s));

  encrypt(s);
  printf("Decrypted string: %s\n", s);
  printf("Checksum: %i\n", checksum(s));

  return 0;
  
}