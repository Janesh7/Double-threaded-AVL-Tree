#ifndef STOCK_NODE_HPP
#define STOCK_NODE_HPP

#include "tree_node.hpp"

class StockNode : public TreeNode {

  public:

                        StockNode   (char * pStockName = nullptr, int pStock = 0);
                        StockNode   (const StockNode & pOther);
                        ~StockNode  ();

           StockNode &  CopyStock   (const StockNode & pOther);

    static long         CmprName    (void * pNode1, void * pNode2);
    static long         CmprStock   (void * pNode1, void * pNode2);

           void         Print       () override;

  private:

           char *   vStockName;
           int      vStock;

};

#endif // !STOCK_NODE_HPP
