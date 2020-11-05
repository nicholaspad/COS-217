/*--------------------------------------------------------------------*/
/* ft.c                                                               */
/* Authors: Byron Zhang, Nicholas Padmanabhan                         */
/*--------------------------------------------------------------------*/

#include "ft.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynarray.h"
#include "node.h"

/* A File Tree is an AO with 3 state variables: */
/* A flag for if it is in an initialized state (TRUE) or not (FALSE) */
static boolean isInitialized;
/* A pointer to the root directory in the hierarchy */
static Node root;
/* A counter of the number of directories and files in the hierarchy */
static size_t count;

/* Starting at the parameter curr, traverses as far down
   the hierarchy as possible while still matching the path
   parameter. Returns a pointer to the farthest matching Node down that
   path, or NULL if there is no node in curr's hierarchy that matches a
   prefix of the path. */
static Node FT_traversePathFrom(char *path, Node curr) {
    Node found;
    size_t i;

    assert(path != NULL);

    /* No path prefix match */
    if (curr == NULL)
        return NULL;

    /* Path match */
    else if (!strcmp(path, Node_getPath(curr)))
        return curr;

    /* Path prefix partial match */
    else if (!strncmp(path, Node_getPath(curr),
                      strlen(Node_getPath(curr)))) {
        if (!Node_isFile(curr)) {
            /* Search all directory children */
            for (i = 0; i < Node_getNumChildren(curr); i++) {
                found =
                    FT_traversePathFrom(path, Node_getChild(curr, i));
                if (found != NULL)
                    return found;
            }
        }

        return curr;
    }

    return NULL;
}

/* Returns the farthest Node reachable from the root following a
   given path, or NULL if there is no Node in the hierarchy that
   matches a prefix of the path. */
static void *FT_traversePath(char *path) {
    assert(path != NULL);
    return FT_traversePathFrom(path, root);
}

/* Given a prospective parent and child Node, adds child to parent's
   children list, if possible. If not possible, destroys the hierarchy
   rooted at child and returns PARENT_CHILD_ERROR, otherwise, returns
   SUCCESS. */
static int FT_linkParentToChild(Node parent, Node child) {
    assert(parent != NULL);

    if (Node_linkChild(parent, child) != SUCCESS) {
        (void)Node_destroy(child);
        return PARENT_CHILD_ERROR;
    }

    return SUCCESS;
}

/* Inserts a new path into the tree rooted at parent, or, if
   parent is NULL, as the root of the data structure. If isFile is TRUE,
   treat the last created Node as a file and set its contents to
   fileContents and its length to fileLength. Otherwise, ignore
   fileContents and fileLength. If a Node representing path already
   exists, returns ALREADY_IN_TREE. If there is an allocation error in
   creating any of the new nodes or their fields, returns MEMORY_ERROR.
   If there is an error linking any of the new nodes, returns
   PARENT_CHID_ERROR. Otherwise, returns SUCCESS. */
static int FT_insertRestOfPath(char *path, Node parent, boolean isFile,
                               void *fileContents, size_t fileLength) {
    Node curr = parent;
    Node firstNew = NULL;
    Node new;
    char *copyPath;
    char *restPath = path;
    char *dirToken;
    int result;
    size_t newCount = 0;

    assert(path != NULL);

    if (curr == NULL) {
        if (root != NULL) {
            /* Inserting a root while a root already exists is not
            allowed */
            return CONFLICTING_PATH;
        }
    } else {
        /* Path match means duplicate directory/file; not allowed */
        if (!strcmp(path, Node_getPath(curr)))
            return ALREADY_IN_TREE;
        restPath += (strlen(Node_getPath(curr)) + 1);
    }

    copyPath = malloc(strlen(restPath) + 1);
    if (copyPath == NULL)
        return MEMORY_ERROR;
    strcpy(copyPath, restPath);
    dirToken = strtok(copyPath, "/");

    /* Keep appending new directories until reaching end of path */
    while (dirToken != NULL) {
        new = Node_create(curr, dirToken, FALSE, NULL, 0);
        newCount++;

        /* Create a temporary hierarchy of Nodes containing part of the
           total path */
        if (firstNew == NULL)
            firstNew = new;
        else {
            result = FT_linkParentToChild(curr, new);
            if (result != SUCCESS) {
                (void)Node_destroy(new);
                (void)Node_destroy(firstNew);
                free(copyPath);
                return result;
            }
        }

        /* If memory allocation failed, destroy all Nodes already
           created */
        if (new == NULL) {
            (void)Node_destroy(firstNew);
            free(copyPath);
            return MEMORY_ERROR;
        }

        curr = new;
        dirToken = strtok(NULL, "/");
    }

    /* If the path passed refers to a file, transform the last
       appended directory to a file with provided fileContents
       and fileLength */
    if (isFile)
        Node_transformToFile(curr, fileContents, fileLength);

    free(copyPath);

    if (parent == NULL) {
        root = firstNew;
        count = newCount;
        return SUCCESS;
    }

    /* Link the new hierarchy to the existing tree */
    result = FT_linkParentToChild(parent, firstNew);
    if (result == SUCCESS)
        count += newCount;
    else
        (void)Node_destroy(firstNew);

    return result;
}

/* see ft.h for specification */
int FT_insertDir(char *path) {
    Node curr;
    int result;

    assert(path != NULL);

    if (!isInitialized)
        return INITIALIZATION_ERROR;

    if (root != NULL && Node_isFile(root))
        return CONFLICTING_PATH;

    curr = FT_traversePath(path);
    if (curr != NULL && Node_isFile(curr))
        return ALREADY_IN_TREE;

    result = FT_insertRestOfPath(path, curr, FALSE, NULL, 0);
    return result;
}

/* see ft.h for specification */
boolean FT_containsDir(char *path) {
    Node curr;
    boolean result;

    assert(path != NULL);

    if (!isInitialized)
        return FALSE;

    curr = FT_traversePath(path);

    if (curr == NULL)
        result = FALSE;
    else if (strcmp(path, Node_getPath(curr)))
        result = FALSE;
    else if (Node_isFile(curr))
        result = FALSE;
    else
        result = TRUE;

    return result;
}

/* Destroys the entire hierarchy of Nodes rooted at curr,
   including curr itself. */
static void FT_removePathFrom(Node curr) {
    if (curr != NULL) {
        count -= Node_destroy(curr);
    }
}

/* Removes the directory hierarchy rooted at path starting from Node
   curr. If curr is the data structure's root, root becomes NULL.
   Returns NO_SUCH_PATH if curr is not the Node for path, and SUCCESS
   otherwise. */
static int FT_rmPathAt(char *path, Node curr) {
    Node parent;

    assert(path != NULL);
    assert(curr != NULL);

    parent = Node_getParent(curr);

    if (!strcmp(path, Node_getPath(curr))) {
        if (parent == NULL)
            root = NULL;
        else
            Node_unlinkChild(parent, curr);

        FT_removePathFrom(curr);

        return SUCCESS;
    }

    return NO_SUCH_PATH;
}

/* see ft.h for specification */
int FT_rmDir(char *path) {
    Node curr;
    int result;

    assert(path != NULL);

    if (!isInitialized)
        return INITIALIZATION_ERROR;

    curr = FT_traversePath(path);
    if (curr == NULL)
        result = NO_SUCH_PATH;
    else if (Node_isFile(curr))
        result = NOT_A_DIRECTORY;
    else
        result = FT_rmPathAt(path, curr);

    return result;
}

/* see ft.h for specification */
int FT_insertFile(char *path, void *contents, size_t length) {
    Node curr;
    int result;

    assert(path != NULL);

    if (!isInitialized)
        return INITIALIZATION_ERROR;

    if (root != NULL && Node_isFile(root))
        return CONFLICTING_PATH;

    curr = FT_traversePath(path);
    if (curr != NULL && Node_isFile(curr))
        return ALREADY_IN_TREE;

    result = FT_insertRestOfPath(path, curr, TRUE, contents, length);
    return result;
}

/* see ft.h for specification */
boolean FT_containsFile(char *path) {
    Node curr;
    boolean result;

    assert(path != NULL);

    if (!isInitialized)
        return FALSE;

    curr = FT_traversePath(path);

    if (curr == NULL)
        result = FALSE;
    else if (strcmp(path, Node_getPath(curr)))
        result = FALSE;
    else if (!(Node_isFile(curr)))
        result = FALSE;
    else
        result = TRUE;

    return result;
}

/* see ft.h for specification */
int FT_rmFile(char *path) {
    Node curr;
    int result;

    assert(path != NULL);

    if (!isInitialized)
        return INITIALIZATION_ERROR;

    curr = FT_traversePath(path);
    if (curr == NULL)
        result = NO_SUCH_PATH;
    else if (!(Node_isFile(curr)))
        result = NOT_A_FILE;
    else
        result = FT_rmPathAt(path, curr);

    return result;
}

/* see ft.h for specification */
void *FT_getFileContents(char *path) {
    Node curr;

    assert(path != NULL);

    curr = FT_traversePath(path);
    if (curr == NULL)
        return NULL;

    if (!Node_isFile(curr))
        return NULL;

    return Node_getContents(curr);
}

/* see ft.h for specification */
void *FT_replaceFileContents(char *path, void *newContents,
                             size_t newLength) {
    Node curr;
    void *oldContents;

    assert(path != NULL);

    curr = FT_traversePath(path);
    if (curr == NULL)
        return NULL;

    if (!Node_isFile(curr))
        return NULL;

    oldContents = Node_getContents(curr);
    Node_setContents(curr, newContents, newLength);
    return oldContents;
}

/* see ft.h for specification */
int FT_stat(char *path, boolean *type, size_t *length) {
    Node curr;

    assert(path != NULL);
    assert(type != NULL);
    assert(length != NULL);

    if (!isInitialized)
        return INITIALIZATION_ERROR;

    curr = FT_traversePath(path);
    if (curr == NULL)
        return NO_SUCH_PATH;

    if (Node_isFile(curr)) {
        *type = TRUE;
        *length = Node_getLength(curr);
    } else
        *type = FALSE;

    return SUCCESS;
}

/* see ft.h for specification */
int FT_init(void) {
    if (isInitialized)
        return INITIALIZATION_ERROR;

    isInitialized = 1;
    root = NULL;
    count = 0;

    return SUCCESS;
}

/* see ft.h for specification */
int FT_destroy(void) {
    if (!isInitialized)
        return INITIALIZATION_ERROR;

    FT_removePathFrom(root);
    root = NULL;
    isInitialized = 0;

    return SUCCESS;
}

/* Performs a pre-order traversal of the tree rooted at n, inserting
   each payload to DynArray_T d beginning at index i. Returns the next
   unused index in d after the insertion(s). */
static size_t FT_preOrderTraversal(Node n, DynArray_T d, size_t i) {
    size_t c;

    assert(d != NULL);

    if (n != NULL) {
        (void)DynArray_set(d, i, Node_getPath(n));
        i++;
        if (!Node_isFile(n))
            for (c = 0; c < Node_getNumChildren(n); c++)
                i = FT_preOrderTraversal(Node_getChild(n, c), d, i);
    }
    return i;
}

/* Alternate version of strlen that uses pAcc as an in-out parameter to
   accumulate a string length, rather than returning the length of str,
   and also always adds one more in addition to str's length. */
static void FT_strlenAccumulate(char *str, size_t *pAcc) {
    assert(str != NULL);
    assert(pAcc != NULL);

    if (str != NULL)
        *pAcc += (strlen(str) + 1);
}

/* Alternate version of strcat that inverts the typical argument
   order, appending str onto acc, and also always adds a newline at
   the end of the concatenated string. */
static void FT_strcatAccumulate(char *str, char *acc) {
    assert(str != NULL);
    assert(acc != NULL);

    if (str != NULL)
        strcat(acc, str);
    strcat(acc, "\n");
}

/* see ft.h for specification */
char *FT_toString() {
    DynArray_T nodes;
    size_t totalStrlen = 1;
    char *result = NULL;

    if (!isInitialized)
        return NULL;

    nodes = DynArray_new(count);
    (void)FT_preOrderTraversal(root, nodes, 0);

    DynArray_map(nodes, (void (*)(void *, void *))FT_strlenAccumulate,
                 (void *)&totalStrlen);

    result = malloc(totalStrlen);
    if (result == NULL) {
        DynArray_free(nodes);
        return NULL;
    }

    *result = '\0';

    DynArray_map(nodes, (void (*)(void *, void *))FT_strcatAccumulate,
                 (void *)result);

    DynArray_free(nodes);
    return result;
}
