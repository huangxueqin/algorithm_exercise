#include <stdio.h>
void max_heapify(int arr[], int len, int p)
{
    int left = 2*p;
    int right = 2*p + 1;
    int largest;

    if(left < len && arr[p] < arr[left])
        largest = left;
    else
        largest = p;

    if(right < len && arr[largest] < arr[right])
            largest = right;

    if(largest != p){
        int temp = arr[p];
        arr[p] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr, len, largest);
    }

}

void min_heapify(int arr[], int len, int p)
{
    int left = 2*p;
    int right = 2*p + 1;
    int minimum;

    if(left < len && arr[p] > arr[left])
        minimum = left;
    else
        minimum = p;

    if(right < len && arr[minimum] > arr[right])
            minimum = right;

    if(minimum != p){
        int temp = arr[p];
        arr[p] = arr[minimum];
        arr[minimum] = temp;
        min_heapify(arr, len, minimum);
    }

}

void build_heap(int arr[], int len)
{
    int i;
    for(i=(len-1)/2;i>0;i--)
        max_heapify(arr, len, i);
}

void r_build_heap(int arr[], int len)
{
    int i;
    for(i=(len-1)/2;i>0;i--)
        min_heapify(arr, len, i);
}

void heap_sort(int arr[], int len)
{
    int i;
    int tmp;

    build_heap(arr, len);
    for(i=1;i<len;i++){
        tmp = arr[len-i];
        arr[len-i] = arr[1];
        arr[1] = tmp;
        max_heapify(arr, len-i, 1);
    }
}

void r_heap_sort(int arr[], int len)
{
    int i;
    int tmp;

    r_build_heap(arr, len);
    for(i=1;i<len;i++){
        tmp = arr[len-i];
        arr[len-i] = arr[1];
        arr[1] = tmp;
        min_heapify(arr, len-i, 1);
    }
}

void print_array(int arr[], int len)
{
    int i;

    printf("[");
    for(i=0;i<len;i++){
        if(i==0)
            printf(" %d",arr[i]);
        else
            printf(", %d",arr[i]);
    }
    printf(" ]\n");

}
