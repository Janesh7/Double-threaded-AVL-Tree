#include "tree.hpp"

// Initializes a new tree with the provided comparison function.
// pFunc: A function pointer to a comparison function used for sorting nodes.
// Initializes the tree properties with default values.
Tree::Tree (CmprFunc pFunc) : vRoot (nullptr), vFirst (nullptr), vLast (nullptr), vNodeCount (0), vCmprFunc (pFunc)
{
}

Tree::~Tree ()
{
    DeleteAll ();
}

// Inserts a new node into the tree.
// pNode: A pointer to the TreeNode object to be inserted.
// Returns GOOD if the insertion was successful, BAD if the node already exists in the tree.
eGoodBad Tree::Insert (TreeNode * pNode)
{
        long       prev_count   = vNodeCount;

    vRoot = Insert (vRoot, pNode);

    if (prev_count == vNodeCount) {

        return BAD;

    } else {

        return GOOD;

    }
}

// Deletes a node from the tree.
// pNode: A pointer to the TreeNode object to be deleted.
// Returns GOOD or BAD based on whether the node was deleted or no.
// Note: The node will not be deleted so user should free the memory of the node
TreeNode * Tree::Delete (TreeNode * pNode)
{
        TreeNode * temp = nullptr;

    if (!vRoot) {
        return nullptr;
    }

    temp = Search (pNode);

    if (!temp) {
        return nullptr;
    }

    vRoot = Delete (vRoot, temp);
    return temp;
}

// Searches for a node in the tree.
// pNode: A pointer to the TreeNode to search for.
// Returns a pointer to the node if found, or nullptr if the node is not in the tree.
TreeNode * Tree::Search (TreeNode * pNode)
{
    return Search (vRoot, pNode);
}

// Updates an existing node by deleting the old one and inserting the new one.
// pNode: The node to be replaced.
// pNewNode: The new node to insert.
// Returns a pointer to the new node if the update was successful, or nullptr if the node to be updated was not found.
eGoodBad Tree::Update (TreeNode * pNode, TreeNode * pNewNode)
{

    if (!pNewNode || Delete (pNode) == nullptr) {
        return BAD;
    }

    if (Insert (pNewNode) == BAD) {

        Insert (pNode);  // Re insert old
        return BAD;

    }

    return GOOD;
}

// Traverses the tree in an in-order fashion and prints each node.
// Prints the nodes from the first to the last in the linked list.
// This assumes the tree is stored in a linked list fashion (vFirst -> vLast).
void Tree::Inorder ()
{
    if (vRoot == nullptr) {
        return;
    }

        TreeNode * start = vFirst;

    while (start) {
        start->Print ();
        start = start->uNext;
    }

}

void Tree::PreOrder ()
{
    PreOrder (vRoot);
}

long Tree::GetNodeCount ()
{
    return vNodeCount;
}

TreeNode * Tree::GetFirst ()
{
    return vFirst;
}

// Walks through the tree (inorder) and applies the provided action function to each node.
// pActionFunc: A function pointer to an action function that is applied to each node.
// pContext: A pointer to additional context that is passed to the action function. Maybe used for search etc while walking
void Tree::Walk (ActionFunc pActionFunc, void * pContext)
{
    if (vRoot == nullptr) {
        return;
    }

        TreeNode * start = vFirst;

    while (start) {

        pActionFunc (start, pContext);
        start = start->uNext;

    }
}

// Returns the height of a given node.
// pNode: A pointer to the node whose height is to be calculated.
// Returns the height of the node, or 0 if the node is nullptr.
long Tree::GetHeight (TreeNode * pNode)
{
    return (pNode) ? pNode->uHeight : 0;
}

// Returns the balance factor of a node, which is the difference between the height of its left and right subtrees.
// pNode: A pointer to the node whose balance factor is to be calculated.
// Returns the balance factor
long Tree::GetBalancefactor (TreeNode * pNode)
{
    if (!pNode) {
        return 0;
    }

    return GetHeight (pNode->uLeft) - GetHeight (pNode->uRight);
}

// Updates the height of a node based on the heights of its left and right children.
// pNode: A pointer to the node whose height is to be updated.
void Tree::UpdateHeight (TreeNode * pNode)
{
    if (pNode == nullptr) {
        return;
    }

        long height_left    = GetHeight (pNode->uLeft);
        long height_right   = GetHeight (pNode->uRight);

    pNode->uHeight = (height_left > height_right) ? height_left + 1 : height_right + 1;

}

// Updates the "first" pointer of the tree, which points to the node with the smallest value.
// pNode: A pointer to the node to be considered for being the "first".
void Tree::UpdateFirst (TreeNode * pNode)
{
    if (!vFirst) {

        vFirst = pNode;

    } else if (vCmprFunc (pNode, vFirst) < 0) {

        vFirst = pNode;

    }
}

// Updates the "last" pointer of the tree, which points to the node with the largest value.
// pNode: A pointer to the node to be considered for being the "last".
void Tree::UpdateLast (TreeNode * pNode)
{
    if (!vLast) {

        vLast = pNode;

    } else if (vCmprFunc (pNode, vLast) > 0) {

        vLast = pNode;

    }
}

// Deletes all nodes
void Tree::DeleteAll ()
{
    if (!vRoot) {
        return;
    }

        TreeNode * start    = vFirst;
        TreeNode * temp     = nullptr;

    while (start) {

        temp = start->uNext;
        delete start;
        start = temp;

    }

    vRoot       = nullptr;
    vFirst      = nullptr;
    vLast       = nullptr;
    vNodeCount  = 0;

}

void Tree::PreOrder (TreeNode * pCurRoot)
{
    if (!pCurRoot) {
        return;
    }

    pCurRoot->Print ();
    PreOrder (pCurRoot->uLeft);
    PreOrder (pCurRoot->uRight);
}

// Recursively inserts a node into the tree rooted at pCurRoot.
// pCurRoot: The current root of the subtree.
// pNode: A pointer to the node to be inserted.
// Returns the new root of the subtree/tree after insertion.
TreeNode * Tree::Insert (TreeNode * pCurRoot, TreeNode * pNode)
{
        bool       found    = false;
        TreeNode * temp     = nullptr;
        TreeNode * new_node = nullptr;

    if (!pCurRoot) {

        UpdateHeight (pNode);
        UpdateFirst (pNode);
        UpdateLast (pNode);
        vNodeCount++;
        return pNode;

    }

    if (vCmprFunc (pNode, pCurRoot) < 0) {

        found = !(pCurRoot->uLeft);

        pCurRoot->uLeft = Insert (pCurRoot->uLeft, pNode);

        if (found) {

            new_node = pCurRoot->uLeft;

            new_node->uPrev = pCurRoot->uPrev;
            new_node->uNext = pCurRoot;

            if (pCurRoot->uPrev) {
                pCurRoot->uPrev->uNext = new_node;
            }

            pCurRoot->uPrev = new_node;

        }

    } else if (vCmprFunc (pNode, pCurRoot) > 0) {

        found = !(pCurRoot->uRight);

        pCurRoot->uRight = Insert (pCurRoot->uRight, pNode);

        if (found) {

            new_node = pCurRoot->uRight;

            new_node->uPrev = pCurRoot;
            new_node->uNext = pCurRoot->uNext;

            if (pCurRoot->uNext) {
                pCurRoot->uNext->uPrev = new_node;
            }

            pCurRoot->uNext = new_node;

        }

    } else {

        return pCurRoot; // return same node

    }

    UpdateHeight (pCurRoot);

    return BalanceInsert (pCurRoot, pNode);
}

// Recursively deletes a node from the tree rooted at pCurNode.
// pCurNode: The current node in the subtree where the deletion is to take place.
// pNode: The node to be deleted.
// Returns the new root of the subtree after deletion, or nullptr if the node is not found.
TreeNode * Tree::Delete (TreeNode * pCurNode, TreeNode * pNode)
{
        TreeNode * temp         = nullptr;
        TreeNode * successor    = nullptr;

    if (!pCurNode) {

        return nullptr;

    }

    if (vCmprFunc (pNode, pCurNode) < 0) {

        pCurNode->uLeft = Delete (pCurNode->uLeft, pNode);

    } else if (vCmprFunc (pNode, pCurNode) > 0) {

        pCurNode->uRight = Delete (pCurNode->uRight, pNode);

    } else { // found

        // both child
        if (pCurNode->uLeft && pCurNode->uRight) {

            successor = pCurNode->uNext;

            pCurNode->uRight = Delete (pCurNode->uRight, successor);

            successor->uLeft = pCurNode->uLeft;
            successor->uRight = pCurNode->uRight;

            if (pCurNode->uPrev) {
                pCurNode->uPrev->uNext = successor;
            }

            if (pCurNode->uNext) {
                pCurNode->uNext->uPrev = successor;
            }

            successor->uPrev = pCurNode->uPrev;
            successor->uNext = pCurNode->uNext;

            pCurNode = successor;

        } else if (!pCurNode->uLeft && !pCurNode->uRight) {    // No child

            // Update threads
            if (pCurNode->uPrev) {
                pCurNode->uPrev->uNext = pCurNode->uNext;
            }

            if (pCurNode->uNext) {
                pCurNode->uNext->uPrev = pCurNode->uPrev;
            }

            // Update vFist and vLast
            if (pCurNode == vFirst) {
                vFirst = pCurNode->uNext;
            }

            if (pCurNode == vLast) {
                vLast = pCurNode->uPrev;
            }

            pCurNode = nullptr;
            vNodeCount--;

        } else {

            // Update threads
            if (pCurNode->uPrev) {
                pCurNode->uPrev->uNext = pCurNode->uNext;
            }

            if (pCurNode->uNext) {
                pCurNode->uNext->uPrev = pCurNode->uPrev;
            }

            temp = pCurNode->uRight;

            if (pCurNode->uLeft) {
                temp = pCurNode->uLeft;
            }

            if (pCurNode == vFirst) {
                vFirst = pCurNode->uNext;
            }

            if (pCurNode == vLast) {
                vLast = pCurNode->uPrev;
            }

            pCurNode = nullptr; 
            vNodeCount--;
            return temp;
        }
    }

    if (!pCurNode) {
        return nullptr;
    }

    UpdateHeight (pCurNode);

    return BalanceDelete (pCurNode);
}

// Recursively searches for a node in the tree rooted at pCurRoot.
// pCurRoot: The current root of the subtree.
// pNode: A pointer to the node to be searched.
// Returns a pointer to the node if found, or nullptr if the node is not found.
TreeNode * Tree::Search (TreeNode * pCurRoot, TreeNode * pNode)
{
    if (!pCurRoot) {
        return nullptr;
    }

    if (vCmprFunc (pNode, pCurRoot) < 0) {

        return Search (pCurRoot->uLeft, pNode);

    } else if (vCmprFunc (pNode, pCurRoot) > 0) {

        return Search (pCurRoot->uRight, pNode);
    
    }

    return pCurRoot;

}

// Performs a left rotation on the given node to restore the AVL balance.
// pNode: The node to be rotated.
// Returns the new root of the subtree after the rotation.
TreeNode * Tree::LeftRotate (TreeNode * pNode)
{
        TreeNode * right_node = pNode->uRight;

    // attach left subtree of right_node's to node's right to maintain BST property
    pNode->uRight = right_node->uLeft;

    right_node->uLeft = pNode;

    UpdateHeight (pNode);
    UpdateHeight (right_node);

    return right_node;

}

// Performs a right rotation on the given node to restore the AVL balance.
// pNode: The node to be rotated.
// Returns the new root of the subtree after the rotation.
TreeNode * Tree::RightRotate (TreeNode * pNode)
{
        TreeNode * left_node = pNode->uLeft;

    // attach right subtree of left_node's to node's left to maintain BST property
    pNode->uLeft = left_node->uRight;

    left_node->uRight = pNode;

    UpdateHeight (pNode);
    UpdateHeight (left_node);

    return left_node;

}

// Balances the tree after inserting a new node to ensure AVL property. [Based on value]
// pCurRoot: The current root of the subtree.
// pNode: The node that was just inserted.
// Returns the new root of the subtree after balancing.
TreeNode * Tree::BalanceInsert (TreeNode * pCurRoot, TreeNode * pNode)
{
        long balance_factor = GetBalancefactor (pCurRoot);

    // Left Left (LL) Case: Right Rotate
    if (balance_factor > 1 && vCmprFunc (pNode, pCurRoot->uLeft) < 0) {
        return RightRotate (pCurRoot);
    }

    // Right Right (RR) Case: Left Rotate
    if (balance_factor < -1 && vCmprFunc (pNode, pCurRoot->uRight) > 0) {
        return LeftRotate (pCurRoot);
    }

    // Left Right (LR) Case:
    if (balance_factor > 1 && vCmprFunc (pNode, pCurRoot->uLeft) > 0) {

        pCurRoot->uLeft = LeftRotate (pCurRoot->uLeft);  // Left rotate the left child
        // Then, right rotate the root
        return RightRotate (pCurRoot);

    }

    // Right Left (RL) Case:
    if (balance_factor < -1 && vCmprFunc (pNode, pCurRoot->uRight) < 0) {

        pCurRoot->uRight = RightRotate (pCurRoot->uRight);  // Right rotate the right child
        // Then, left rotate the root
        return LeftRotate (pCurRoot);

    }

    // No balancing needed, return the node
    return pCurRoot;
}

// Balances the tree after inserting a new node to ensure AVL property. [Based on BF]
// pCurRoot: The current root of the subtree.
// pNode: The node that was just inserted.
// Returns the new root of the subtree after balancing.
TreeNode * Tree::BalanceDelete (TreeNode * pNode)
{
    if (!pNode) {
        return nullptr;
    }

        long balance_factor = GetBalancefactor (pNode);

    if (balance_factor > 1) {

        if (GetBalancefactor (pNode->uLeft) > 0) {

            return RightRotate (pNode);

        } else {

            pNode->uLeft = LeftRotate (pNode->uLeft);
            return RightRotate (pNode);

        }
    }

    if (balance_factor < -1) {

        if (GetBalancefactor (pNode->uLeft) > 0) {

            pNode->uRight = RightRotate (pNode->uRight);
            return LeftRotate (pNode);

        } else {

            return LeftRotate (pNode);
        }
    }

    return pNode;

}
