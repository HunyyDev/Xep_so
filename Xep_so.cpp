#define _CRT_SECURE_NO_WARNINGS
//https://khmt.uit.edu.vn/wecode/truonganpn/assignment/35/150
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#define ll long long 
#define ft(i,a,b) for(int i=a; i<=b; ++i)
#define ii pair<int,int>
using namespace std;

struct info 
{
	int stt;
	string num;
	vector<vector<ii>> connectPoint{ 4,vector<ii>()};
};

vector<info> A{ 4 };
int ans = 0;

void update(info &A, info &B) {
	ft(i, 0, A.num.size() - 1) {
		ft(j, 0, B.num.size() - 1) {
			if (A.num[i] == B.num[j]) {
				A.connectPoint[B.stt].push_back({ i,j });
				B.connectPoint[A.stt].push_back({ j,i });
			}
		}
	}
}

void Init() {
	ft(i, 0, 3) {
		ft(j, 0, 3) {
			A[i].connectPoint[j].clear();
		}
	}
	ft(i, 0, 2) {
		ft(j, i + 1, 3) {
			// find connectable point between A[i] and A[j]
			update(A[i], A[j]);
		}
	}
}

void check(int no1, int no2) {
	int no3 = -1, no4 = -1;
	ft(i, 0, 3) {
		if (i != no1 && i != no2) {
			if (no3 == -1) no3 = i; else no4 = i;
		}
	}
	for (int i = 0; i < A[no1].connectPoint[no3].size(); ++i) {
		for (int j = 0; j < A[no1].connectPoint[no4].size(); ++j) {
			ii a = A[no1].connectPoint[no3][i], b = A[no1].connectPoint[no4][j];
			if (abs(b.first - a.first) >= 2) {
				for (int k = 0; k < A[no2].connectPoint[no3].size(); ++k) {
					for (int l = 0; l < A[no2].connectPoint[no4].size(); ++l) {
						ii c = A[no2].connectPoint[no3][k], d = A[no2].connectPoint[no4][l];
						if (d.first - c.first == b.first - a.first && c.second - a.second == d.second - b.second && abs(c.second - a.second) >= 2 && (c.second - a.second) * (d.second - b.second) > 0) {
							++ans;
						}
					}
				}
			}

		}
	}
	reverse(A[no3].num.begin(), A[no3].num.end());
	reverse(A[no4].num.begin(), A[no4].num.end());
	Init();
}


void Process() {
	ft(i, 1, 3) {
		//choose 2 up and down parallel edge - default is Edge 0 and Edge i
		check(0, i);
		//choose again with 90 degree rotated sides edge 
		check(0, i);
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("XEPSO.INP", "r", stdin);
	//freopen("XEPSO.OUT", "w", stdout);
	cin >> A[0].num >> A[1].num >> A[2].num >> A[3].num;
	ft(i, 0, 3) A[i].stt = i;
	Init();
	Process();
	cout << ans;
	return 0;
}