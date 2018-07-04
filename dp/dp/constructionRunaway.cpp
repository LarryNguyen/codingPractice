#include<iostream>

using namespace std;
int N,X;
int Ter[20][20];
int dp[7][7][20][2];//prev,curr, count, flag

int dfsRow(int row, int col, int prev, int count, int flag){
	int ret = 0;
	//printf("row = %d; col = %d, prev = %d, count = %d, flag = %d \n", row, col, prev, count, flag);
	if(dp[prev][Ter[row][col]][count][flag] != -1)
		return dp[prev][Ter[row][col]][count][flag];

	if(col == N){
		if((flag == 1) && (count < X)){
			ret = 0;
		}else{
			ret = 1;
		}
	}else{
		if(Ter[row][col] == prev){
			if((flag == 1) && (count == X)){			
				ret = dfsRow(row, col+1, Ter[row][col], 1, 0);			
			}else{
				ret = dfsRow(row, col+1, Ter[row][col], count+1, flag);
			}
		}else{
			if(Ter[row][col] == prev +1 ){
				if(count < X){
					ret = 0;
					dp[prev][Ter[row][col]][count][flag] = ret;
				}else{
					ret = dfsRow(row, col+1, Ter[row][col], 1, 0);
				}
			}else if(Ter[row][col] == prev-1){
				if((flag == 1) && (count < X)){
					ret = 0;
					dp[prev][Ter[row][col]][count][flag] = ret;
				}else{
					ret = dfsRow(row, col+1, Ter[row][col], 1, 1);
				}
			}else{
				ret = 0;
				dp[prev][Ter[row][col]][count][flag] = ret;
			}
		}
	}
	
	return ret;
}

int dfsCol(int row, int col, int prev, int count, int flag){
	int ret = 0;
	//printf("row = %d; col = %d, prev = %d, count = %d, flag = %d \n", row, col, prev, count, flag);
	if(dp[prev][Ter[row][col]][count][flag] != -1)
		return dp[prev][Ter[row][col]][count][flag];

	if(row == N){
		if((flag == 1) && (count < X)){
			ret = 0;
		}else{
			ret = 1;
		}
	}else{
		if(Ter[row][col] == prev){
			if((flag == 1) && (count == X)){
				ret = dfsCol(row+1, col, Ter[row][col], 1, 0);
			}else{
				ret = dfsCol(row+1, col, Ter[row][col], count+1, flag);
			}
		}else{
			if(Ter[row][col] == prev+1){
				if(count < X){
					ret = 0;
					dp[prev][Ter[row][col]][count][flag] = ret;
				}else{
					ret = dfsCol(row+1, col, Ter[row][col], 1, 0);
				}
			}else if(Ter[row][col] == prev-1){
				if((flag == 1) && (count < X)){
					ret = 0;
					dp[prev][Ter[row][col]][count][flag] = ret;
				}else{
					ret = dfsCol(row+1, col, Ter[row][col], 1, 1);
				}
			}else{
				ret = 0;
				dp[prev][Ter[row][col]][count][flag] = ret;
			}
		}
	}
	
	return ret;
}


int dfs(){
	int i;
	int ret = 0;

	for(i = 0; i < N; i++){
		ret += dfsRow(i, 1, Ter[i][0], 1, 0);
		//cout<< "Row "<<i<<": "<<ret<<endl;
		ret += dfsCol(1, i, Ter[0][i], 1, 0);
		//cout<< "Col "<<i<<": "<<ret<<endl;
	}
	return ret;
}

int main(int argc, char** argv)
{
	int test_case, ans;
	int T,i,j;
	freopen("constructionRunaway.txt", "r", stdin);
	cin >> T;
	//T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int ans = 0;
		cin >> N >> X;
		//cout<< N << " " << X << "\n";
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				cin >> Ter[i][j];				
				//cout << Ter[i][j]<< " ";
			}
			//cout << "\n";
		}
		//cout << "\n";

		for(int prev = 0; prev < 7; prev++){
			for(int cur = 0; cur < 7; cur++){
				for(int count = 0; count < 20; count++){
					for(int flag = 0; flag < 2; flag++){
						dp[prev][cur][count][flag] = -1;
					}
				}
			}
		}
		ans = dfs();

		cout << "#" << test_case << ' ' << ans << endl;		
	}

	return 0;
}