#include<stdio.h>
#include<iostream>
#include<time.h>
#include"second.h"


int main(){
	// variables to pass data from user
	int l=1,p=1,f=1, s=1;
	
	// Ask your for valid values and keep looping if it's invalid.
	do{
		printf("\nPlease enter valid number of frames:");
		scanf("%d", &f);
	}while(f<=0);
	do{
		printf("\nPlease enter valid number of pages:");
		scanf("%d", &p);
	}while(p<=0);
	do{
		printf("\nPlease enter valid length of sequence:");
		scanf("%d", &l);
	}while(l<=0);
	do{
		printf("\nPlease enter valid seed number:");
		scanf("%d", &s);
	}while(s<=0);
	
	// Initialize the Data set
	srand(s);
	PageReplacement rp(p,f, l);
	
	
	while(1)
		rp.method();
	
	
	system("PAUSE");
	return 0;
}