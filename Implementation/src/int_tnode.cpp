#include "int_tnode.hpp"
#include <stdio.h>

IntTNode::IntTNode (int pNum) : vNum (pNum)
{
}

IntTNode::~IntTNode ()
{
}

void IntTNode::Print ()
{
    printf ("%d\n", vNum);
}

int IntTNode::GetNode ()
{
    return vNum;
}
