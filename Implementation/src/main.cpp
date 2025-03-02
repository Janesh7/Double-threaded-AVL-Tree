#include "int_tnode.hpp"
#include "tree.hpp"
#include <stdio.h>
#include <crtdbg.h>

long Cmpr (void * pObj1, void * pObj2)
{
    return (*(IntTNode *) pObj1).GetNode () - (*(IntTNode *) pObj2).GetNode ();
}

void Print (void * pObj, void * pContext)
{
    (*(IntTNode *) pObj).Print ();
}

int main ()
{
        Tree     *  tree    = new Tree     ((CmprFunc) Cmpr);
        IntTNode *  o1      = new IntTNode (10);
        IntTNode *  o2      = new IntTNode (20);
        IntTNode *  o3      = new IntTNode (30);
        IntTNode *  o4      = new IntTNode (40);
        IntTNode *  o5      = new IntTNode (50);
        IntTNode *  o6      = new IntTNode (25);

        IntTNode *  search  = nullptr;

    tree->Insert (o1);
    tree->Insert (o2);
    tree->Insert (o3);
    tree->Insert (o4);
    tree->Insert (o5);
    tree->Insert (o6);
    tree->Insert (o6);
    tree->Delete (o6);
    delete o6;
    tree->Delete (o5);
    delete o5;
    tree->Delete (o2);
    delete o2;
    tree->Delete (o1);
    tree->Delete (o1);
    delete o1;

    search = (IntTNode *) tree->Search (o1);
    search = (IntTNode *) tree->Search (o3);
    search->Print ();

    printf ("\n\n");

    tree->Inorder ();

    printf ("\n\n");
    tree->PreOrder ();
    printf ("\n\n");
    tree->Walk (Print, nullptr);

    delete tree;

    return 0;
}
