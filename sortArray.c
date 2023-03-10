#include <stdio.h>

void sortByIndex(int arr[], int index[], int n) {
    int tempArr[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[index[i]];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = tempArr[i];
        index[i] = i;
    }
}
int main() {
    int arr[] = {16, 25, 42, 12, 35};
    int index[] = { 3, 1, 4, 2, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (n != sizeof(index) / sizeof(index[0])) {
        printf("Error: 2 mang khong bang nhau\n");
        return 1;
    }
    sortByIndex(arr, index, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}