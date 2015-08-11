#include <stdio.h>

void inline exchange(int arr[], int i_a, int i_b)
{
    int temp = arr[i_a];
    arr[i_a] = arr[i_b];
    arr[i_b] = temp;
}

void quick_sort_r(int arr[], int start, int end)
{
    if(end - start > 2) {
        int i, j;
        int mid = (start + end) / 2;
        
        if(arr[start] > arr[mid])
            exchange(arr, start, mid);
        if(arr[mid] > arr[end-1])
            exchange(arr, mid, end-1);
        if(arr[start] > arr[mid])
            exchange(arr, start, mid);

        exchange(arr, mid, end-1);
        j = start-1;
        for(i=start;i<end;i++){
            if(arr[i] <= arr[end-1]){
                j += 1;
                if(i != j)
                    exchange(arr, i, j);
            }
        }
        quick_sort_r(arr, start, j);
        quick_sort_r(arr, j, end);
    }
    else if(end - start == 2 && arr[start] > arr[end-1])
        exchange(arr, start, end-1);
    else
        return;
    
}

void quick_sort(int arr[], int len)
{
    quick_sort_r(arr, 0, len);    
}

