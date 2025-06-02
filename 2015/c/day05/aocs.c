#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 16

static int is_nice(const char *s) {
  int has_pair, has_repeat;
  size_t i, j, len;

  has_pair = has_repeat = 0;
  len = strlen(s);

  for (i = 0; i + 1 < len; ++i) {
    for (j = i + 2; j + 1 < len; ++j) {
      if (s[i] == s[j] && s[i + 1] == s[j + 1]) {
        has_pair = 1;
        break;
      }
    }
    if (has_pair) {
      break;
    }
  }

  for (i = 2; i < len; ++i) {
    if (s[i - 2] == s[i]) {
      has_repeat = 1;
      break;
    }
  }

  return has_pair && has_repeat;
}

int main(void) {
  char line[MAX_LINE_LEN + 1];
  int nice_cnt;

  nice_cnt = 0;
  while (fgets(line, sizeof(line), stdin)) {
    line[strcspn(line, "\r\n")] = 0;

    if (is_nice(line)) {
      ++nice_cnt;
    }
  }

  printf("%d\n", nice_cnt);
  return 0;
}