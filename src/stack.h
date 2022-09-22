#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief List element
 * 
 */
struct node {
  void *data;
  struct node *next;
};

/**
 * @brief Stack itself
 * 
 */
typedef struct {
  struct node *top;
  void **returned;
  size_t r_size;
} Stack;

// Working with stack
Stack *init_stack();
Stack *destroy_stack(Stack *s);
int is_stack_empty(Stack *s);

// Working with elements of stack
void push_stack(Stack *s, void *value, size_t v_size);
void *pop_stack(Stack *s);
void *top_stack(Stack *s);

#endif  // SRC_S21_STACK_H_
