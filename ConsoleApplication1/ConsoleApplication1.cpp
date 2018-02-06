// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
using namespace std;

/*
lesson 11 Sieve of Eratosthenes 素数筛法的笔记。
关键在于建立一个N的临时数组，用于标记每个index上是否可能是素数。比如index 8，就表示数字8，因为2+2+2+2的时候会等于8，所以在循环加的时候index 8肯定会被2的倍数加到，也就是我们会把
index 8上的临时数组的值置为false，表示肯定不是素数。用空间来换时间了。另外，由于因子肯定小于sqrt（N)，所以循环的因子要小于Sqrt（N)，time complexity是O（sqrt（N））

把一个数factorization是拆成素数的乘积，可以上面的方法改造一下，也是一个临时数组，数组记录该index里最小的factor，比如把2的所有倍数的index的value全部填上2， 然后把待拆解的x除以x index
对应的value，得到一个新的x，然后再除以新的x index的value，直到除到一个x的value为0，也就是这个x是素数
*/


//原来下面的简单题也有错，一个是复杂度超标，一个是还有错误
//现在下面的代码没有问题了，用了一个preSum的方法，解决了复杂度的问题，另外一个limit的错误是因为没有i*i<=N，需要==N，包括N
vector<int> CountSemiprimes(int N, vector<int> &P, vector<int> &Q)
{
	vector<int> ret;
	int M = P.size();
	vector<int> factors(N+1, 0);
	vector<int> semiPriCnt(N + 1, 0);
	//先求出1到N的数组里每个数的最小factor并保存，如果本省是素数，那么factor记为0
	int i = 2, j = 2;
	while (i*i <= N)
	{
		j = i;
		while (j <= N)
		{
			if (factors[j] == 0 && j!=i)
				factors[j] = i;
			j += i;
		}
		i++;
	}

	//然后求出1到N里每个数是否是semiPrime，如果是，并且把该index上的前面的semiPrime的和求出来，放入临时数组中
	int semicount =0;
	for (int i = 2; i <= N; i++)
	{
		//if the index i is a semiprimer
		if (factors[i] != 0)
		{
			int x = i / factors[i];
			if (factors[x] == 0)
			{
				semicount++;				
			}			
		}
		semiPriCnt[i] = semicount;		
	}

	//因为只能用O(M)的算法，所以只能有M次循环，所以，每次循环用上面的preSemiPrimeCnt的数据，右下标的index的值减去左下标的值
	//这里要注意，需要判断左边本身是不是一个semiPrime,如果是，需要+1. 判断的方法是看看它的值是否大于它左边的value
	for (int k = 0; k < M; k++)
	{
		int count = 0;
		if (semiPriCnt[P[k]] > semiPriCnt[P[k]-1])
			count = semiPriCnt[Q[k]] - semiPriCnt[P[k]] + 1;
		else
			count = semiPriCnt[Q[k]] - semiPriCnt[P[k]];
		ret.push_back(count);
	}
	


	return ret;

}

///

int Distinct(vector<int> &A) {
	/*ddddad
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
	int ArrayP[] = { 1, 1, 1 };
	int ArrayQ[] = { 4,4,4};
	//int Array[] = {-100,2,4,5};
	int cntP = sizeof(ArrayP) / sizeof(int);
	int cntQ = sizeof(ArrayQ) / sizeof(int);
	vector<int> P(ArrayP, ArrayP + cntP);
	vector<int> Q(ArrayQ, ArrayQ + cntQ);
	//int ret = triangle(A);
	vector<int> ret;
	int N = 4;
	ret = CountSemiprimes(N, P, Q);
	
    return 0;
}

