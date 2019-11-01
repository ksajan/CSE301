#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
void main()
{
  int mbt[50];
  int i, j, k, pa, bs, bfree, bfree_mode, ps, js, var = 0, var2=0, jn, job;

clrscr();
    printf("\n\t\t PAGING\n");

    printf("\n\t Enter the physical address space:");
        scanf("%d",&pa);
    printf("\n\t Enter the Block size:");
        scanf("%d",&bs);
    bfree = pa / bs;
    printf("\n\t the number of blocks are = %d\n",bfree);
    bfree_mode = bfree;
    for( i = 0 ; i < bfree ; i++ ) {
        mbt[i] = 0;
    }

    printf("How many jobs do you want to enter to the memory ?\n");
        scanf("%d",&jn);
       for ( j = 0 ; j <= jn+2 ; j++  )  {

        printf("Enter %d Job size :\n",j+1);
            scanf("%d",&job);
        k = var;
        var = job / bs ;
        if (job % bs !=0)
            var +=1;
        if ( var <= bfree ) {
            var2 += var;
            for ( k ; k < var2 ; k++  ) {
                mbt[k] = j+1;
            }
            bfree -= var;
            printf("mbt[0] = OS Reserved!\n");
            for ( i = 1 ; i < bfree_mode ; i++)
                printf("mbt[%d] = %d\n",i,mbt[i]);


        }else if ( var > bfree ) {
            printf("\nThe Memory is not enough for the %d Job",j+1);
            break;
          }
    }

getch();
}
