#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* wc -L input.in */
#define MAX_LINE_LEN 8192

typedef struct {
  int x, y;
} pos_t;

typedef struct {
  pos_t *lst;
  size_t len, cap;
} vec_t;

int main(void) {
  char line[MAX_LINE_LEN + 1];
  vec_t visited;
  pos_t santa;
  size_t idx, jdx;

  visited.cap = MAX_LINE_LEN;
  visited.len = 0;
  visited.lst = malloc(visited.cap * sizeof(pos_t));
  if (!visited.lst) {
    perror("malloc");
    exit(1);
  }

  santa.x = santa.y = 0;
  visited.lst[0].x = visited.lst[0].y = 0;
  visited.len = 1;

  while (fgets(line, sizeof(line), stdin)) {
    for (idx = 0; idx < strlen(line); idx++) {
      switch (line[idx]) {
      case '^':
        santa.y++;
        break;
      case 'v':
        santa.y--;
        break;
      case '>':
        santa.x++;
        break;
      case '<':
        santa.x--;
        break;
      default:
        continue;
      }

      for (jdx = 0; jdx < visited.len; jdx++) {
        if (visited.lst[jdx].x == santa.x && visited.lst[jdx].y == santa.y) {
          break;
        }
      }

      if (jdx < visited.len) {
        continue;
      }

      if (visited.len >= visited.cap) {
        visited.cap *= 2;
        visited.lst = realloc(visited.lst, visited.cap * sizeof(pos_t));
        if (!visited.lst) {
          perror("realloc");
          exit(1);
        }
      }

      visited.lst[visited.len].x = santa.x;
      visited.lst[visited.len].y = santa.y;
      visited.len++;
    }
  }

  printf("%ld\n", visited.len);
  free(visited.lst);
  return 0;
}