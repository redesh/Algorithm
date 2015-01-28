
/*
归并排序
算法思想：归并排序法是将两个（或两个以上）有序表合并成一个新的有序表，
即把待排序序列分为若干个子序列，每个子序列是有序的。然后再把有序子序列合并为整体有序序列。
*/
template <typename T>
void Merge(T *array,int low,int mid,int high)      
 {      
     int i = low;  
     int j = mid + 1;
	 int p = 0;
	 T *temp;
	 temp = (ElemType *)malloc((high-low+1)*sizeof(ElemType));
     if(!temp)
		 return;

	 while(i <= mid && j <= high) {
			temp[p++] = (array[i] <= array[j]) ? array[i++] : array[j++];	
	 }
	 while(i <= mid)      
		 temp[p++] = array[i++];
	 while(j <= high)     
		 temp[p++] = array[j++];
	
	 for(p=0, i=low; i <= high; p++,i++) {
		array[i] = temp[p];
	 }
	 free(temp);   //及时释放
}       
      
 void MergeSort(T array[], int low, int high)      
 {      
     if (low  < high)      
     {      
         int mid = low + (high - low) / 2;   //均分      
         MergeSort(array, low, mid);        //对前半部分    
         MergeSort(array, mid+1, high);      
         Merge(array, low, mid, high);      
     }      
 } 