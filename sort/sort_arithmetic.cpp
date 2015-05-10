//============================================================================
// Name        : Sort_c_plus_plus.cpp
// Author      : 
// Version     :
// Copyright   : copyright reserved
// Description : insert sort and bubble sort in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;

/* Define NULL pointer value */

#ifndef NULL
#define NULL    0
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
		int small = i;
		//选择从i到length-1 之间一个最小的
		for (int j = i; j < length; j++) {
			if (array[j] < array[small]) {
				small = j;
			}
		}
		if(small != i){
			sw(array[small], array[i]);
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
		int mid = (low + high) / 2 + 1;
		mergeSort(array, arrayAssist, low, mid - 1);
		mergeSort(array, arrayAssist, mid, high);
		merge(array, arrayAssist, low, mid, high);
	}
}

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

