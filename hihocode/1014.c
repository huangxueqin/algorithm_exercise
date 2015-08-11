#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie_node {
    char c;
    int count;
    struct trie_node *brother;
    struct trie_node *child;
};


struct trie_node *create_empty_trie() {
    struct trie_node *root = (struct trie_node *)malloc(sizeof(struct trie_node));
    memset(root, 0, sizeof(struct trie_node));
    return root;
}

struct trie_node *create_trie_node(char c) {
    struct trie_node *node = (struct trie_node *)malloc(sizeof(struct trie_node));
    memset(node, 0, sizeof(struct trie_node));
    node->c = c;
    node->count = 1;
    return node;
}

void add_string(struct trie_node *root, char *s) {
    char *p = s;
    struct trie_node *parent = root;
    while(*p) {
        struct trie_node *node = parent->child;
        while(node != NULL && node->c != *p) {
            node = node->brother;
        }
        if(node == NULL) {
            node = create_trie_node(*p);
            node->brother = parent->child;
            parent->child = node;
        }
        else {
            node->count++;
        }
        parent = node;
        p++;
    }
}

int search_string(struct trie_node *root, char *s) {
    char *p = s;
    struct trie_node *parent = root;
    while(*p && parent != NULL) {
        struct trie_node *node = parent->child;
        while(node != NULL && node->c != *p) {
            node = node->brother;
        }
        parent = node;
        if(node != NULL) {
            p++;
        }
    }
    return *p ? 0 : parent->count;
}

void free_trie(struct trie_node *root) {
    struct trie_node *node = root;
    if(node != NULL) {
        free_trie(node->brother);
        free_trie(node->child);
        free(node);
    }
}

struct trie_node *root;

int main(void) {
    char word[11];
    int i, n, m;
    root = create_empty_trie();
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%s", word);
        add_string(root, word);
    }
    scanf("%d", &m);
    for(i = 0; i < m; i++) {
        scanf("%s", word);
        printf("%d\n", search_string(root, word));
    }
    free_trie(root);
    return 0;
}
