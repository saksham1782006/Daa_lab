#include <stdio.h>

// Insertion Sort
void insertionSort(int a[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(int a[], int n) {
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++) {
        min = i;

        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

// Merge function
void merge(int a[], int low, int mid, int high) {
    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

// Merge Sort
void mergeSort(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

// Display array
void display(int a[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main() {
    int a[100], n, choice, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\n--- SORTING MENU ---\n");
    printf("1. Insertion Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Merge Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            insertionSort(a, n);
            printf("\nSorted using Insertion Sort: ");
            break;

        case 2:
            selectionSort(a, n);
            printf("\nSorted using Selection Sort: ");
            break;

        case 3:
            mergeSort(a, 0, n - 1);
            printf("\nSorted using Merge Sort: ");
            break;

        default:
            printf("Invalid choice!\n");
            return 0;
    }

    display(a, n);

    return 0;
}

