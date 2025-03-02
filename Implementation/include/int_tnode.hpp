#ifndef INT_TNODE_HPP
#define INT_TNODE_HPP

#include "tree_node.hpp"

class IntTNode : public TreeNode {

  public:

                IntTNode    (int pNum);

                ~IntTNode   ();

    void        Print       () override;
    int         GetNode     ();


  private:

    int         vNum;
};

#endif // !INT_TNODE_HPP
