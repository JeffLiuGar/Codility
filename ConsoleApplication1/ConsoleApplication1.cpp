// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;
int Flags(vector<int> &A) {
	//performance不够，需要考虑用空间换时间。
	//比如next peak里，应该可以吧所有的next peak都算出来，然后用直接数组查表来找，不用向右一个一个的找
	// write your code in C++14 (g++ 6.2.0)
	int ret = 0;
	//
	vector<int> vPeaks;
	int size = A.size();

	//get the peak positions first, store them in a vector v
	for (int i = 1; i < size-1; i++)
	{
		//handle index 0
		//if (0 == i)
		/*
		{
			if (size > 1)
			{
				if (A[0] > A[1])
					vPeaks.push_back(0);
			}
		}//handle the last element
		else if (i == size - 1)
		{
			if (A[i] > A[i - 1])
				vPeaks.push_back(i);
		}//rest of the vector*/
	
		if (A[i] > A[i - 1] && A[i] > A[i + 1])
			vPeaks.push_back(i);
	
	}


	int posMaxFlags = vPeaks.size();
	int peakSize = vPeaks.size();
	//int firstFlag = 0;
	//int firstPeak = vPeaks[0];
	int nextFlag;
	int nextPeak;
	//int currentFlag = firstFlag;
	int flags;
	for (flags = posMaxFlags; flags > 0; flags--)
	{
		int moves = flags -1;
		int currentFlag = 0;
		while (moves > 0 /*&& currentFlag < peakSize*/)
		{
			nextPeak = vPeaks[currentFlag] + flags;
			//nextFlag = currentFlag + flags;
			//if (nextFlag >= peakSize)
			//	break;
			int j;
			for (j = currentFlag + 1; j < peakSize; j++)
			{
				if (vPeaks[j] >= nextPeak)
				{
					currentFlag = j;
					break;
				}
			}
			if (j >= peakSize)
				break;
			moves--;
		}
		if (0 == moves)
		{
			ret = flags;
			break;
		}
	}
	ret = flags;

	return ret;
}

int main()
{
	//int Array[] = {1,5,3,4,3,4,1,2,3,4,6,2};
	//int Array[] = { 1,5,9,7,3,4,3,4,1,2,3,4,6,2,20 };
	int Array[] = {3,2,1};
	int cnt = sizeof(Array) / sizeof(int);
	vector<int> A(Array, Array + cnt);
	int ret = solution(A);
	
    return 0;
}

