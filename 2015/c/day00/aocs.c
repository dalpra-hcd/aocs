#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 2

int main(void) {
  char line[MAX_LINE_LEN + 2];

  while (fgets(line, sizeof(line), stdin)) {
    line[strcspn(line, "\r\n")] = 0;
    printf("%s\n", line);
  }

  return 0;
}