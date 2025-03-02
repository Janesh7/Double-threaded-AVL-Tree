#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

class TreeNode {

  public:
                            TreeNode    ();

    virtual     void        Print       () {};
    virtual                 ~TreeNode   () {};

                // Data members
                TreeNode *  uNext;
                TreeNode *  uPrev;
                TreeNode *  uLeft;
                TreeNode *  uRight;

                long        uHeight;

};

#endif // !TREE_NODE_HPP
