#include <stdio.h>

#define MAX_LINE_LEN 2

int main(void) {
  char line[MAX_LINE_LEN + 1];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    printf("%s\n", line);
  }

  return 0;
}