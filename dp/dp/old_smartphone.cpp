#include<iostream>

using namespace std;
int N,Op,maxTouch;
int touchNum[10];
int Operator[4];
int target;

int main(int argc, char** argv)
{
	int test_case, ans;
	int T,i,j,k;
	freopen("old_smartphone_sample_input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int ans = 0;
		int val;
		cin >> N >> Op >> maxTouch;
		cout<< N << " " << Op << " " << maxTouch<< "\n";;
		for(i = 0; i < N; i++){
			cin >> val;
			touchNum[i] = val- '0';
			cout << touchNum[i]<< " ";
		}
		cout << "\n";
		for(i = 0; i < Op; i++){
			cin >> Operator[i];
			cout << Operator[i] << " ";
		}
		cout << "\n";
		cin >> target;
		cout<< target << "\n";
		cout << "#" << test_case << ' ' << ans << endl;		
	}

	return 0;
}