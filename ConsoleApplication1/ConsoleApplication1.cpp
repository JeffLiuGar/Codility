﻿// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <list>
#include <limits>
#include "myString.h"
//#include <hash_map>
using namespace std;

struct tree {
	int x;
	tree * l;
	tree * r;
};

/*
future lesson treeheight
思路是遍历整个tree，然后中间记录每层的深度level
如果level大于height，就记录height
用引用的方式每层传递height到下一层

注意：遍历的算法用递归的，如果不用递归怎么写？需要用到stack
*/
void GetTreeHeight(tree * T, int level, int &height)
{

	//int tempLevel = 0;
	if (NULL == T)
	{
		return;
	}
	if (height < level)
		height = level;
	//level++;

	GetTreeHeight(T->l, level + 1, height);

	GetTreeHeight(T->r, level + 1, height);
	return;


}
int solution(tree * T) {
	int level = 0, height = 0;
	GetTreeHeight(T, level, height);
	return height;
}

void TraverseTree(tree * T)
{
	if (NULL == T)
		return;

	TraverseTree(T->l);
	TraverseTree(T->r);


}


//lesson 16 gready algrithom practice, correct
int TieRopes(vector<int> &A, int K)
{
	int size = A.size();

	int i = 0;
	int len = 0;
	int count = 0;

	for (; i < size; i++)
	{
		len += A[i];
		if (len >= K)
		{
			count++;
			len = 0;
		}			
	}

	return count;

}

int bsearch(vector<int> &a, int k)
{

	int left = 0;
	int right = a.size() - 1;

	while (left <= right)
	{
		int mid = (left + right ) / 2;
		if (a[mid] < k)
		{
			left = mid+1;
		}
		else if(a[mid]>k)
		{
			right = mid-1;
		}
		else
			return mid;
	}
	return -1;
}


void QSort(vector<int> &a, int left, int right) {
	int i, j, pivot;

	//这个if有必要，因为是递归调用，有可能后面调用越界
	//递归调用，left和right是整个数组的index，也就是说递归的时候，可能是数组的某个区间
	if (left < right)
	{
		//先随便选一个数作为pivot，比如选第一个数，left这个数
		pivot = a[left];
		i = left;
		j = right;
		while (i < j)
		{
			//循环比较右边的数和pivot，如果数等于或者大于pivot，就把j向左移动，也就是说大的数据就留在原位
			//注意条件里必须有i<j
			while (i < j && a[j] >= pivot)
				j--;
			//循环退出了。因为条件可能是因为i==j退出的，
			//所以要判断一下是不是因为j减小越界了，如果不是的话，那么我们就要把这个a[j]放到左边
			//放完了后把i++，因为这个i已经被放置一个比pivot小的数了，我们就从它后面开始比较，寻找比pivot小的数
			if (i < j)
				a[i++] = a[j];

			//开始循环比较左边的区间，是否比pivot小，如果不小，就停止增加i，
			while (i < j && a[i] <= pivot)
				i++;

			//如果退出了上面的循环，而且不是因为i越界，那么一定是找到了一个比pivot小的数，这时需要把这个数放给右面j停止的位置
			if (i < j)
				a[j--] = a[i];

			//上面的循环一次，最多移动了一个比pivot大的和一个比pivot小的，
			//这个时候如果i<j,那么还要继续循环，直到 i==j,那么也就把整个数组里比pivot小的数据放到了i左边，大的放到了i右边

		}
		//整个数组里比pivot小的数据放到了i左边，大的放到了i右边
		//这样i就应该是pivot，
		a[i] = pivot;

		//然后把i左边的数据进行递归排序
		QSort(a, left, i - 1);
		//然后把i右边的数据进行递归排序
		QSort(a, i + 1, right);

	}

}



void QuickSort(vector<int>&A){

	QSort(A, 0, A.size() - 1);


}

/*
注意vector的reserve并没有实际分配空间
resize分配了，所以reserve后不能直接访问，会出现access violation，需要用resize
*/
vector<int> CyclicRotation(vector<int> &A, int K) {
	// write your code in C++14 (g++ 6.2.0)
	
	//get the array size
	int size = A.size();

	vector<int> ret;
	int shiftTimes =0 ;//only really need to shift so many times, if the K is bigger than size, only need to shift the K % size times

	ret.resize(size);
	
	if (size == 0)
		goto exit;

	if (size == 1)
	{
		ret[0] = A[0];
		goto exit;
	}
	
	shiftTimes = K % size;

	//get the new index of each element then assign it to the new location
	for (int i = 0; i < size; i++)
	{
		int newindex = (i + shiftTimes) % size;
		ret[newindex] = A[i];
	}


exit:
	return ret;
}



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
	while (i*i <= N)//这里要<=N
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
奇数偶数的题，可以考虑xor来做
0与任何数xor都是任何数，不改变值，所以异或loop的初值可以是0
*/
int OddOccurrencesInArray(vector<int> &A) {

	// write your code in C++14 (g++ 6.2.0)
	int x = 0;
	for (vector<int>::iterator iter = A.begin(); iter != A.end(); iter++)
	{
		x ^= *iter;
	}
	return x;


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


//一定要注意临界区，-2147483648 的abs越界了
int AbsDistinct(vector<int> &A){

	int leftPos = 0;
	int rightPos = A.size() - 1;
	int ret = 0;
	int pre = 0;
	int intMin = INT_MIN;

	while (leftPos < rightPos)
	{
		if (INT_MIN == A[leftPos])
		{
			if (pre != INT_MIN)
				ret++;
			pre = INT_MIN;
			leftPos++;
		}
		else if (abs(A[leftPos]) < abs(A[rightPos]))
		{	//需要判断是否是第一次比较，如果是也需要+1，记录
			//需要记录上一次的值，如果一样的话，不能再加ret
			if (pre != A[rightPos] || rightPos == A.size() - 1)
			{
				ret += 1;
				pre = A[rightPos];
			}				
			rightPos--;
		}
		else if (abs(A[leftPos]) > abs(A[rightPos]))
		{
			if (pre != A[leftPos] || leftPos == 0)
			{
				ret += 1;
				pre = A[leftPos];
			}				
			leftPos++;
		}
		else
		{
			if (A[leftPos] != pre || rightPos == A.size() - 1)
			{
				ret += 1;
				pre = A[leftPos];
			}
			rightPos--;
			leftPos++;
		}		

	}
	if (A[leftPos] != pre || leftPos == 0)
	{
		ret += 1;
	}

	return ret;

}

/*
Lesson 16 Greedy Algrithm
理解错题了，这个很要命，题一定要多读几遍，不要理解错了。
下面这道题全错了
*/
int MaxNonoverlappingSegments(vector<int> &A, vector<int> &B){

	int size = A.size();
	int ret = 0;
	
	if (0 == size || 1 == size)
		return size;
	int leftA = A[size - 1];
	for (int i = size - 1; i > 0; i--)
	{
		if (B[i - 1] < leftA)
		{
			ret++;
			leftA = A[i - 1];
		}
		else
		{
			leftA = min(leftA,min(A[i - 1], A[i]));
		}
	}

	if (ret > 0)
		ret++;
	return ret;


}

typedef struct _test {
	char c;
	short c1;
	int i;
	char c2;

} Test;

#define BIT_MASK(Pos) (0x01<<(pos))

int resetBit(int param, int pos)
{
	if (pos<0 || pos > sizeof(param))
		return 0;
	param &= ~BIT_MASK(pos);
	return 1;
}

void printtest()
{
	int i = 5.0l;
	float f = 5;

	printf("%f ", 5);
	printf("%lf ", 5.0l);
	printf("%02f ", f);
	printf("%d ", i);
	printf("%d ", 5.0l);

}

class testclas
{
public:




};

struct _str {

	void func() {
		printf("ad");
	}
};

typedef struct
{
	int value;
	char type;
}head_t;
typedef struct
{
	head_t head;
	int para;
}message_t;


void test()
{


		message_t *message = NULL;
		head_t *head = NULL;
		message = (message_t *)malloc(sizeof(message_t));
		//assert(message);
		memset(message, 0, sizeof(message_t));
		message->para = 100;
		message->head.type = 'a';
		head = (head_t *)message;
		head->value++;
		head->type++;

		printf("message->head.value= %d, message->head.type = %c, message->para = %d\n",message->head.value, message->head.type, message->para);
		free(message);
		return;



}



void f(char**);

void test2()
{
	const char * argv[] = { "ab" ,"cd" , "ef" ,"gh", "ij" ,"kl" };
	f((char **)argv);
}

void f( char **p)
{
	//char* t;

	//t = ;

	printf("%s", (p += sizeof(int))[-1]);
}

int main()
{
	test2();
	test();
	//struct _str lkk;
	//lkk.func();
	
	//printtest();
	myString str("adgadgg");
	myString str2("adgd");
	myString str3 = str2+str;
	str.printString();
	str2.printString();
	//str = str2;
	//str.printString();
	//myString str3(str2);
	str3.printString();
	//char name[10] = "";
	//const char *str[] = { "adf","adgg","dadkg" };

	//const char **pp = str + 1;


	//char c[66] = "adgdga";
	//int a[5] = {1,2,3,4,5};

	//char *p1 = c;
	//while (*p1++)
	//{
	//	char ccc = *p1;
	//}
	//int *p = (int*)(&a + 1);
	//printf("%d", *(p - 1));
	//Test tt;
	//int adad = sizeof(tt);
	//printf("%08X,%08X,%08X,%08X\n ", &tt.c, &tt.c1, &tt.i, &tt.c2);
	//int Array[] = {1,5,3,4,3,4,1,2,3,4,6,2};
	//int Array[] = { 1,5,9,7,3,4,3,4,1,2,3,4,6,2,20 };
	int ArrayP[] = { 1, 3, 7, 9, 1 };
	//int ArrayQ[] = { -5, -3, -1, 0, 3, 6 };
	int ArrayQ[] = { 5, 6, 8, 9, 10 };
	list<int> list;
	list.assign(ArrayP, ArrayP + 3);
	//int Array[] = {-100,2,4,5};
	int cntP = sizeof(ArrayP) / sizeof(int);
	int cntQ = sizeof(ArrayQ) / sizeof(int);
	vector<int> P(ArrayP, ArrayP + cntP);
	vector<int> Q(ArrayQ, ArrayQ + cntQ);
	//int ret = triangle(A);
	vector<int> ret;
	int N = 4;
	//ret = Shift(P, 3);
	//AbsDistinct(Q);
	int iret = MaxNonoverlappingSegments(P, Q);
    return 0;
}

