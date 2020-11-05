/*--------------------------------------------------------------------*/
/* checker.c                                                          */
/* Author: Byron Zhang and Nicholas Padmanabhan                       */
/*--------------------------------------------------------------------*/

#include "checker.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dynarray.h"

/*--------------------------------------------------------------------*/

/* see checker.h for specification */
boolean Checker_Node_isValid(Node n) {
    Node parent, curr, next;
    const char *npath;
    const char *ppath;
    const char *rest;
    size_t i;
    int cmp;

    /* Check that n is not NULL */
    if (n == NULL) {
        fprintf(stderr, "Node is a NULL pointer\n");
        return FALSE;
    }

    parent = Node_getParent(n);
    npath = Node_getPath(n);

    /* Check that n's path is not NULL */
    if (npath == NULL) {
        fprintf(stderr, "Node's path is a NULL pointer\n");
        return FALSE;
    }

    if (parent != NULL) {
        /* Check that parent's path is a prefix of n's path */
        ppath = Node_getPath(parent);
        i = strlen(ppath);
        if (strncmp(npath, ppath, i)) {
            fprintf(stderr, "P's path is not a prefix of C's path\n");
            return FALSE;
        }

        /* Check that n's path after parent's path + '/' has no further
        '/' characters */
        rest = npath + i;
        rest++;
        if (strstr(rest, "/") != NULL) {
            fprintf(stderr, "C's path has grandchild of P's path\n");
            return FALSE;
        }
    } else {
        /* Check that root's path has zero slashes */
        if (strstr(npath, "/") != NULL) {
            fprintf(stderr, "Root's path contains a slash\n");
            return FALSE;
        }
    }

    /* Check that n's children are lexicographically sorted and are
    unique */
    for (i = 0; i < Node_getNumChildren(n) - 1; i++) {
        next = Node_getChild(n, i + 1);
        if (next == NULL)
            break;

        curr = Node_getChild(n, i);
        cmp = Node_compare(curr, next);

        /* Check that n's children are sorted */
        if (cmp > 0) {
            fprintf(stderr, "Node's children are not ordered\n");
            return FALSE;
        }
        /* Check that n's children are unique */
        else if (cmp == 0) {
            fprintf(stderr, "Node has a duplicate child\n");
            return FALSE;
        }
    }

    /* Check that n's children aren't NULL and that their parent is n */
    for (i = 0; i < Node_getNumChildren(n); i++) {
        curr = Node_getChild(n, i);
        if (curr == NULL) {
            fprintf(stderr, "Node has a NULL child\n");
            return FALSE;
        }

        parent = Node_getParent(curr);

        if (parent != n) {
            fprintf(stderr, "Node has a child with incorrect parent\n");
            return FALSE;
        }
    }

    return TRUE;
}

/*--------------------------------------------------------------------*/

/*
   Performs a pre-order traversal of the tree rooted at n.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise.
*/
static boolean Checker_treeCheck(Node n) {
    size_t c;

    if (n != NULL) {
        /* Check each non-root Node: all must be valid; if not, pass
         that failure back up immediately */
        if (!Checker_Node_isValid(n))
            return FALSE;

        for (c = 0; c < Node_getNumChildren(n); c++) {
            Node child = Node_getChild(n, c);

            /* If recurring down one subtree results in a failed check
               farther down, passes the failure back up immediately */
            if (!Checker_treeCheck(child))
                return FALSE;
        }
    }

    return TRUE;
}

/*--------------------------------------------------------------------*/

/* Returns the number of Nodes underneath n, including n itself. */
static size_t Checker_countNodes(Node n) {
    size_t c, i = 1;

    if (n == NULL)
        return 0;

    for (c = 0; c < Node_getNumChildren(n); c++)
        i += Checker_countNodes(Node_getChild(n, c));

    return i;
}

/*--------------------------------------------------------------------*/

/* see checker.h for specification */
boolean Checker_DT_isValid(boolean isInit, Node root, size_t count) {
    /* If the given DT is not initialized, its count should be 0 */
    if (!isInit)
        if (count != 0) {
            fprintf(stderr, "Not initialized, but count is not 0\n");
            return FALSE;
        }

    /* Check that the parent of root is NULL */
    if (root != NULL && Node_getParent(root) != NULL) {
        fprintf(stderr, "Parent of root is not NULL\n");
        return FALSE;
    }

    /* Check that count is correct for the given DT */
    if (Checker_countNodes(root) != count) {
        fprintf(stderr, "DT count (number of Nodes) is wrong\n");
        return FALSE;
    }

    /* Check invariants recursively at each Node from root */
    return Checker_treeCheck(root);
}
