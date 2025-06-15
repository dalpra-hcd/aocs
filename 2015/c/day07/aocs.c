#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 18
#define MAX_WIRE_LEN 1024
#define MAX_NAME_LEN 8

enum op_t { OP_SET, OP_NOT, OP_AND, OP_OR, OP_LSHIFT, OP_RSHIFT };

struct operand_t {
  uint8_t is_const;
  char name[MAX_NAME_LEN];
};

struct inst_t {
  enum op_t op;
  struct operand_t lhs;
  struct operand_t rhs;
};

struct wire_t {
  char name[MAX_NAME_LEN];
  struct inst_t inst;
  uint8_t is_set;
  uint16_t res;
};

static struct wire_t wires[MAX_WIRE_LEN];
static uint16_t wire_cnt = 0;

static void set_operand(struct operand_t *op, const char *tok) {
  op->is_const = isdigit(tok[0]) ? 1 : 0;
  strncpy(op->name, tok, MAX_NAME_LEN - 1);
  op->name[MAX_NAME_LEN - 1] = '\0';
}

static uint16_t find_or_create(const char *name) {
  uint16_t i;
  for (i = 0; i < wire_cnt; ++i) {
    if (strcmp(wires[i].name, name) == 0) {
      return i;
    }
  }

  strncpy(wires[wire_cnt].name, name, MAX_NAME_LEN - 1);
  wires[wire_cnt].name[MAX_NAME_LEN - 1] = '\0';
  return wire_cnt++;
}

static struct wire_t *get_wire(const char *name) {
  uint16_t idx;
  idx = find_or_create(name);
  return &wires[idx];
}

static uint16_t eval(const char *name) {
  struct wire_t *w;
  uint16_t lhs, rhs;

  w = get_wire(name);
  if (w->is_set) {
    return w->res;
  }

  lhs = w->inst.lhs.is_const ? atoi(w->inst.lhs.name) : eval(w->inst.lhs.name);

  switch (w->inst.op) {
  case OP_SET:
    w->res = lhs;
    break;
  case OP_NOT:
    w->res = ~lhs;
    break;
  case OP_AND:
    rhs = eval(w->inst.rhs.name);
    w->res = lhs & rhs;
    break;
  case OP_OR:
    rhs = eval(w->inst.rhs.name);
    w->res = lhs | rhs;
    break;
  case OP_LSHIFT:
    rhs = atoi(w->inst.rhs.name);
    w->res = lhs << rhs;
    break;
  case OP_RSHIFT:
    rhs = atoi(w->inst.rhs.name);
    w->res = lhs >> rhs;
    break;
  }

  w->is_set = 1;
  return w->res;
}

static void parse_line(char *line) {
  struct wire_t *w;
  char *tokens[5], *tok;
  uint16_t tok_cnt;

  tok_cnt = 0;
  tok = strtok(line, " ");
  while (tok) {
    tokens[tok_cnt++] = tok;
    tok = strtok(NULL, " ");
  }

  if (tok_cnt == 3) {
    /* format: lhs -> w */
    w = get_wire(tokens[2]);
    w->inst.op = OP_SET;
    set_operand(&w->inst.lhs, tokens[0]);
    w->inst.rhs.name[0] = '\0';
  } else if (tok_cnt == 4) {
    /* format: NOT lhs -> w */
    w = get_wire(tokens[3]);
    w->inst.op = OP_NOT;
    set_operand(&w->inst.lhs, tokens[1]);
    w->inst.rhs.name[0] = '\0';
  } else if (tok_cnt == 5) {
    /* format: lhs op rhs -> w */
    w = get_wire(tokens[4]);
    set_operand(&w->inst.lhs, tokens[0]);
    set_operand(&w->inst.rhs, tokens[2]);
    if (strcmp(tokens[1], "AND") == 0) {
      w->inst.op = OP_AND;
    } else if (strcmp(tokens[1], "OR") == 0) {
      w->inst.op = OP_OR;
    } else if (strcmp(tokens[1], "LSHIFT") == 0) {
      w->inst.op = OP_LSHIFT;
    } else if (strcmp(tokens[1], "RSHIFT") == 0) {
      w->inst.op = OP_RSHIFT;
    } else {
      fprintf(stderr, "Unknown operation: %s\n", tokens[1]);
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr, "Invalid line format: %s\n", line);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  char line[MAX_LINE_LEN + 2];
  struct wire_t *wb;
  uint16_t i, a;

  while (fgets(line, sizeof(line), stdin)) {
    line[strcspn(line, "\r\n")] = '\0';
    if (line[0] != '\0') {
      parse_line(line);
    }
  }

  a = eval("a");

  for (i = 0; i < wire_cnt; ++i) {
    wires[i].is_set = 0;
    wires[i].res = 0;
  }

  wb = get_wire("b");
  wb->inst.op = OP_SET;
  wb->inst.lhs.is_const = 1;
  snprintf(wb->inst.lhs.name, MAX_NAME_LEN, "%u", a);
  wb->inst.rhs.name[0] = '\0';

  printf("%u\n", eval("a"));
  return 0;
}
