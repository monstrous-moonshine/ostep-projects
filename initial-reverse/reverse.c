#include <stdio.h>
#include <stdlib.h>

void *Malloc(size_t size) {
    void *out = malloc(size);
    if (!out) {
        fprintf(stderr, "reverse: malloc failed\n");
        exit(1);
    }
    return out;
}

FILE *Fopen(const char *name, const char *mode) {
    FILE *fp = fopen(name, mode);
    if (!fp) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", name);
        exit(1);
    }
    return fp;
}

typedef struct _node {
    char *line;
    struct _node *next;
} node;

typedef struct {
    node *head;
} list;

void insert(list *lst, char *line) {
    node *n = Malloc(sizeof *n);
    n->line = line;
    if (!lst->head) {
        n->next = NULL;
    } else {
        n->next = lst->head;
    }
    lst->head = n;
}

void printlist(list *lst, FILE *fp) {
    for (node *n = lst->head; n; n = n->next) {
        fputs(n->line, fp);
    }
}

void freelist(list *lst) {
    for (node *n = lst->head; n; ) {
        free(n->line);
        node *next = n->next;
        free(n);
        n = next;
    }
}

void reverse(FILE *in, FILE *out) {
    list lst = {};
    for (;;) {
        char *line = NULL;
        size_t n;
        ssize_t nr = getline(&line, &n, in);
        if (nr < 0) {
            free(line);
            break;
        } else {
            insert(&lst, line);
        }
    }
    printlist(&lst, out);
    freelist(&lst);
}

int main(int argc, char *argv[]) {
    FILE *in = stdin, *out = stdout;
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    if (argc > 1) {
        in = Fopen(argv[1], "r");
    }
    if (argc > 2) {
        out = Fopen(argv[2], "w");
    }

    reverse(in, out);

    if (argc > 1)
        fclose(in);
    if (argc > 2)
        fclose(out);
}
