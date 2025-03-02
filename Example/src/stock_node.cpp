#include "stock_node.hpp"
#include <stdlib.h>
#include "string_utils.hpp"
#include <stdio.h>

StockNode::StockNode (char * pStockName, int pStock) : vStockName (pStockName), vStock (pStock)
{
}

// Copy Constructor
StockNode::StockNode (const StockNode & pOther) : vStock (pOther.vStock)
{
        size_t len = StrLen (pOther.vStockName) + 1;

    if (pOther.vStockName == nullptr) {

        vStockName = nullptr;
        return;

    }

    vStockName = (char *) malloc (len);

    if (vStockName) {

        StringCopy (vStockName, pOther.vStockName);

    } else {

        vStockName = nullptr;  // In case malloc fails

    }

}

// Destructor
StockNode::~StockNode ()
{
    if (vStockName != nullptr) {
        free(vStockName);
    }
}


StockNode & StockNode::CopyStock (const StockNode & pOther)
{
        size_t len;

    if (this == &pOther) {
        return *this;  // Handle self-assignment
    }

    if (vStockName != nullptr) {
        free (vStockName);
    }

    vStock = pOther.vStock;

    if (pOther.vStockName != nullptr) {

        len = StrLen (pOther.vStockName) + 1;
        vStockName = (char *) malloc (len);

        if (vStockName) {

            StringCopy (vStockName, pOther.vStockName);

        } else {

            vStockName = nullptr;  // In case malloc fails

        }

    } else {

        vStockName = nullptr;

    }

    return *this;
}

long StockNode::CmprName (void * pNode1, void * pNode2)
{
        char * stock_name1 = ((StockNode *) (pNode1))->vStockName;
        char * stock_name2 = ((StockNode *) (pNode2))->vStockName;

    return StrCompare (stock_name1, stock_name2);
}

long StockNode::CmprStock (void * pNode1, void * pNode2)
{
        char * stock_name1 = ((StockNode *) (pNode1))->vStockName;
        char * stock_name2 = ((StockNode *) (pNode2))->vStockName;

        long   stock1      = ((StockNode *) (pNode1))->vStock;
        long   stock2      = ((StockNode *) (pNode2))->vStock;

    return (stock1 - stock2) == 0 ? (StrCompare (stock_name1, stock_name2)) : (stock1 - stock2);
}

void StockNode::Print ()
{
    printf ("\nStock Name: %s", vStockName);
    printf ("\nStock     : %d\n", vStock);
}
