#include "types.h"
#include "user.h"

int arrGlobal[10000];

int main(int argc, char *argv[])
{
    int arrLocal[10000];
    //intializing arrLocal
    for(int i = 0; i < 10000; i++){
        arrLocal[i] = 0;
        arrLocal[i]++;
    }
    pgtPrint();
    exit();
}