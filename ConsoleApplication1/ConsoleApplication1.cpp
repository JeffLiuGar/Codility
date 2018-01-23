// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
using namespace std;


int Distinct(vector<int> &A) {
	/*
	用空间换时间，codility似乎不在乎element去年创造出来的固定数组，哪怕是2000000个
	*/
	// write your code in C++14 (g++ 6.2.0)
	int tmpSize = 2000000 + 1;
	
	vector<bool> v(tmpSize, false);
	int size = A.size();
	int ret = 0;
	for (int i = 0; i<size; i++)
	{
		v[A[i] + 1000000] = true;
	}

	for (int i = 0; i<2000001; i++)
	{
		if (v[i])
			ret++;
	}

	return ret;
}

int MaxProfit(vector<int> &A) {
	/*
	关键在于向左遍历的时候，同时知道了前面的最小值 这样就能把当前值减去前面的最小，得到的profit来和保存的maxprofit比较
	*/
	int size = A.size();
	int maxProfit = 0;
	int currentMin = 0;
	if (size < 2)
		return 0;

	currentMin = A[0];
	for (int i = 1; i < size; i++)
	{
		
		int profit = A[i] - currentMin;
		if (profit > maxProfit)
			maxProfit = profit;
		if (A[i] < currentMin)
			currentMin = A[i];
	}

	return maxProfit > 0 ? maxProfit : 0;


}


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


/*
加法的比较可以考虑排序后再加，后面的数肯定比前面的大，如果相邻的两个数相加后不能大于后面相邻的数，那么肯定更靠后的更大不了
Int最大是2,147,483,647,两个数相加如果想要结果等于一个longlong，必须把其中一个强转化为long long后再加
algrithm里有sort，注意使用

*/
int triangle(vector<int> &A)
{
	int size = A.size();
	int ret = 0;
	int minPositive = 0;
	int positiveStart = 0;
	int positiveNums = 0;
	int i = 0;
	int leftSide = 0;
	if (size < 3)
	{
		ret = 0;
		goto exit;
	}

	sort(&A[0], &A[0] + size);
	//std::qsort(&A[0], size, sizeof(int));
	i = 0;
	while (A[i] < 0)
	{
		i++;
	}
	positiveStart = i;
	positiveNums = size - i;

	if (positiveStart >= size-2)
	{
		ret = 0;
		goto exit;
	}


	for (leftSide = positiveStart; leftSide < size - 2; leftSide++)
	{
		long long temp = (long long)A[leftSide] + A[leftSide + 1];
		if (temp > A[leftSide + 2])
			break;
	}
	if (leftSide == size - 2)
		ret = 0;
	else
		ret = 1;
exit:
	return ret;

}

int main()
{
	//int Array[] = {1,5,3,4,3,4,1,2,3,4,6,2};
	//int Array[] = { 1,5,9,7,3,4,3,4,1,2,3,4,6,2,20 };
	int Array[] = {-100,2,4,5};
	int cnt = sizeof(Array) / sizeof(int);
	vector<int> A(Array, Array + cnt);
	int ret = triangle(A);
	
    return 0;
}

