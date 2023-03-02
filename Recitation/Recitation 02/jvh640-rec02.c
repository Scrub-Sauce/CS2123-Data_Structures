#include <stdio.h>

void increaseA(int val) { val++;}
void increaseB(int *pval) { pval++;}
void increaseC(int *pval) { *pval++;}
void increaseD(int *pval) { (*pval)++;}
void exchange(int **p1, int **p2){
    int *temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void main(){
    int a = 10, b = 20, c = 30, temp, sum, *tmp, *pa, *pb, *pc, **ppa, **ppb, **ppc;
    
    pa = &a;
    pb = &b;
    pc = &c;
    ppa = &pa;
    ppb = &pb;
    ppc = &pc;
    
    printf("%d %d %d\n", a, *pb, **ppc); 
    sum = a + *pb + **ppc;
    printf("%d\n", sum);
    temp = *pa;
    *pa = **ppb;
    **ppb = temp;
    printf("%d %d\n", a, b);
    
    tmp = &*pa;
    pa = &**ppb;
    *ppb = tmp;
    
    printf("%d %d %d %d\n", a, b, *pa, *pb);
    /*on line 26 I set the value of tmp as the address of a, the we change the value of the pointer pa to the address of b, then the override the value of pb as the address of a which was stored in tmp then Prints the value of a and the value of b then pa prints the value of b and pb prints the value of pa*/
    
    increaseA(a);//increments the value within the function but does not return the new value to main 
    printf("%d\n", a);
    increaseB(&a); //executes from right to left, so it increments the address of a
    printf("%d\n", a);
    increaseC(&a); //executes from right to left again and increments the adress stored in this value.
    printf("%d\n", a);
    increaseD(&a); //executes whats in the braces first then increments the value stored in that pointer.
    printf("%d\n", a);
    printf("%d %d %p %p\n", *pa, *pb, pa, pb);
    exchange(&pa, &pb); // Uses the addresses of each pointer to swap the address value stored in the pointer.
    printf("%d %d %p %p\n", *pa, *pb, pa, pb);
    exchange(&pa, ppb); // Uses the address of pa and the value in ppb to exchange addresses stored in the pointers
    printf("%d %d %p %p\n", *pa, *pb, pa, pb);
    exchange(ppa, ppb); // uses the values stored in ppa and ppb to change the pointers values
    printf("%d %d %p %p\n", *pa, *pb, pa, pb);
}