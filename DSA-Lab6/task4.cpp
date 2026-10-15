#include <iostream>
#include <vector>
using namespace std;

const int DX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(const vector<vector<int>>& board,int N,int r,int c){
    return r>=0 && r<N && c>=0 && c<N && board[r][c]==-1;
}

bool solveKnightTour(vector<vector<int>>& board,int N,int r,int c,int moveNo){
    board[r][c]=moveNo;                  // mark current square
    if(moveNo==N*N) return true;         // base case: all squares visited

    for(int k=0;k<8;k++){                // try all 8 moves
        int nr=r+DX[k], nc=c+DY[k];
        if(isSafe(board,N,nr,nc)){
            if(solveKnightTour(board,N,nr,nc,moveNo+1))
                return true;
        }
    }

    board[r][c]=-1;                      // backtrack if dead end
    return false;
}

int main(void){
    int N,x,y;
    cout<<"Board size N: "; cin>>N;
    cout<<"Start row and column (0-based): "; cin>>x>>y;
    if(N<=0||x<0||x>=N||y<0||y>=N){
        cout<<"Invalid board size or start position."<<endl;
    }

    vector<vector<int>> board(N,vector<int>(N,-1));
    if(solveKnightTour(board,N,x,y,1)){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout.width(3);           // align numbers
                cout<<board[i][j];
            }
            cout<<endl;
        }
    } else {
        cout<<"No tour was found by the search."<<endl;
    }
    return 0;
}
