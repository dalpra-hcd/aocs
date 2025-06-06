#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 32
#define MAX_GRID_SIZE 1000

enum Op { OP_INVALID, OP_ON, OP_OFF, OP_TOGGLE };

static enum Op parse_op(const char *line, int *x0, int *y0, int *x1, int *y1) {
  if (sscanf(line, "turn on %d,%d through %d,%d", x0, y0, x1, y1) == 4) {
    return OP_ON;
  }
  if (sscanf(line, "turn off %d,%d through %d,%d", x0, y0, x1, y1) == 4) {
    return OP_OFF;
  }
  if (sscanf(line, "toggle %d,%d through %d,%d", x0, y0, x1, y1) == 4) {
    return OP_TOGGLE;
  }
  return OP_INVALID;
}

static void apply_op(int grid[MAX_GRID_SIZE][MAX_GRID_SIZE], enum Op op, int x0,
                     int y0, int x1, int y1) {
  int x, y;

  for (y = y0; y <= y1; ++y) {
    for (x = x0; x <= x1; ++x) {
      switch (op) {
      case OP_ON:
        grid[y][x] += 1;
        break;
      case OP_OFF:
        if (grid[y][x] > 0) {
          grid[y][x] -= 1;
        }
        break;
      case OP_TOGGLE:
        grid[y][x] += 2;
        break;
      default:
        break;
      }
    }
  }
}

static void count(int grid[MAX_GRID_SIZE][MAX_GRID_SIZE]) {
  int x, y, cnt;

  cnt = 0;
  for (y = 0; y < MAX_GRID_SIZE; ++y) {
    for (x = 0; x < MAX_GRID_SIZE; ++x) {
      cnt += grid[y][x];
    }
  }

  printf("%d\n", cnt);
}

int main(void) {
  char line[MAX_LINE_LEN + 2];
  int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
  int x0, y0, x1, y1;
  enum Op op;

  memset(grid, 0, sizeof(grid));

  while (fgets(line, sizeof(line), stdin)) {
    line[strcspn(line, "\r\n")] = 0;

    op = parse_op(line, &x0, &y0, &x1, &y1);
    if (OP_INVALID != op) {
      apply_op(grid, op, x0, y0, x1, y1);
    }
  }

  count(grid);
  return 0;
}