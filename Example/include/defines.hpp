#ifndef DEFINES_HPP
#define DEFINES_HPP

typedef long (*CmprFunc)    (void * pVal1, void * pVal2);
typedef void (*ActionFunc)  (void * pNode, void * context);

enum eGoodBad {

    GOOD,
    BAD

};

#endif // !DEFINES_HPP
