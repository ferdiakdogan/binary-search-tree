#ifndef BINARY_SEARCH_TREE_CLASS
#define BINARY_SEARCH_TREE_CLASS

#include <iostream>
#include <cstdlib>

#ifndef NULL
const int NULL = 0;
#endif  // NULL

#include "treenode.h"

template <class T>
class BinSTree
{
    private:
        // pointer to tree root
        TreeNode<T> *root;

        // number of elements in the tree
        int size;

        // memory allocation/deallocation
        TreeNode<T>* GetTreeNode(const T& item, TreeNode<T> *lptr, TreeNode<T> *rptr);
        void FreeTreeNode(TreeNode<T> *p);

        // used by copy constructor and assignment operator
        TreeNode<T>* CopyTree(TreeNode<T> *t);

        // used by destructor and assignment operator
        void DeleteTree(TreeNode<T> *t);

    public:
        // locate a node with data item and its parent in tree.
        // used by Delete
        TreeNode<T>* FindNode(const T& item, TreeNode<T>* & parent) const;

        // constructors, destructor
        BinSTree(void);
        BinSTree(const BinSTree<T>& tree);
        ~BinSTree(void);

        // assignment operator
        BinSTree<T>& operator=(const BinSTree<T>& rhs);

        // tree handling methods
        void Insert(const T& item);
        void Delete(const T& item); // TO BE IMPLEMENTED IN PART 2
        int TreeEmpty(void) const;
        int TreeSize(void) const;

        TreeNode<T>* GetRoot(void) const;
};

// allocate a new tree node and return a pointer to it. Similar to GetNode of Linked List.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T>* BinSTree<T>::GetTreeNode(const T& item,TreeNode<T> *lptr,TreeNode<T> *rptr)
{
    TreeNode<T> *p;

    p = new TreeNode<T>(item, lptr, rptr);
    if (p == NULL)
    {
        exit(1); //exits with error code
    }
    return p;
}

// delete the storage occupied by a tree node
template <class T>
void BinSTree<T>::FreeTreeNode(TreeNode<T> *p)
{
    delete p;
}

// RECURSIVELY copy tree t and make it the tree stored in the current object.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T>* BinSTree<T>::CopyTree(TreeNode<T> *t)
{
    TreeNode<T> *newlptr, *newrptr, *newNode;

    // if tree branch NULL, return NULL
    if (t == NULL)
        return NULL;

    // RECURSIVELY copy the left branch of root t and assign its root to newlptr
    newlptr = t -> left;
    CopyTree(newlptr);
    // RECURSIVELY copy the right branch of tree t and assign its root to newrptr
    newrptr = t -> right;
    CopyTree(newrptr);

    // allocate storage for the current root node and assign its data value
    // and pointers to its subtrees. return its pointer

	newNode = new TreeNode<T>(t->data, newlptr, newrptr);

    return newNode;
}

// delete the tree stored by the current object.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::DeleteTree(TreeNode<T> *t)
{
    // if current root node is not NULL, delete its left subtree,
    // its right subtree and then the node itself
    if (t != NULL)
    {
        DeleteTree (t -> left);
        DeleteTree(t-> right) ;
        delete t;
    }

}

// search for data item in the tree. if found, return its node
// address and a pointer to its parent; otherwise, return NULL.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T> *BinSTree<T>::FindNode(const T& item, TreeNode<T>* & parent) const
{
    parent = root;
    TreeNode<T> *p;
    p = parent;

    while(item != p->data)
    {
        parent = p;
        if(item < p->data)
            p = p->left;
        else if(item > p->data)
            p = p->right;
        else
            return NULL;
    }
    if(item == p->data)
    {
        if(p == root)
            parent = p;
        return p;
    }


}

// constructor. initialize root to NULL, size to 0
template <class T>
BinSTree<T>::BinSTree(void): root(NULL), size(0)
{
}

// copy constructor.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>::BinSTree(const BinSTree<T>& tree)
{
    // copy tree to the current object. assign size
    root = new T(*tree.root);
    size = tree.size;
}

// destructor
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>::~BinSTree(void)
{
    DeleteTree(root);
}

// assignment operator.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>& BinSTree<T>::operator= (const BinSTree<T>& rhs)
{
    // can't copy a tree to itself
    if (this == &rhs)
        return *this;

    // Delete current tree. copy new tree into current object
    DeleteTree();
    CopyTree();

    // set the tree size
    size = rhs.size;

    // return reference to current object
    return *this;
}

// insert item into the search tree
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::Insert(const T& item)
{
    // t is current node in traversal, parent the previous node
    TreeNode<T> *t = root, *parent = NULL, *newNode;

    // Search for the point of insertion by searching for the item in the tree.
    // Terminate on on empty subtree, insertion is at the leaf position.
    while(root != NULL)
    {
        if(t == NULL)
            break;

        parent = t;
        if(item < t -> data)
            t = t->left;
        else if(item > t -> data)
            t = t->right;
        else if(item == t -> data)
            break;
    }

    // create the new leaf node and insert. Special case: Insertion can be at the root node.
    if(root == NULL)
        root = GetTreeNode(item,NULL,NULL);
    else
        {
            if(item != parent->data)
            {
                if(item < parent->data)
                {
                    newNode = new TreeNode<T>(item, NULL,NULL);
                    parent->left = newNode;
                }

                else if(item > parent->data)
                {
                    newNode = new TreeNode<T>(item, NULL,NULL);
                    parent->right = newNode;
                }
            }
        }
    // Update the state of the tree object
            size = size + 1;
}

// if item is in the tree, delete it. PART 2
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::Delete(const T& item)
{
    // DNodePtr = pointer to node D that is deleted
    // PNodePtr = pointer to parent P of node D
    // RNodePtr = pointer to node R that replaces D
    TreeNode<T> *DNodePtr, *PNodePtr, *RNodePtr;

    // search for a node containing data value item. obtain its
    // node address and that of its parent
    DNodePtr = FindNode(item,PNodePtr);

    // If D has a NULL pointer, the
    // replacement node is the one on the other branch
    if(DNodePtr->left == NULL && DNodePtr->right == NULL)
        delete DNodePtr;
    else if(DNodePtr->left == NULL)
    {
        RNodePtr = DNodePtr->right;
        PNodePtr->right = RNodePtr;
    }
    else if(DNodePtr->right == NULL)
    {
        RNodePtr = DNodePtr->left;
        PNodePtr->left = RNodePtr;
    }


    // Both pointers of DNodePtr are non-NULL.

    else
    {
        // Find and unlink replacement node for D.
        // Starting on the left branch of node D,
        // find node whose data value is the largest of all
        // nodes whose values are less than the value in D.
        // Unlink the node from the tree.

        // PofRNodePtr = pointer to parent of replacement node
        TreeNode<T> *PofRNodePtr;

        // first possible replacement is left child of D
        PofRNodePtr = DNodePtr->left;
        RNodePtr = PofRNodePtr;


        while(RNodePtr->right != NULL)
        {
            PofRNodePtr = RNodePtr;
            RNodePtr = RNodePtr->right;
        }



        if(RNodePtr != PofRNodePtr)
        {
            RNodePtr->right = DNodePtr->right;
            RNodePtr->left = DNodePtr->left;
            PofRNodePtr->right = NULL;
        }

        else
        {
            RNodePtr->right = DNodePtr->right;
            RNodePtr->left = PofRNodePtr->left;
        }



        // descend down right subtree of the left child of D,
        // keeping a record of current node and its parent.
        // when we stop, we have found the replacement



            // left child of deleted node is the replacement.
            // assign right subtree of D to R


            // we moved at least one node down a right branch
            // delete replacement node from tree by assigning
            // its left branch to its parent


            // put replacement node in place of DNodePtr.



    // complete the link to the parent node.

    // deleting the root node. assign new root

    // attach R to the correct branch of P
        if(PNodePtr != DNodePtr)
        {
            if(DNodePtr->data < PNodePtr->data)
            PNodePtr->left = RNodePtr;
            else if(DNodePtr->data > PNodePtr->data)
            PNodePtr->right = RNodePtr;
        }
        else
        {
            root = RNodePtr;
        }

    // delete the node from memory and decrement list size
        delete DNodePtr;
    }
    size = size - 1;
}

// indicate whether the tree is empty
template <class T>
int BinSTree<T>::TreeEmpty(void) const
{
    return root == NULL;
}

// return the number of data items in the tree
template <class T>
int BinSTree<T>::TreeSize(void) const
{
    return size;
}

// return the address of the root node.
template <class T>
TreeNode<T> *BinSTree<T>::GetRoot(void) const
{
    return root;
}

#endif  // BINARY_SEARCH_TREE_CLASS
