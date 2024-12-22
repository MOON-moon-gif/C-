#include <stdio.h>
  int main(){
     printf("The size of int is %zu bytes.\n",
	    sizeof(int));
     printf("The size of float is %zu bytes.\n",
	    sizeof(float));
     printf("The size of double is %zu bytes.\n",
	    sizeof(double));
     printf("The size of char is %zu bytes.\n",
	    sizeof(char));
     return 0;
}
