#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
string chessboard1[8] = {
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW"
  };
string chessboard2[8] = {
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB"
  };
string board[50];
int W_start(int x, int y)
  {
    int cnt = 0;
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        if(chessboard1[i][j] != board[x+i][y+j]){
          cnt++;
        }
      }
    }
    return cnt;
  }
int B_start(int x, int y)
  {
    int cnt = 0;
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        if(chessboard2[i][j] != board[x+i][y+j]){
          cnt++;
        }
      }
    }
    return cnt;
  }

int main(){
  ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

  int min_value = 2500;
  pair<int,int> v;
  cin >> v.first >> v.second;

  for(int i = 0; i< v.first; i++){
    cin >> board[i]; 
  }

  for(int i = 0; i+8 <= v.first; i++){
    for(int j = 0; j+8 <= v.second; j++){
      int temp = 0;
      temp = min(W_start(i,j),B_start(i,j));
      if(temp < min_value){
        min_value = temp;
      }
    }
  }
  cout << min_value;
  return 0;
}