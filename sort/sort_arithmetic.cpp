//============================================================================
// Name        : Sort_c_plus_plus.cpp
// Author      : 
// Version     :
// Copyright   : copyright reserved
// Description : sort arithmetic in C++, Ansi-style
//============================================================================
#include <cstdlib>
#include <iostream>
using namespace std;
/* Define NULL pointer value */
#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

template<class T> void myswap(T &a, T &b) //系统提供了swap 函数
{
	if (a == b)
		return;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

template<class T> int getArrayLen(T& array) {
	return (sizeof(array) / sizeof(array[0])); //若是字符数组需要-1
}

template<class T> int littleThan(T a, T b) {
	return b - a;
}

template<class T> int cmp(const T a, const T b) {
	return a - b;
}

int cmpForQsort(const void *a, const void *b) {
	return *(int *) a > *(int *) b ? 1 : -1; //注意
}
/*
 int cmpForQsort2( const void *a , const void *b )
 {
 return *(double *)a > *(double *)b ? 1 : -1;//注意double float
 }*/

//insert sort
template<class T> void insertSort(T array[], int length, int (*lt)(T, T)) {
	if (array == NULL || length <= 0 || lt == NULL)
		return;
	for (int i = 1; i < length; i++) {
		int cur = array[i];
		if (cur < array[i - 1]) {
			int j = i - 1;
			for (; j >= 0 && lt(cur, array[j]) > 0; j--) {
				array[j + 1] = array[j];
			}
			array[j + 1] = cur;
		}
	}
}

//bubble sort
template<class T> void bubbleSort(T array[], int length, void (*sw)(T &, T &)) {
	if (array == NULL || length <= 0 || sw == NULL)
		return;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				sw(array[j], array[j + 1]);
			}
		}
	}
}

//select sort
template<class T> void selectSort(T array[], int length, void (*sw)(T &, T &)) {
	if (array == NULL || length <= 0 || sw == NULL)
		return;
	for (int i = 0; i < length; i++) {
		int small = array[i];
		for (int j = i; j < length; j++) {
			if (array[j] < small) {
				small = array[j];
				sw(array[j], array[i]);
			}
		}

	}
}

//shell sort
template<class T> void ShellSort(T array[], int length, void (*sw)(T &, T &)) {
	if (array == NULL || length <= 0 || sw == NULL)
		return;
	for (int delta = length / 2; delta > 0; delta /= 2) {
		for (int i = 0; i < delta; i++) {
			for (int j = i + delta; j < length; j += delta) {
				for (int k = j; k > 0; k -= delta) {
					if (array[k] < array[k - 1])
						sw(array[k], array[k - 1]);
				}
			}
		}
	}
}

//quick sort
//(1) one partition
template<class T> int partition(T array[], int low, int high,
		void (*sw)(T &, T &)) {
	if (array == NULL || low < 0 || high < 0 || low > high || sw == NULL)
		return -1;
	int mid = (low + high) / 2;
	sw(array[low], array[mid]);
	T pivotkey = array[low];
	while (low < high) {
		while (low < high && cmp(array[high], pivotkey) >= 0)
			--high;
		array[low] = array[high];
		while (low < high && cmp(pivotkey, array[low]) >= 0)
			++low;
		array[high] = array[low];
	}
	array[low] = pivotkey;
	return low;
}
//(2) 递归
template<class T> void quickSort(T array[], int low, int high,
		void (*sw)(T &, T &)) {
	if (array == NULL || low < 0 || high < 0 || low > high || sw == NULL)
		return;
	if (low < high) {
		int pivot = partition(array, low, high, sw);
		if (pivot < 0)
			return;
		quickSort(array, low, pivot - 1, sw);
		quickSort(array, pivot + 1, high, sw);
	}
}

//merge sort
//(1) merge [low,mid-1] [mid,high]
template<class T> void merge(T array[], T arrayAssist[], int low, int mid,
		int high) {
	if (array == NULL || low < 0 || high < 0 || mid < 0 || low >= mid
			|| mid > high)
		return;
	int i = low;
	int j = mid;
	int k = low;
	for (; i < mid && j <= high; k++) {
		if (cmp(array[i], array[j]) <= 0) {
			arrayAssist[k] = array[i];
			i++;
		} else {
			arrayAssist[k] = array[j];
			j++;
		}
	}
	while (i < mid) {
		arrayAssist[k] = array[i];
		i++;
		k++;
	}

	while (j <= high) {
		arrayAssist[k] = array[j];
		j++;
		k++;
	}

	for (int index = low; index <= high; index++) //数据从辅助空间写回原数据空间
			{
		array[index] = arrayAssist[index];
	}

}
//(2) 递归
template<class T> void mergeSort(T array[], T arrayAssist[], int low,
		int high) {
	if (array == NULL || low < 0 || high < 0 || low > high)
		return;
	if (low < high) {
		int mid = (low + high) / 2 ;
		mergeSort(array, arrayAssist, low, mid - 1);
		mergeSort(array, arrayAssist, mid, high);
		merge(array, arrayAssist, low, mid, high);
	}
}

//test
int main(int argc, char *argv[]) {
	int arrayint[] = { 1, 2, 5, 7, 3 };
	int arrayAssist[5];
//    insertSort(arrayint,5,littleThan);
//    bubbleSort(arrayint,5,myswap);
//	  selectSort(arrayint,5,myswap);
//	  ShellSort(arrayint,5,myswap);
//	  quickSort(arrayint,0,5,myswap);
//	  mergeSort(arrayint,arrayAssist,0,5);
	qsort(arrayint, 5, sizeof(int), cmpForQsort); //call stl 's quickSort 

	for (int i = 0; i < 5; i++) {
		cout << arrayint[i] << " ";
	}
	cout << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}

/*
稳定的排序算法：
    冒泡排序（bubble sort） — O(n2)
　　插入排序 （insertion sort）— O(n2)
　　桶排序（bucket sort）— O(n); 需要 O(k) 额外 记忆体
　　归并排序 （merge sort）— O(n log n); 需要 O(n) 额外记忆体
　　基数排序 （radix sort）— O(n·k); 需要 O(n) 额外记忆体
不稳定的排序算法：
    选择排序 （selection sort）— O(n2)
　  希尔排序 （shell sort）— O(n log n) 如果使用最佳的现在版本
　　堆排序 （heapsort）— O(n log n)
　　快速排序 （quicksort）— O(n log n) 期望时间, O(n2) 最坏情况; 对於大的、乱数串列一般相信是最快的已知排序

一般来说：存在不相邻交换的排序算法是不稳定的，相邻交换的排序算法是稳定的；对于相邻交换的稳定排序算法，通过控制交换条件可以转换成不稳定排序算法；
冒泡、插入、归并和基数排序是稳定的；选择、快速、希尔和堆排序是不稳定的。

ps:桶排序的应用：
海量数据
一年的全国高考考生人数为500 万，分数使用标准分，最低100 ，最高900 ，没有小数，要求对这500 万元素的数组进行排序。
分析：对500W数据排序，如果基于比较的先进排序，平均比较次数为O(5000000*log5000000)≈1.112亿。但是我们发现，这些数据都有特殊的条件： 100=<score<=900。那么我们就可以考虑桶排序这样一个“投机取巧”的办法、让其在毫秒级别就完成500万排序。
方法：创建801(900-100)个桶。将每个考生的分数丢进f(score)=score-100的桶中。这个过程从头到尾遍历一遍数据只需要500W次。然后根据桶号大小依次将桶中数值输出，即可以得到一个有序的序列。而且可以很容易的得到100分有***人，501分有***人。
实际上，桶排序对数据的条件有特殊要求，如果上面的分数不是从100-900，而是从0-2亿，那么分配2亿个桶显然是不可能的。所以桶排序有其局限性，适合元素值集合并不大的情况。
典型应用：
在一个文件中有10G个整数，乱序排列，要求找出中位数。内存限制为2G。只写出思路即可（内存限制为2G意思是可以使用2G空间来运行程序，而不考虑本机上其他软件内存占用情况。） 
关于中位数：数据排序后，位置在最中间的数值。即将数据分成两部分，一部分大于该数值，一部分小于该数值。中位数的位置：当样本数为奇数时，中位数=(N+1)/2 ; 当样本数为偶数时，中位数为N/2与1+N/2的均值（那么10G个数的中位数，就第5G大的数与第5G+1大的数的均值了）。
分析：既然要找中位数，很简单就是排序的想法。那么基于字节的桶排序是一个可行的方法。
思想：将整型的每1byte作为一个关键字，也就是说一个整形可以拆成4个keys，而且最高位的keys越大，整数越大。如果高位keys相同，则比较次高位的keys。整个比较过程类似于字符串的字典序。
第一步:把10G整数每2G读入一次内存，然后一次遍历这536,870,912即（1024*1024*1024）*2 /4个数据。每个数据用位运算">>"取出最高8位(31-24)。这8bits(0-255)最多表示256个桶，那么可以根据8bit的值来确定丢入第几个桶。最后把每个桶写入一个磁盘文件中，同时在内存中统计每个桶内数据的数量NUM[256]。
代价：(1) 10G数据依次读入内存的IO代价(这个是无法避免的，CPU不能直接在磁盘上运算)。(2)在内存中遍历536,870,912个数据，这是一个O(n)的线性时间复杂度。(3)把256个桶写回到256个磁盘文件空间中，这个代价是额外的，也就是多付出一倍的10G数据转移的时间。
第二步：根据内存中256个桶内的数量NUM[256]，计算中位数在第几个桶中。很显然，2,684,354,560个数中位数是第1,342,177,280个。假设前127个桶的数据量相加，发现少于1,342,177,280，把第128个桶数据量加上，大于1,342,177,280。说明，中位数必在磁盘的第128个桶中。而且在这个桶的第1,342,177,280-N(0-127)个数位上。
N(0-127)表示前127个桶的数据量之和。然后把第128个文件中的整数读入内存。(若数据大致是均匀分布的，每个文件的大小估计在10G/256=40M左右，当然也不一定，但是超过2G的可能性很小)。注意，变态的情况下，这个需要读入的第128号文件仍然大于2G，那么整个读入仍然可以按照第一步分批来进行读取。
代价：(1)循环计算255个桶中的数据量累加，需要O(M)的代价，其中m<255。(2)读入一个大概80M左右文件大小的IO代价。
第三步：继续以内存中的某个桶内整数的次高8bit（他们的最高8bit是一样的）进行桶排序(23-16)。过程和第一步相同，也是256个桶。
第四步：一直下去，直到最低字节(7-0bit)的桶排序结束。我相信这个时候完全可以在内存中使用一次快排就可以了。
整个过程的时间复杂度在O(n)的线性级别上(没有任何循环嵌套)。但主要时间消耗在第一步的第二次内存-磁盘数据交换上，即10G数据分255个文件写回磁盘上。一般而言，如果第二步过后，内存可以容纳下存在中位数的某一个文件的话，直接快排就可以了（修改者注：我想，继续桶排序但不写回磁盘，效率会更高？）。[3] 
*/
