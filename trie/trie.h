#ifndef __TRIE_H_
#define __TRIE_H_

struct trie_search_result {
  char *rest;
  struct trie_node *last;
};

struct trie_node {
  char letter;
  struct trie_node *next;
  struct trie_node *down;
  void *data;
};

struct trie { struct trie_node *root; };

void trie_add_entry(struct trie *const trie, const char *str, const void *const data);
struct trie_search_result trie_search(const struct trie *const trie, const char *str);
struct trie_node *trie_level_search(const struct trie_node *const level, const char letter);
void trie_level_append_node(const struct trie_node *const level, struct trie_node const *const node);
struct trie_node *trie_level_get_tail(const struct trie_node *const level);
struct trie_node *trie_make_node(const char letter);
void trie_dealloc_nodes(struct trie_node **const node);
struct trie_node *trie_bfs(const struct trie_node *const from);

#endif // __TRIE_H_
