#include <stdio.h>
void pushZeroEndOfArray (int arr[], int n) {
    int count = {0};
    for (int i = 0 ; i<n; i++){
        if (arr[i] != 0){
            arr[count++] = arr[i];
        }
    }
    while (count < n){
        arr[count++] = 0;
    }
}
int main() {
    int arr[] = { 2, 5, 6,  8, 9, 15,3, 6, 0, 12, 0, 35, 21, 0, 32,1 ,9, 8, 4 ,2 ,7, 6, 9, 0, 0 ,0 ,0 };
    int n = sizeof(arr)/sizeof(arr[0]);
    pushZeroEndOfArray(arr, n);
    printf("%s\n", "Array after pushing all zeros to end of array:");
    for (int i= 0; i<n ;i++){
        printf("%d ", arr[i]);
    } 
    return 0;

}
