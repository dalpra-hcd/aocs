#include <stdio.h>

#define MAX_LINE_LEN 7000

int main(void) {
  char line[MAX_LINE_LEN + 2];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    int i, floor;

    floor = 0;
    for (i = 0; line[i] != '\n' && line[i] != '\0'; ++i) {
      floor += line[i] == ')' ? -1 : 1;

      if (floor == -1) {
        printf("%d\n", i + 1);
        break;
      }
    }
  }

  return 0;
}