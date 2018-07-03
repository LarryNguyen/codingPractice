#include <stdio.h>
#include <string.h>
#include <vector>
#include <string.h>

using namespace std;

typedef struct Point{
	int x;
	int y;
};
typedef struct Block{
	Point pf;
	Point pt;
};
long long *A;
int width, height;
int isExist(Point from, Point to, vector<Block> badBlocks){
	for(int i = 0; i < badBlocks.size(); i++){
		if((badBlocks[i].pf.x == from.x && badBlocks[i].pf.y == from.y && 
			badBlocks[i].pt.x == to.x && badBlocks[i].pt.y == to.y) || 
			(badBlocks[i].pf.x == to.x && badBlocks[i].pf.y == to.y && 
			badBlocks[i].pt.x == from.x && badBlocks[i].pt.y == from.y)){
				return 1;
		}
	}
	return 0;
}

long long countPath(Point from, Point to, vector<Block> badBlocks){
	long long count = 0;
	if(from.x == to.x && from.y == from.y)
		return 1;
	Point new_from1 = from;
	Point new_from2 = from;
	new_from1.x++;
	new_from2.y++;

	if(isExist(from, new_from1, badBlocks) == 1){
		if(isExist(from, new_from2, badBlocks) == 1)
			count = 0;
		else{
			if(new_from2.y <= to.y){
				if(A[new_from2.y*(width+1)+new_from2.x] == -1)
					A[new_from2.y*(width+1)+new_from2.x] = countPath(new_from2, to, badBlocks);				
				count += A[new_from2.y*(width+1)+new_from2.x];
			}
		}
	}else{
		if(isExist(from, new_from2, badBlocks) == 1){
			if(new_from1.x <= to.x){
				if(A[new_from1.y*(width+1)+new_from1.x] == -1)
					A[new_from1.y*(width+1)+new_from1.x] = countPath(new_from1, to, badBlocks);
				count += A[new_from1.y*(width+1)+new_from1.x];
			}
		}else{
			if(new_from1.x <= to.x){
				if(new_from2.y <= to.y){
					if(A[new_from1.y*(width+1)+new_from1.x] == -1)
						A[new_from1.y*(width+1)+new_from1.x] = countPath(new_from1, to, badBlocks);
					if(A[new_from2.y*(width+1)+new_from2.x] == -1)
						A[new_from2.y*(width+1)+new_from2.x] = countPath(new_from2, to, badBlocks);

					count += A[new_from1.y*(width+1)+new_from1.x] + A[new_from2.y*(width+1)+new_from2.x];
					
				}else{
					if(A[new_from1.y*(width+1)+new_from1.x] == -1)
						A[new_from1.y*(width+1)+new_from1.x] = countPath(new_from1, to, badBlocks);
					count += A[new_from1.y*(width+1)+new_from1.x];
				}
			}else{
				if(new_from2.y <= to.y){
					if(A[new_from2.y*(width+1)+new_from2.x] == -1)
						A[new_from2.y*(width+1)+new_from2.x] = countPath(new_from2, to, badBlocks);				
					count += A[new_from2.y*(width+1)+new_from2.x];
				}else{
					count = 0;
				}
			}
		}
	}
	return count;
}

long long numWays(int width, int height, vector<string> bad){
	long long count = 0;
	vector<Block> badBlocks;
	int n = bad.size();
	printf("%d \n",n);
	for(int i = 0; i < n; i++){
		Block bb;
		sscanf(bad[i].c_str(), "%d %d %d %d", &bb.pf.x, &bb.pf.y, &bb.pt.x, &bb.pt.y);
		printf("[%d,%d] -> [%d,%d] \n", bb.pf.x, bb.pf.y, bb.pt.x, bb.pt.y);
		badBlocks.push_back(bb);
	}

	A = (long long *) malloc(sizeof(long) * sizeof(long) * (width+1)*(height+1));
	for(int i = 0; i <= (width+1)*(height+1); i++){
		A[i] = -1;
	}
	Point from, to;
	from.x = 0;
	from.y = 0;
	to.x = width;
	to.y = height;
	count = countPath(from, to, badBlocks);
	return count;
}

int main(){
	width = 10;
	height = 100;
	//string bad[] = {""};//{"0 0 0 1", "6 6 5 6"};
	string bad[] = {"0 2 0 3", "1 2 1 3", "2 2 2 3", "3 2 3 3", "4 2 4 3", "5 2 5 3", "6 2 6 3", "7 2 7 3", "8 2 8 3", "9 2 9 3"};
	//string bad[] = {"6 6 5 6"};
	int n = sizeof(bad)/sizeof(string);
	//int n = 0;
	vector<string> vbad(bad, bad+n);
	
	printf(">>> %lld \n", numWays(width, height, vbad));

	getchar();
	return 0;
}