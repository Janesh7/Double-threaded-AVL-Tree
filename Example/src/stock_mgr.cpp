#include "stock_mgr.hpp"
#include "input_utils.hpp"
#include "string_utils.hpp"
#include <stdlib.h>

StockMgr::StockMgr () : vStockName (new Tree (StockNode::CmprName)), vStock (new Tree (StockNode::CmprStock))
{
}

StockMgr::~StockMgr ()
{
    delete vStockName;
    delete vStock;
}

void StockMgr::StockMenu ()
{
        int         choice;
        eOptions    selected_option;

    do {

        ClearScreen ();
        DisplayMenu ();

        printf ("Enter your choice: ");
        choice = GetInt ();

        selected_option = (eOptions) (choice);

        if (selected_option < EXIT_STOCK || selected_option > LEAST_STOCK) {

            printf ("\nInvalid choice, please try again.\n");
            WaitForEntr ();
            continue;

        }

        // Execute the corresponding option based on user choice
        switch (selected_option) {
            case INSERT_STOCK:
                InsertStock ();
                break;
            case DELETE_STOCK:
                DeleteStock ();
                break;
            case UPDATE_STOCK:
                UpdateStock ();
                break;
            case SEARCH_STOCK:
                Search ();
                break;
            case DISPLAY_STOCK:
                PrintAll ();
                break;
            case LEAST_STOCK:
                LowestStock ();
                break;
            case EXIT_STOCK:
                printf ("Exiting the program...\n");
                WaitForEntr ();  // Wait for Enter before exiting
                return;
            default:
                break;
        }

        WaitForEntr ();

    } while (true);
}

void StockMgr::InsertStock ()
{
        StockNode * new_stock = nullptr;
        StockNode * cpy_stock = new StockNode ();

    InputStock (new_stock);

    cpy_stock->CopyStock (*new_stock);

    if (vStockName->Insert (new_stock) == GOOD && vStock->Insert (cpy_stock) == GOOD) {

        printf ("\nStock successfully inserted.\n");

    } else {

        printf ("\nFailed to insert stock. Make sure the stock name is unique.\n");
        delete new_stock;
        delete cpy_stock;

    }
}

void StockMgr::DeleteStock ()
{
        char      * stock_name  = nullptr;
        StockNode * stock_obj   = nullptr;
        StockNode * search      = nullptr;
        StockNode * cpy_stock   = nullptr;

    if (vStockName->GetNodeCount () == 0) {

        printf ("\nNo stocks to delete. Enter nodes first.\n");
        return;

    }

    printf ("Enter stock name to delete:");
    GetString (stock_name);

    stock_obj = new StockNode (stock_name, INT_MIN);

    search = (StockNode *) vStockName->Delete (stock_obj);

    if (search == nullptr) {

        printf ("\nFailed to delete stock. Make sure the entered stock name exists.");
        delete stock_obj;
        return;

    } else {

        cpy_stock = (StockNode *) vStock->Delete (search);
        delete search;
        delete cpy_stock;
        printf ("\nStock deleted successfully");

    }

}

void StockMgr::UpdateStock ()
{
        char      * stock_name  = nullptr;
        StockNode * stock_obj   = nullptr;
        StockNode * search1     = nullptr;
        StockNode * search2     = nullptr;
        StockNode * new_stock   = nullptr;
        StockNode * new_copy    = new StockNode ();

    if (vStockName->GetNodeCount () == 0) {

        printf ("\nNo stocks to update. Enter nodes first.\n");
        return;

    }

    printf ("Enter stock name to update:");
    GetString (stock_name);

    stock_obj = new StockNode (stock_name, INT_MIN);

    search1 = (StockNode *) vStockName->Search (stock_obj);

    if (search1 == nullptr) {

        printf ("\nFailed to find stock with that name. Make sure the entered stock name exists.");
        delete stock_obj;
        delete new_copy;
        return;

    }

    search2 = (StockNode *) vStock->Search (search1);

    printf ("\nEnter new stock details:");
    InputStock (new_stock);

    new_copy->CopyStock (*new_stock);

    if (vStockName->Update (search1, new_stock) == GOOD && vStock->Update (search2, new_copy) == GOOD) {

        printf ("\nStock successfully Updated.\n");

    } else {

        printf ("\nFailed to update stock.\n");
        delete stock_obj;
        delete new_stock;
        delete new_copy;

    }
}

void StockMgr::Search () const
{
        char      * stock_name  = nullptr;
        StockNode * stock_obj   = nullptr;
        StockNode * search      = nullptr;

    if (vStockName->GetNodeCount () == 0) {

        printf ("\nNo stocks to search. Enter nodes first.\n");
        return;
    }

    printf ("Enter stock name to search:");
    GetString (stock_name);

    stock_obj = new StockNode (stock_name, INT_MIN);

    search = (StockNode *) vStockName->Search (stock_obj);

    if (search == nullptr) {

        printf ("\nFailed to find stock with that name. Make sure the entered stock name exists.");
        delete stock_obj;
        return;

    } else {

        printf ("\nFound stock details:\n");
        search->Print ();

    }
}

void StockMgr::LowestStock () const
{
        StockNode * lowest_stock = nullptr;

    if (vStockName->GetNodeCount () == 0) {

        printf ("\nNo stocks. Enter nodes first.\n");
        return;

    }

    lowest_stock = (StockNode *) vStock->GetFirst ();
    printf ("\nLowest stock details:\n");
    lowest_stock->Print ();

}

void StockMgr::PrintAll () const
{
    if (vStockName->GetNodeCount () == 0) {

        printf ("\nNo stocks. Enter nodes first.\n");

    }

    printf ("\nAll stock details:\n");

    vStockName->Walk (StockMgr::PrintNode, nullptr);

}

void StockMgr::PrintNode (void * pStock, void * pContext)
{

    StockNode * stock = (StockNode *) pStock;
    stock->Print ();

}

void StockMgr::DisplayMenu () const
{
    printf ("\n======= Stock Management Menu ========\n");
    printf ("1. Insert Stock\n");
    printf ("2. Delete Stock\n");
    printf ("3. Update Stock\n");
    printf ("4. Search Stock\n");
    printf ("5. Display Stock\n");
    printf ("6. Lowest Stock\n");
    printf ("0. Exit\n");
    printf ("======================================\n\n");
}

void StockMgr::ClearScreen () const
{
    printf (ANSI_CODE_TO_CLEAR_SCREEN);
}

void StockMgr::WaitForEntr () const
{
    printf ("\n\nPress Enter to continue...\n");
    (void) getchar ();  // Wait for Enter key press
}

void StockMgr::InputStock (StockNode *& pNode)
{
        char * stock_name = nullptr;
        int    stock;

    printf ("\nEnter stock name [UNIQUE]:");

    while (true) {

        GetString (stock_name);

        if (stock_name == nullptr || !(StrCompare (stock_name, ""))) {

            printf ("\nEnter a valid string");
            continue;

        }

        break;
    }

    printf ("\nEnter stock:");

    while (true) {

        stock = GetInt ();

        if (stock == INT_MIN) {

            printf ("\nInvalid input.\nEnter a valid int:");
            continue;
        }

        break;

    }

    pNode = new StockNode (stock_name, stock);

}
