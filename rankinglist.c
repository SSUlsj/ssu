#include<stdio.h>
void main()
{
	short a[]={1,2,3,4,5} // 플레이어 기록으로 채우기
	short i,j,temp;

	for(i=0;i<=4;i++){
		for(j=i+1;j<=4;j++){
			if(a[i]>a[j]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	for(i=0;i<5;i++)printf(" %d",a[i]);
	printf("\n");
}
