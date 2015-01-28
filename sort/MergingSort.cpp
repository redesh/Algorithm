
/*
�鲢����
�㷨˼�룺�鲢�����ǽ����������������ϣ������ϲ���һ���µ������
���Ѵ��������з�Ϊ���ɸ������У�ÿ��������������ġ�Ȼ���ٰ����������кϲ�Ϊ�����������С�
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
	 free(temp);   //��ʱ�ͷ�
}       
      
 void MergeSort(T array[], int low, int high)      
 {      
     if (low  < high)      
     {      
         int mid = low + (high - low) / 2;   //����      
         MergeSort(array, low, mid);        //��ǰ�벿��    
         MergeSort(array, mid+1, high);      
         Merge(array, low, mid, high);      
     }      
 } 