#include<stdio.h>
#include<iostream>

using namespace std;

bool pathInMatrix(int a[3][3], int starti, int startj, int endi, int endj, int M, int N,bool visited[3][3]) {
		
	if (a[starti][startj] != -1 && starti >= 0 && starti < N && startj >= 0 && startj < N && !visited[starti][startj]) {
		visited[starti][startj] = true;
		if  (starti == endi && startj == endj)
			return true;
		if ( pathInMatrix(a, starti, startj-1, endi, endj, M, N,visited) )
			return true;
		if ( pathInMatrix(a, starti + 1, startj, endi, endj, M, N,visited) )
			return true;
		if ( pathInMatrix(a, starti, startj+1, endi, endj, M, N,visited) )
			return true;
		if ( pathInMatrix(a, starti - 1, startj, endi, endj, M, N,visited) )
			return true;
	}
	return false;
	}


int main() {
	int a[3][3] = { { 1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 } };
	int starti = 0,startj = 0,endi = 2,endj = 2;
	int M = 3, N = 3;
	bool visited[3][3] = { false };
	if (pathInMatrix(a, starti, startj, endi, endj, M, N,visited)) 
		cout << "Yes" << endl;
	else
		cout << "no" << endl;
	return 0;
}
