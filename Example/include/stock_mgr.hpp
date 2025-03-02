#ifndef STOCK_MGR_HPP
#define STOCK_MGR_HPP

#include "stock_node.hpp"
#include "tree.hpp"

constexpr const char * ANSI_CODE_TO_CLEAR_SCREEN = "\033[H\033[J";

enum eOptions {

    EXIT_STOCK,
    INSERT_STOCK,
    DELETE_STOCK,
    UPDATE_STOCK,
    SEARCH_STOCK,
    DISPLAY_STOCK,
    LEAST_STOCK

};

class StockMgr {

  public:

                    StockMgr ();
                    ~StockMgr ();

            void    StockMenu ();

  private:

            void    InsertStock ();
            void    DeleteStock ();
            void    UpdateStock ();
            void    Search      () const ;
            void    LowestStock () const ;
            void    PrintAll    () const ;

    static  void    PrintNode   (void * pStock, void * pContext);

            void    DisplayMenu () const;
            void    ClearScreen () const;
            void    WaitForEntr () const;

            void    InputStock  (StockNode *& pNode);

            // Data members
            Tree *  vStockName;
            Tree *  vStock;

};

#endif // !STOCK_MGR_HPP
