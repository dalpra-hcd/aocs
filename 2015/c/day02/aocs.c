#include <stdio.h>

#define MAX_LINE_LEN 8
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  char line[MAX_LINE_LEN + 2];
  int total;

  total = 0;
  while (fgets(line, sizeof(line), stdin) != NULL) {
    int l, w, h, sm;

    if (sscanf(line, "%dx%dx%d", &l, &w, &h) != 3) {
      continue;
    }

    sm = MAX(l, MAX(w, h));
    total += 2 * (l + w + h - sm);
    total += l * w * h;
  }

  printf("%d\n", total);
  return 0;
}