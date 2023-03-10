#include <stdio.h>

void swapNumber(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sortReduce (int x[], int n) {
    for (int i = 0; i < n-1; i++){
        int min = i;
        for (int j=i+1; j<n; j++){
            if (x[i] < x[j]){
                min = j;
            }
        }
        swapNumber(&x[i], &x[min]);
    }
}
void printArray(int x[],int n){
    for (int i=0; i<n; i++){
        printf("%d ", x[i]);
    }
}

int main() {
    int a [100];
    int n;
    do{
        printf("Nhap so phan tu cua mang (0<n<=100): ");
        scanf("%d", &n);
    }while (n<=0 || n>100);

    for (int i = 0; i < n ; i++){
        printf("Nhap phan tu thu %d:", i+1);
        scanf("%d", &a[i]);
    }

    printf("\n Mang giam vua nhap  la: ");
    sortReduce(a, n);
    printArray(a, n);
    return 0;
}