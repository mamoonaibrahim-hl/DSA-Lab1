#include <iostream>
#include <vector>
using namespace std;

vector<int> temp;   // global helper vector

void merge(vector<int>& array,int left,int mid,int right){
    int i=left,j=mid+1,k=left;
    while(i<=mid && j<=right) // pick smaller element from both subarrays
        temp[k++]=(array[i]<=array[j])?array[i++]:array[j++];
    while(i<=mid) temp[k++]=array[i++];      // copy leftover (left half)
    while(j<=right) temp[k++]=array[j++];    // copy leftover (right half)
    for(int i=left;i<=right;i++)             // copy back to original array
        array[i]=temp[i];   
}

void mergeSort(vector<int>& array,int left,int right){
    if(left>=right) return;
    int mid=left+(right-left)/2;
    mergeSort(array,left,mid);
    mergeSort(array,mid+1,right);
    if(array[mid]<=array[mid+1]) return; // already sorted
    merge(array,left,mid,right);
}

void displayArray(vector<int>& array,int n){
    for(int i=0;i<n;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}

int main(void){
    int n;
    cout << "Number of marks: "; cin >> n;
    if (n < 0) n = 0;
    vector<int> arr(n);
    temp.resize(n); // allocate temp once globally
    for (int i = 0; i < n; i++) { cout << "  Mark " << i + 1 << ": "; cin >> arr[i]; }
    cout << "Before: "; displayArray(arr, n);
    mergeSort(arr,0, n - 1);
    cout << "After : "; displayArray(arr, n);
    return 0;
}
