#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void Bubblesort(vector<int>& arr, int n){
    for (int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubblesort(vector<int> &arr, int n){
    bool sorted = false;

    while(!sorted){
        sorted = true;

        // Odd phase
        #pragma omp parallel for
        for(int i = 1; i < n - 1; i += 2){
            if(arr[i] > arr[i + 1]){
                #pragma omp critical
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        // Even phase
        #pragma omp parallel for
        for(int i = 0; i < n - 1; i += 2){
            if(arr[i] > arr[i + 1]){
                #pragma omp critical
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

int main(){
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    parallelBubblesort(arr, n);

    cout << "Sorted array is: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
