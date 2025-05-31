#include <stdio.h>

#define MAX_LINE_LEN 8
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(void) {
  char line[MAX_LINE_LEN + 1];
  int total;

  total = 0;
  while (fgets(line, sizeof(line), stdin) != NULL) {
    int l, w, h, s1, s2, s3, sm;

    if (sscanf(line, "%dx%dx%d", &l, &w, &h) != 3) {
      continue;
    }

    s1 = l * w;
    s2 = w * h;
    s3 = h * l;
    sm = MIN(s1, MIN(s2, s3));
    total += 2 * (s1 + s2 + s3) + sm;
  }

  printf("%d\n", total);
  return 0;
}