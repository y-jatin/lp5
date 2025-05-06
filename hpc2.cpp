#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}

void bubbleSortParallel(vector<int> &arr){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        #pragma omp parallel for
        for (int j = i%2; j < n-1; j += 2){
            if (arr[j] > arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}


void merge(vector<int> &arr, int l, int m, int r){
    vector<int> left(arr.begin()+l, arr.begin()+m+1);
    vector<int> right(arr.begin()+m+1, arr.begin()+r+1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()){
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int> &arr, int l, int r){
    if (l < r){
        int m = l + (r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

void mergeSortParallel(vector<int> &arr, int l, int r){
    if (l < r){
        int m = l + (r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSortParallel(arr,l,m);
            }
            #pragma omp section
            {
                mergeSortParallel(arr,m+1,r);
            }
        }
        merge(arr,l,m,r);
    }
}

void print(vector<int> &arr){
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
}

int main(){
    vector<int> arr = {9,1,2,7,4,10,15,13,20,19};
    mergeSortParallel(arr,0,9);
    print(arr);
    return 0;
}