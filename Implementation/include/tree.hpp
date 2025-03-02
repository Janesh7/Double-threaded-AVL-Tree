#ifndef TREE_HPP
#define TREE_HPP

#include "tree_node.hpp"
#include "defines.hpp"

constexpr long BALANCING_FACTOR_MAX = 1;
constexpr long BALANCING_FACTOR_MIN = -1;

class Tree {

  public:
                Tree            (CmprFunc pFunc);
                ~Tree           ();

    eGoodBad    Insert          (TreeNode * pNode);
    TreeNode *  Delete          (TreeNode * pNode);
    TreeNode *  Search          (TreeNode * pNode);
    eGoodBad    Update          (TreeNode * pNode, TreeNode * pNewNode);

    void        Inorder         ();
    void        PreOrder        ();

    long        GetNodeCount    ();
    TreeNode *  GetFirst        ();

    void        Walk            (ActionFunc pActionFunc, void * pContext);

  private:

    long        GetHeight        (TreeNode * pNode);
    long        GetBalancefactor (TreeNode * pNode);

    void        UpdateHeight     (TreeNode * pNode);
    void        UpdateFirst      (TreeNode * pNode);
    void        UpdateLast       (TreeNode * pNode);

    void        DeleteAll        ();
    void        PreOrder         (TreeNode * pCurRoot);

    TreeNode *  Insert           (TreeNode * pCurRoot, TreeNode * pNode);
    TreeNode *  Delete           (TreeNode * pCurRoot, TreeNode * pNode);
    TreeNode *  Search           (TreeNode * pCurRoot, TreeNode * pNode);

    TreeNode *  LeftRotate       (TreeNode * pNode);
    TreeNode *  RightRotate      (TreeNode * pNode);
    TreeNode *  BalanceInsert    (TreeNode * pCurRoot, TreeNode * pNode);
    TreeNode *  BalanceDelete    (TreeNode * pNode);

    // Data members
    TreeNode *  vRoot;
    TreeNode *  vFirst;
    TreeNode *  vLast;

    long        vNodeCount;
    CmprFunc    vCmprFunc;

};

#endif // !TREE_HPP
