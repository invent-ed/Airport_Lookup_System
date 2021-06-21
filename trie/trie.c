#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "trie.h"

struct trie_node *trie_make_node(const char letter) {
  struct trie_node *const new = malloc(sizeof *new);
  if (new == NULL) {
    // error
  }
  *new = (struct trie_node) {.letter = letter};
  return new;
}

struct trie_node *trie_level_get_tail(const struct trie_node *const level) {
  assert(level != NULL);
  const struct trie_node *trav = level;
  while (trav->next != NULL) {
    trav = trav->next;
  }
  return (struct trie_node *)trav;
}

void trie_level_append_node(const struct trie_node *const level, const struct trie_node *const node) {
  struct trie_node *const tail = trie_level_get_tail(level);
  tail->next = (struct trie_node *)node;
}

struct trie_node *trie_level_search(const struct trie_node *const level, const char letter) {
  const struct trie_node *trav = (struct trie_node *)level;
  while (trav != NULL && trav->letter != letter) {
    trav = trav->next;
  }
  return (struct trie_node *)trav;
}

struct trie_search_result trie_search(const struct trie *const trie, const char *str) {
  assert(trie != NULL);
  assert(str != NULL);
  struct trie_node *level = trie->root,
                         *curr = NULL,
                         *prev = NULL;
  for (char c = *str; c != '\0'; str++, c = *str) {
    prev = curr;
    curr = trie_level_search(level, c);
    if (curr != NULL) {
      level = curr->down;
    }
    else {
      break;
    }
  }
  return (struct trie_search_result){(char *)str, (struct trie_node *) curr != NULL ? curr : prev};
}

/* maybe recursive version
void trie_add_entry_r(struct trie_node *const node, const char *str, const void *const data) {
  if (*str == '\0') {
    node->data = (void *)data;
    return;
  }
  if (node->down != NULL && node->letter == *str) {
    trie_add_entry_r(node->down, str + 1, data);
  }
  else if (node->next != NULL) {
    trie_add_entry_r(node->next, str, data);
  }
  node->next = trie_make_node(*str);
  // idk! something like this!
}
*/

void trie_add_entry(struct trie *const trie, const char *str, const void *const data) {
  // TODO: make less ugly, adding a level should be its own function
  assert(trie != NULL);
  assert(str != NULL);
  // assert(data != NULL);
  struct trie_search_result search = trie_search(trie, str);
  str = search.rest;
  struct trie_node *node = search.last;
  if (*str == '\0') {
    return;
  }
  if (trie->root == NULL) {
    trie->root = trie_make_node(*str++);
    node = trie->root;
  }
  else if (node == NULL) {
    struct trie_node *root_level_tail = trie_level_get_tail(trie->root);
    root_level_tail->next = trie_make_node(*str++);
    node = root_level_tail->next;
  }
  else if (node->down != NULL) {
    // TODO: smarter level insertion
    node = trie_level_get_tail(node->down);
    node->next = trie_make_node(*str++);
    node = node->next;
  }
  for (char c = *str; c != '\0'; str++, c = *str) {
    node->down = trie_make_node(c);
    node = node->down;
  }
  node->data = (void *)data;
}

void trie_dealloc_nodes(struct trie_node **const node) {
  // TODO: make / dealloc trie itself, instead of root
  // curiously, const struct trie_node **const creates a type nightmare
  // dereferencing ^ gives struct trie_node *const *
  // the rules for double pointer const results are apparently tricky
  if ((*node)->down != NULL) {
    trie_dealloc_nodes(&(*node)->down);
  }
  if ((*node)->next != NULL) {
    trie_dealloc_nodes(&(*node)->next);
  }
  free(*node);
  *node = NULL;
}

struct trie_node *trie_bfs(const struct trie_node *const from) {
  if (from->data != NULL) {
    return (struct trie_node *)from;
  }
  if (from->next != NULL) {
    return trie_bfs(from->next);
  }
  if (from->down != NULL) {
    return trie_bfs(from->down);
  }
  return NULL; // reach this => ill formed trie
}
