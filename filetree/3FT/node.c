/*--------------------------------------------------------------------*/
/* node.c                                                             */
/* Authors: Byron Zhang, Nicholas Padmanabhan, Christopher Moretti    */
/*--------------------------------------------------------------------*/

#include "node.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynarray.h"

/* A node structure represents a directory in the directory tree */
struct node {
    /* The full path of this Node */
    char* path;
    /* The parent directory of this directory NULL for the root of the
     * directory tree */
    Node parent;
    /* The subdirectories and files of this directory stored in sorted
     * order by pathname, with files appearing first */
    DynArray_T children;
    /* TRUE if node represents a file. FALSE if node represents a
     * directory */
    boolean isFile;
    /* Pointer to file's contents, relevant if isFile is TRUE */
    void* fileContents;
    /* Length of the file, relevant if isFile is TRUE. */
    size_t fileLength;
};

/* Returns a path with contents n->path/dir or NULL if there is an
   allocation error. Allocates memory for the returned string, which is
   then owned by the caller. */
static char* Node_buildPath(Node n, const char* dir) {
    char* path;

    assert(dir != NULL);

    if (n == NULL)
        path = malloc(strlen(dir) + 1);
    else
        path = malloc(strlen(Node_getPath(n)) + 1 + strlen(dir) + 1);

    if (path == NULL)
        return NULL;
    *path = '\0';

    if (n != NULL) {
        strcpy(path, Node_getPath(n));
        strcat(path, "/");
    }
    strcat(path, dir);

    return path;
}

/* Compares node1 and node2 based on their paths. Returns <0, 0, or >0
   if node1 is less than, equal to, or greater than node2, respectively.
   File paths are lexicographically less than directory paths. */
static int Node_compare(Node node1, Node node2) {
    assert(node1 != NULL);
    assert(node2 != NULL);

    /* if node1 is a file, node2 is not, node1 < node2 */
    if (Node_isFile(node1) && !Node_isFile(node2))
        return -1;

    /* if node2 is a file, node2 is not, node1 > nodes */
    if (!Node_isFile(node1) && Node_isFile(node2))
        return 1;

    /* if node1 and node2 are both files or directories, compare them
     * based on their paths */
    return strcmp(Node_getPath(node1), Node_getPath(node2));
}

/* Returns 1 if n has a child directory with path, 0 if it does not have
   such a child, and -1 if there is an allocation error during search.
   Note that n cannot be a file. If n does have such a child, and
   childID is not NULL, store the child's identifier in *childID. If n
   does not have such a child, store the identifier that such a child
   would have in *childID. */
static int Node_hasChild(Node n, const char* path, size_t* childID) {
    size_t index;
    int result;
    Node checker;

    assert(n != NULL);
    assert(!Node_isFile(n));
    assert(path != NULL);

    checker = Node_create(NULL, path, FALSE, NULL, 0);
    if (checker == NULL)
        return -1;

    result = DynArray_bsearch(
        n->children, checker, &index,
        (int (*)(const void*, const void*))Node_compare);

    (void)Node_destroy(checker);

    if (childID != NULL)
        *childID = index;
    return result;
}

/* see node.h for specification */
Node Node_create(Node parent, const char* dir, boolean isFile,
                 void* fileContents, size_t fileLength) {
    Node new;

    assert(dir != NULL);

    new = malloc(sizeof(struct node));
    if (new == NULL)
        return NULL;

    new->path = Node_buildPath(parent, dir);

    if (new->path == NULL) {
        free(new);
        return NULL;
    }

    new->parent = parent;
    new->isFile = isFile;

    if (isFile) {
        new->children = NULL;
        new->fileContents = fileContents;
        new->fileLength = fileLength;
    } else {
        new->children = DynArray_new(0);
        if (new->children == NULL) {
            free(new->path);
            free(new);
            return NULL;
        }
    }

    return new;
}

/* see node.h for specification */
size_t Node_destroy(Node n) {
    size_t i;
    size_t count = 0;
    Node c;

    assert(n != NULL);

    if (!(n->isFile)) {
        for (i = 0; i < DynArray_getLength(n->children); i++) {
            c = DynArray_get(n->children, i);
            count += Node_destroy(c);
        }
        DynArray_free(n->children);
    }

    free(n->path);
    free(n);
    count++;

    return count;
}

/* see node.h for specification */
const char* Node_getPath(Node n) {
    assert(n != NULL);
    return n->path;
}

/* see node.h for specification */
size_t Node_getNumChildren(Node n) {
    assert(n != NULL);
    assert(!(n->isFile));

    return DynArray_getLength(n->children);
}

/* see node.h for specification */
boolean Node_isFile(Node n) {
    assert(n != NULL);
    return n->isFile;
}

/* see node.h for specification */
Node Node_getChild(Node n, size_t childID) {
    assert(n != NULL);
    assert(!(n->isFile));

    if (DynArray_getLength(n->children) > childID)
        return DynArray_get(n->children, childID);
    else
        return NULL;
}

/* see node.h for specification */
Node Node_getParent(Node n) {
    assert(n != NULL);

    return n->parent;
}

/* see node.h for specification */
void* Node_getContents(Node n) {
    assert(n != NULL);
    assert(n->isFile);
    return n->fileContents;
}

/* see node.h for specification */
size_t Node_getLength(Node n) {
    assert(n != NULL);
    assert(n->isFile);
    return n->fileLength;
}

/* see node.h for specification */
void Node_setContents(Node n, void* fileContents, size_t fileLength) {
    assert(n != NULL);
    assert(n->isFile);
    n->fileContents = fileContents;
    n->fileLength = fileLength;
}

/* see node.h for specification */
int Node_linkChild(Node parent, Node child) {
    size_t i;
    char* rest;

    assert(parent != NULL);
    assert(child != NULL);
    assert(!(parent->isFile));

    /* Validates child's candidacy before adding to tree */
    if (Node_hasChild(parent, child->path, NULL))
        return ALREADY_IN_TREE;
    i = strlen(parent->path);
    if (strncmp(child->path, parent->path, i))
        return PARENT_CHILD_ERROR;
    rest = child->path + i;
    if (strlen(child->path) >= i && rest[0] != '/')
        return PARENT_CHILD_ERROR;
    rest++;
    if (strstr(rest, "/") != NULL)
        return PARENT_CHILD_ERROR;

    child->parent = parent;

    if (DynArray_bsearch(
            parent->children, child, &i,
            (int (*)(const void*, const void*))Node_compare) == 1)
        return ALREADY_IN_TREE;

    /* Adds the child to the parent's children array if possible */
    if (DynArray_addAt(parent->children, i, child) == TRUE)
        return SUCCESS;
    else
        return PARENT_CHILD_ERROR;
}

/* see node.h for specification */
int Node_unlinkChild(Node parent, Node child) {
    size_t i;

    assert(parent != NULL);
    assert(child != NULL);
    assert(!(parent->isFile));

    if (DynArray_bsearch(
            parent->children, child, &i,
            (int (*)(const void*, const void*))Node_compare) == 0)
        return PARENT_CHILD_ERROR;

    (void)DynArray_removeAt(parent->children, i);
    return SUCCESS;
}

/* see node.h for specification */
void Node_transformToFile(Node n, void* fileContents,
                          size_t fileLength) {
    assert(n != NULL);
    assert(!(n->isFile));

    DynArray_free(n->children);
    n->isFile = TRUE;
    n->fileContents = fileContents;
    n->fileLength = fileLength;
}

/* see node.h for specification */
char* Node_toString(Node n) {
    char* copyPath;

    assert(n != NULL);

    copyPath = malloc(strlen(n->path) + 1);
    if (copyPath == NULL)
        return NULL;
    else
        return strcpy(copyPath, n->path);
}
