#include<iostream>

using namespace std;

#define MAX_H 10
#define MAX_W 25

int H,W;
int Wafer[MAX_H][MAX_W];

int dp[MAX_W][1<<MAX_H][1<<MAX_H];

void print(){
	for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++){
			cout << Wafer[i][j] << ' ';
		}
		cout<<"\n";
	}
	cout<<"\n";
}
int getPos(int col){
	int val = 0;
	for(int i = 0 ; i < H; i++){
		if(Wafer[i][col] >= 1){
			val |= 1 << i;
		}
	}
	return val;
}
int max(int a, int b){return (a>b)?a:b;}

int findMax(int startH, int startW){
	int currColVal = getPos(startW);
	int nextColVal = getPos(startW+1);
	if(dp[startW][currColVal][nextColVal] > 0)
		return dp[startW][currColVal][nextColVal];

	int i,j, nextH, nextW;
	if((startH >= H-1) && (startW >= W-1)){
		return 0;
	}
	int maxVal = 0;
	//int count = 0;
	//for(i = startH; i < H-1; i++){
	j = startW;
		for(i = startH; i < H-1; i++){
			if((Wafer[i][j] | Wafer[i][j+1] | Wafer[i+1][j] | Wafer[i+1][j+1]) == 0){
				Wafer[i][j] = 2; Wafer[i][j+1] = 2; Wafer[i+1][j] = 2; Wafer[i+1][j+1] = 2;
				//total++;
				//count++;
				nextH = i+2;
				nextW = j;
				//print();
				maxVal = max(maxVal,1+findMax(nextH, nextW));
				//total--;
				Wafer[i][j] = 0; Wafer[i][j+1] = 0; Wafer[i+1][j] = 0; Wafer[i+1][j+1] = 0;
			}
		}
	//}
	for(j = startW+1; j < W-1; j++){
		for(i = 0; i < H-1; i++){
		
			if((Wafer[i][j] | Wafer[i][j+1] | Wafer[i+1][j] | Wafer[i+1][j+1]) == 0){
				Wafer[i][j] = 2; Wafer[i][j+1] = 2; Wafer[i+1][j] = 2; Wafer[i+1][j+1] = 2;
				//total++;
				nextH = i+2;
				nextW = j;
				//print();
				maxVal = max(maxVal,1+findMax(nextH, nextW));
				//total--;
				Wafer[i][j] = 0; Wafer[i][j+1] = 0; Wafer[i+1][j] = 0; Wafer[i+1][j+1] = 0;
			}
		}
	}
	dp[startW][currColVal][nextColVal] = maxVal;
	//print();
	return maxVal;
}

int dfs(){
	int i,j,k, nextH, nextW;
	int maxVal = 0;
	int flag;
	int count = 0;
#if 0
	for(i = 0; i < MAX_W; i++){
		for(j = 0; j < (1<<MAX_H); j++){
			for(k = 0; k < (1<<MAX_H); k++){
				dp[i][j][k] = 0;
			}
		}
	}
#endif
	for(j = 0; j < W-1; j++){
		flag = 0;
		for(i = 0; i < H-1; i++){
			if((Wafer[i][j] | Wafer[i][j+1] | Wafer[i+1][j] | Wafer[i+1][j+1]) == 0){
				Wafer[i][j] = 2; Wafer[i][j+1] = 2; Wafer[i+1][j] = 2; Wafer[i+1][j+1] = 2;
				nextH = i+2;
				nextW = j;
				//print();
				maxVal = max(maxVal,1+findMax(nextH, nextW));
				Wafer[i][j] = 0; Wafer[i][j+1] = 0; Wafer[i+1][j] = 0; Wafer[i+1][j+1] = 0;
				flag=1;
			}
		}
		if(flag ==1)
			count++;
		if(count==2)
			return maxVal;
	}
	return maxVal;
}

int main(int argc, char** argv)
{
	int test_case, ans;
	int T,i,j,k;
	freopen("chip_sample_input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int ans = 0;
		cin >> H >> W;
		for (i = 0; i < H; i++){
			for(j = 0; j < W; j++){
				cin >> Wafer[i][j];
				//cout << Wafer[i][j] << ' ';
			}

			//cout<<"\n";
		}
		//cout<<"\n";
		
		ans = dfs();
		cout << "#" << test_case << ' ' << ans << endl;
		for(i = 0; i < W; i++){
			for(j = 0; j < (1<<H); j++){
				for(k = 0; k < (1<<H); k++){
					dp[i][j][k] = 0;
				}
			}
		}
	}

	return 0;
}