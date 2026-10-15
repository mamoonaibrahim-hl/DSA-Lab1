#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool isSorted(vector<int>& array,int n){
    for(int i=1;i<n;i++)
       if (array[i-1]>array[i]) return false; //ascending order check
    return true;
}

void inputSortedIDs(vector<int>& array,int n){
    array.resize(n);
    while(true){
        for(int i=0;i<n;i++){
            cout<<"ID "<<i+1<<" : ";
            cin>>array[i];
        }
        if(isSorted(array,n)) return;
        cout<<"input is not in ascending order (SORTED)"<<endl<<"please re-enter";
    }
}

int binarySearch(vector<int>& array,int low,int high,int target){
    while(low<=high){
        int mid=low+(high-low)/2;
        if(array[mid]==target)     return mid;
        else if(array[mid]<target) low=mid+1; //search right half
        else                       high=mid-1; //search left half
    }
    return -1; //not found
}


int main(void){
    vector<int> array;
    int n,target;
    cout<<"Enter number of IDs:"<<endl;
    cin>>n;
    if(n<0) n=0;
    inputSortedIDs(array,n);
    cout<<"Targeted ID: "<<endl;
    cin>>target;
    int index=binarySearch(array,0,n-1,target);
    if(index==-1)cout<<"Not Found"<<endl;
    else         cout<<"Fount at Index "<<index<<endl;

    return 0;
}