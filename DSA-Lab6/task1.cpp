#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

    void inputIDs(vector<int>& array,int n){
        array.resize(n);
        for(int i=0;i<n;i++){
            cout<<"ID "<<i+1<<":";
            cin>>array[i];
        }
    }

    int linearSearch(vector<int>& array,int n,int target){
        for(int i=0;i<n;i++){
            if(array[i]==target)
            return i;
        }
        return -1;
    }

    void displayResult(int index){
        if(index==-1)
        cout<<"ID Not Found"<<endl;
        else
        cout<<"Found at index: "<<index<<endl;
        
    }

    int main(void){
        vector<int> array;
        int n, target;
        cout<<"Enter number of IDs:"<<endl;
        cin>>n;
        if(n<0) n=0;
        inputIDs(array,n);
        cout<<"Targeted ID: "<<endl;
        cin>>target;
        displayResult(linearSearch(array,n,target));
        return 0;

    }


