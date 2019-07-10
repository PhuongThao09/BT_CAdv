#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int i, int j){
	int item;
	item = a[i];
	a[i] = a[j];
	a[j] = item;
}
//3-way
// void sort(int* a, int l, int r){
// 	if(r<=1) return;
// 	int i = l -1 , j = r;
// 	int p = l -1, q = r;
// 	while(1){
// 		while(a[++l] < a[r]);
// 		while (a[r] < a[--j])
// 			if (j == i) break;
// 		if(i >= j) break;
// 		swap(a,i,j);
// 		if(a[i] == a[r]) swap(a, ++p,i);
// 		if(a[j] == a[r]) swap(a, --q,i);
// 	}
// 	swap(a,i,r);
// 	j = i -1;
// 	i = i + 1;
// 	for(int k =1; k <= p; k++) swap(a, k, j--);
// 	for (int k = r - 1; k >= q; k--)
// 	{
// 		swap(a, k, i++);
// 	}
// 	sort(a,l,j);
// 	sort(a,i,r);
// }

//2-way
int partition(int *a, int l, int r){
	int pivot = a[r]; //chon phan tu chot la phan tu cuoi cung cua mang
	int pos = l - 1; // vi tri cua pivot sau khi thuc hien xong ham partition
	for (int i = l; i < r; i++)
	{
		if (a[i] <= pivot) // pivot lon hon a[i]
		{
			pos = pos + 1; 
			swap(a,pos,i);
		}
	}
	swap(a, pos +1,r);
	return pos +1;
}
void quicksort(int *a, int l, int r){
	int j;
	if(l<r){
		j = partition(a,l,r);
		quicksort(a,l,j-1);
		quicksort(a,j+1,r);
	}
}
int main(){
	int a[100];
	int n = 5;
	printf("nhap cac phan tu cua mang: ");
	for(int i = 0; i<n;i++){
		scanf("%d", &a[i]);
	}
	quicksort(a,0, n-1 );
	for (int i = 0; i < n; i++)
	{
		printf("a[%d]= %d\n",i,a[i]);
	}
	return 0;
}
