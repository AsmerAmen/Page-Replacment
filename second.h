#include<stdio.h>
#include<iostream>

using namespace std;

class PageReplacement{
	private:
		// Variables
		
		int no_pages,no_frames, len_of_seq;
		
		int* p_reference;	// page reference sequence
		int* frame;  // pages in frames
		
		bool hit= false;
		int miss_count=0;
		
		// Functions
		void initialize();
		bool isHit(int);
		int getHitIndex(int);
		void dispPages();
		void dispMissCnt();
		/***********************/
		
		void FIFO();
		void LRU();
		void LFU();
		void MFU();
		void second_chance();
		void Optimal();
			
	public:
		PageReplacement(int, int, int);
		void method();
		
	};
	
	
	
	
	