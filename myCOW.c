#include "types.h"
#include "stat.h"
#include "user.h"

#define N 3000		//global array size - change to see effect. Try 3000, 5000, 10000
int glob[N];
int main(){
    for(int i = 0; i < 3000; i++){
        glob[i] = 0;
    }
    int pid = fork();
    if(pid == 0){
        pgtPrint();
        for(int i = 0; i < 3000; i++){
            glob[i] = 1;
        }
        pgtPrint();        
    }
    else{
        pgtPrint(); 
        for(int i = 0; i < 3000; i++){
            glob[i] = 1;
        }
        pgtPrint(); 
    }
exit();
}
