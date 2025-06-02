#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 16

static int is_nice(const char *s) {
  size_t i;
  int vowels_cnt, has_double;

  vowels_cnt = has_double = 0;

  for (i = 0; s[i]; ++i) {
    if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
        s[i] == 'u') {
      ++vowels_cnt;
    }

    if (i > 0) {
      if (s[i - 1] == s[i]) {
        has_double = 1;
      }

      if ((s[i - 1] == 'a' && s[i] == 'b') ||
          (s[i - 1] == 'c' && s[i] == 'd') ||
          (s[i - 1] == 'p' && s[i] == 'q') ||
          (s[i - 1] == 'x' && s[i] == 'y')) {
        return 0;
      }
    }
  }

  return vowels_cnt >= 3 && has_double;
}

int main(void) {
  char line[MAX_LINE_LEN + 1];
  int nice_cnt;

  nice_cnt = 0;
  while (fgets(line, sizeof(line), stdin)) {
    if (is_nice(line)) {
      ++nice_cnt;
    }
  }

  printf("%d\n", nice_cnt);
  return 0;
}