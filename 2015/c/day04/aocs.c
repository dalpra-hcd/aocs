#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 8
#define MAX_BUF_LEN 64

int main(void) {
  char line[MAX_LINE_LEN + 1];
  char buf[MAX_BUF_LEN];
  unsigned char digest[MD5_DIGEST_LENGTH];
  size_t num, len;

  while (fgets(line, sizeof(line), stdin)) {
    num = 0;
    while (1) {
      len = snprintf(buf, sizeof(buf), "%s%ld", line, num);
      if (len >= sizeof(buf)) {
        fprintf(stderr, "buf too small");
        exit(1);
      }

      MD5((const unsigned char *)buf, len, digest);

      if ((digest[0] == 0x00 && digest[1] == 0x00 &&
           (digest[2] & 0xF0) == 0x00)) {
        printf("%ld\n", num);
        break;
      }

      num++;
    }
  }

  return 0;
}