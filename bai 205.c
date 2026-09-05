#include <stdio.h>
int main () {
	int n ;
	printf ("nhập số lương chuỗi :");
	scanf ("%d", &n);
	int a[n];
	printf ( " nhập chuỗi của bạn:/n ");
	for (int i=0; i < n ;i++){
		printf ("%d ",i);
	
		scanf ("%d",&a[i]);
	}
	
	for(int i= 0; i<n; i++){
		printf ( "%d ",a[i]);
	}
	return 0;
}