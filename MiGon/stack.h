/* stack.h */
#ifndef STATCK_H
#define STATCK_H
#include "main.h" // provides definition for item_t
#include <stdio.h>

extern void push(item_t);
extern item_t pop(void);
extern int is_empty(void);

#endif
