/*--------------------------------------------------------------------*/
/* node.h                                                             */
/* Authors: Byron Zhang, Nicholas Padmanabhan, Christopher Moretti    */
/*--------------------------------------------------------------------*/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stddef.h>

#include "a4def.h"

/*
  A Node is an object that contains a path payload and references to
  the Node's parent (if it exists) and children (if they exist).
*/
typedef struct node* Node;

/*
  Given a parent Node and a directory string dir, returns a new
  Node structure or NULL if any allocation error occurs in creating
  the node or its fields. If isFile is TRUE, the Node is a file, so set
  its contents to fileContents and its length to fileLength. Otherwise,
  ignore fileContents and fileLength.

  The new structure is initialized to have its path as the parent's
  path (if it exists) prefixed to the directory string parameter,
  separated by a slash. It is also initialized with its parent link
  as the parent parameter value (but the parent itself is not changed
  to link to the new Node.  The children links are initialized but
  do not point to any children.
*/
Node Node_create(Node parent, const char* dir, boolean isFile,
                 void* fileContents, size_t fileLength);

/*
  Destroys the entire hierarchy of Nodes rooted at n, including n
  itself.

  Returns the number of Nodes destroyed.
*/
size_t Node_destroy(Node n);

/*
  Returns Node n's path.
*/
const char* Node_getPath(Node n);

/*
  Returns the number of child directories n has.

  Note that n cannot be a file.
*/
size_t Node_getNumChildren(Node n);

/*
  Returns TRUE if n is a file, or FALSE if n is a directory.
*/
boolean Node_isFile(Node n);

/*
  Returns the child Node of n with identifier childID, if one exists,
  otherwise returns NULL.

  Note that n cannot be a file.
*/
Node Node_getChild(Node n, size_t childID);

/*
  Returns the parent Node of n, if it exists, otherwise returns NULL
*/
Node Node_getParent(Node n);

/*
  Returns the contents of Node n.

  Note that n must be a file.
*/
void* Node_getContents(Node n);

/*
  Returns the length of Node n.

  Note that n must be a file.
*/
size_t Node_getLength(Node n);

/*
  Sets the contents of n as fileContents and the length of n as
  fileLength.

  Note that n must be a file.
*/
void Node_setContents(Node n, void* fileContents, size_t fileLength);

/*
  Makes child a child of parent, if possible, and returns SUCCESS.
  This is not possible in the following cases:
  * child's path is not parent's path + / + directory,
    in which case returns PARENT_CHILD_ERROR
  * parent already has a child with child's path,
    in which case returns ALREADY_IN_TREE
  * parent is unable to allocate memory to store new child link,
    in which case returns MEMORY_ERROR

  Note that parent cannot be a file.
 */
int Node_linkChild(Node parent, Node child);

/*
  Unlinks Node parent from its child Node child, leaving the
  child Node unchanged.

  Note that parent cannot be a file.

  Returns PARENT_CHILD_ERROR if child is not a child of parent,
  and SUCCESS otherwise.
 */
int Node_unlinkChild(Node parent, Node child);

/*
  Transforms Node into a file; sets its contents to fileContents and its
  length to fileLength.

  Note that n cannot already be a file.
*/
void Node_transformToFile(Node n, void* fileContents,
                          size_t fileLength);

/*
  Returns a string representation n, or NULL if there is an
  allocation error. Allocates memory for the returned string, which
  is then owned by client!
*/
char* Node_toString(Node n);

#endif
