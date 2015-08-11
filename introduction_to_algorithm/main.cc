#include <stdio.h>
#include "utils.h"
int main(void)
{
    int len, i;
    int arr[] = { 757,4,4943,57,565,444,883,48,9334,484,3,48,345,3,3990,44,48483,45,456,6,33,6765,4564 };
    len = sizeof(arr)/sizeof(arr[0]);
    quick_sort(arr,len);

    for(i=0;i<len;i++){
        printf("%d\n",arr[i]);
    }

    return 0;
}
