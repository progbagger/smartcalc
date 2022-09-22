#include "stack.h"

/**
 * @brief Allocate memory for stack
 *
 * @return Stack*
 */
Stack *init_stack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->top = NULL;
  s->returned = NULL;
  s->r_size = 0;
  return s;
}

/**
 * @brief Free memory of stack
 *
 * @param s Stack to free
 * @return Stack*
 */
Stack *destroy_stack(Stack *s) {
  if (s) {
    while (s->top) {
      struct node *elem = s->top;
      s->top = s->top->next;
      if (elem->data) free(elem->data);
      free(elem);
    }
    if (s->returned) {
      for (size_t i = 0; i < s->r_size; i++)
        if (s->returned[i]) free(s->returned[i]);
      free(s->returned);
    }
    free(s);
  }
  return NULL;
}

/**
 * @brief Check if stack is empty or not allocated
 *
 * @param s Stack to check for emptyness
 * @return int 1 if empty or not allocated; 0 otherwise
 */
int is_stack_empty(Stack *s) {
  int result = 1;
  if (s)
    if (s->top) result = 0;
  return result;
}

/**
 * @brief Push element into stack
 *
 * @param s Stack where to push element
 * @param value Value to push into stack
 * @param v_size Size of value
 */
void push_stack(Stack *s, void *value, size_t v_size) {
  struct node *elem = (struct node *)malloc(sizeof(struct node));
  void *data = malloc(v_size);
  for (size_t i = 0; i < v_size; i++)
    *((char *)data + i) = *((char *)value + i);
  elem->data = data;
  elem->next = s->top;
  s->top = elem;
}

/**
 * @brief Remove and return element from stack
 *
 * @param s Stack where to pop element
 * @return void* Element
 */
void *pop_stack(Stack *s) {
  struct node *elem = s->top;
  void *result = NULL;
  if (elem) {
    s->top = s->top->next;
    result = elem->data;
    free(elem);
    void **tmp = s->returned;
    s->returned = (void **)realloc(tmp, ++(s->r_size) * sizeof(void *));
    s->returned[s->r_size - 1] = result;
  }
  return result;
}

/**
 * @brief Get data from top of stack
 *
 * @param s Stack where to get data
 * @return void* Element
 */
void *top_stack(Stack *s) {
  void *result = NULL;
  if (s->top) result = s->top->data;
  return result;
}
