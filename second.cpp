#include<stdio.h>
#include<iostream>
#include<time.h>
#include"second.h"

using namespace std;

	/*
	 * Constructor, initialize dataset
	 * @param: p, number of pages
	 * @param: f, number of frames
	 * @param: l, length of sequence
	 * @return: none.
	 */
	PageReplacement::PageReplacement(int p, int f, int l){
		no_pages = p;
		no_frames = f;
		len_of_seq = l;
		
		p_reference = new int[l];
		frame = new int[f]; 
		
		//Filling the page reference sequence with random numbers.
		for(int i=0; i<len_of_seq; i++)
			p_reference[i] = 1 + (rand()%no_pages);
	} /* end of constructor */
	
	/*
	 * Initialize the pages array
	 * @param: void
	 * @return: void
	 */
	void PageReplacement::initialize(){
		miss_count=0;
		for(int i=0; i<no_frames; i++)
			frame[i]=9999;
	} /* end of initialize */
	
	/*
	 * Check if the page already exists in the frames
	 * @param: data, the page number to be checked,
	 * @return: hit, boolean value
	 */
	bool PageReplacement::isHit(int data){
		hit= false;
		for(int j=0; j<no_frames; j++){
			/* if page was found in frames, return true
		      * return false otherwise
			  */
			if(frame[j]==data)
			{
				/*if it was found set hit to true and break of the loop*/
				hit=true;
				break;
			} /* end if */
		} /* end for */
		return hit;
	} /* end of isHit */
	
	/* 
	 * Gets the index of the page that was found in the frames,
	 * in the pages reference sequence.
	 * @param: data, the page number to be checked,
	 * @return: hitind, page caused hit index
	 */
	int PageReplacement::getHitIndex(int data){
		int hitind;
		for(int i=0; i<no_frames; i++){
			/* if page was found in frames, return its index
			 * in the frames array
			  */
			if(frame[i]==data)
			{
				hitind=i;
				break;
			} /* end if */
		} /* end for */
		return hitind;
	} /* end getHitIndex*/

	/* 
	 * prints out the pages present at the frames, each replacement.
	 * @param: void
	 * @return: void
	 */
	void PageReplacement::dispPages()	{
		for (int i=0; i<no_frames; i++)
		{
			// Print out the page number, unless it wasn't changed for initialization.
			if(frame[i]!=9999)
				printf(" %d",frame[i]);
		}
	 
	} /* end dispPages */
	
	/*
	 * Print out the total miss.
	 * @param: void
	 * @return: void
	 */
	void PageReplacement::dispMissCnt(){
		printf("\nTotal no of page miss:%d \n",miss_count);
	}
	
	/*
	 * The user enters number to determine the method they like to use, or exit.
	 * @param: void
	 * @return: void
	 */
	 void PageReplacement::FIFO()
	{
		initialize(); //initialize the frame array.
    
		// loop through all the pages entered.
		for(int i=0; i<len_of_seq; i++)
		{
			int k;
			// print out next page to be entered
			printf("\nFor %d :",p_reference[i]);
				   
			// check if it is already in frame
			if(isHit(p_reference[i])==false)
			{
				for(k=0; k<no_frames-1; k++)	
					frame[k]=frame[k+1];
				 
				frame[k] = p_reference[i];
				
					
				// the page to be inserted is not in a frame
				miss_count++;
				// print out the pages in the frames
				dispPages();
			} /* end if */
			else
				printf("No page fault!"); // Already there.
				 
		} /* end for */
	   dispMissCnt();    //print out the total miss
	}  /* end fifo */
	
	void PageReplacement::LRU()
    {
		   initialize();
		   
		   int least[len_of_seq]; //which page least used
		   
		   for(int i=0; i< len_of_seq; i++) // loop through all the pages entered.
		   {
			  // printf("\nFor %d :",p_reference[i]);
			   cout<<"\nFor"<<"  "<<p_reference[i]<<":";
			   // @edit
			   if(isHit(p_reference[i])==false)  // check if it is already in frame
			   {
				   
				   for(int j=0; j<no_frames; j++)
				   {
					   int pg=frame[j];
					   bool found=false;
					   for(int k=i-1; k>=0; k--)
					   {
						   if(pg==p_reference[k])
						   {
							   least[j]=k;
							   found=true;
							   break;
						   }
						   else
						   found=false;
					   }
					   if(!found)
					   least[j]=-9999;
				   }
				   int min=9999;
				   int repindex;
				   for(int j=0; j<no_frames; j++)
				   {
					   if(least[j]<min)
					   {
						   min=least[j];
						   repindex=j;
					   }
				   }
				  frame[repindex]=p_reference[i];
				   miss_count++;
				   
				   dispPages();
			   }
			   else
			   cout<<"No page fault!";
		   }
		   dispMissCnt(); //print out the total miss
	}
   
	void PageReplacement::LFU()
	{
		int usedcnt[len_of_seq];// shows the page
		int least,repin,sofarcnt=0,bn;
		
		//initialize the frame array.
		initialize();
		// initialize usedbit array with zeros
		for(int i=0; i<no_frames; i++)
			usedcnt[i]=0;
		
		// loop through all the pages entered.
		for(int i=0; i<len_of_seq; i++)
		{
			printf("\n For %d :",p_reference[i]);
			if(isHit(p_reference[i]))
			{
				int hitind=getHitIndex(p_reference[i]);
				usedcnt[hitind]++;
				cout<<"No page fault!";
			}
			else
			{
				miss_count++;	
				if(bn<no_frames)
				{
					frame[bn]=p_reference[i];
					usedcnt[bn]=usedcnt[bn]+1;
					bn++;
				}
				else
				{
					least=9999;
					for(int k=0; k<no_frames; k++)
						if(usedcnt[k]<least)
						{
							least=usedcnt[k];
							repin=k;
						}
					frame[repin]=p_reference[i];
					sofarcnt=0;
					for(int k=0; k<=i; k++)
						if(p_reference[i]==p_reference[k])
							sofarcnt=sofarcnt+1;
					usedcnt[repin]=sofarcnt;
				}
				dispPages();//print out the total miss
			}
		}
		dispMissCnt();
	}
	   /* end lfu */
	   
	
   /*
	 * Simulates the mfu Page Replacement Algorithm on the Data set
	 * @param: void
	 * @return: void
	 */
	   void PageReplacement::MFU()
	{
		int usedcnt[len_of_seq]; // shows the page
		int most,repin,sofarcnt=0,bn;
		
		//initialize the frame array.
		initialize();
		// initialize usedbit array with 9999
		for(int i=0; i<no_frames; i++)
			usedcnt[i]=9999;
		
		// loop through all the pages entered.
		for(int i=0; i<len_of_seq; i++)
		{
				// print out next page to be entered
			printf("\n For %d :",p_reference[i]);
			// check if it is already in frame
			if(isHit(p_reference[i]))
			{
				// get the page index in the pages array
				int hitind=getHitIndex(p_reference[i]);
				usedcnt[hitind]++;
				cout<<"No page fault!"; // Already there.
			}  /* end if */
			else
			{
				miss_count++; // the page to be inserted is not in a frame	
				if(bn<no_frames)
				{
					frame[bn]=p_reference[i];
					usedcnt[bn]=usedcnt[bn]+1;
					bn++;
				}  /* end if */
				else
				{  
					most = -9999;
					for(int k=0; k<no_frames; k++) //The page with maximum frequency is selected
						if(usedcnt[k]>most)
						{
							most =usedcnt[k]; 
							repin=k;
						}
					frame[repin]=p_reference[i];
					sofarcnt=0;
					for(int k=0; k<=i; k++)
						if(p_reference[i]==p_reference[k])
							sofarcnt=sofarcnt+1;
					usedcnt[repin]=sofarcnt;
					
				}  /* end else */
				dispPages(); // print out the pages in the frames
			}
		}  /* end for */
		dispMissCnt(); //print out the total miss
	}
	   /* end mfu */


	
	/*
	 * Simulates the Second Chance Page Replacement Algorithm on the Data set
	 * @param: void
	 * @return: void
	 */
	void PageReplacement::second_chance(){
		int usedbit[len_of_seq];	// shows the page chance
		int victimptr=0;
		
		//initialize the frame array.
		initialize();
		
		// initialize usedbit array with zeros
		for(int i=0; i<no_frames; i++)
			usedbit[i]=0;
		
		// loop through all the pages entered.
		for(int i=0; i<len_of_seq; i++)
		{
			// print out next page to be entered
			printf("\nFor %d:",p_reference[i]);
			// check if it is already in frame
			if(isHit(p_reference[i]))
			{
				printf("No page fault!");		// Already there.
				// get the page index in the pages array
				int hitindex=getHitIndex(p_reference[i]);
				// change the page chance to 1
				if(usedbit[hitindex]==0)
					usedbit[hitindex]=1;
			} /* end if */
			else
			{
				// the page to be inserted is not in a frame
				miss_count++;	
				
				// change the page chance if it's 1
				if(usedbit[victimptr]==1)
				{
					do
					{
						usedbit[victimptr]=0;
						victimptr++;
						if(victimptr==no_frames)
							victimptr=0;
					}while(usedbit[victimptr]!=0);
				} /* end if */
				
				// Replace the page if it's chance is 0
				if(usedbit[victimptr]==0)
				{
					frame[victimptr]=p_reference[i];
					usedbit[victimptr]=1;
					victimptr++;
				} /* end if */
				
				// print out the pages in the frames
				dispPages();
			} /* end else */
			
			if(victimptr==no_frames)
				victimptr=0;
		} /* end for */
		
		//print out the total miss
		dispMissCnt();
	} /* end second chance */
	

	void PageReplacement::Optimal()
	{
		initialize();
		int near [len_of_seq];

		for (int i=0; i<no_pages; i++)
		{
			printf ("\nFor %d :", p_reference[i]);

			if (isHit(p_reference[i])==false)
			{
				for (int j=0; j<no_frames; j++)
				{
					int pg=frame[j];
					int found=0;

					for (int k=i; k<no_pages; k++)
					{
						if (pg==p_reference[k])
						{
							near[j]=k;
							found=1;
							break; 
						} /* end if */
						else
							found=false;
					} /* end for */
					if (!found)
						near[j]=9999;
				} /* end for */

				int max=-9999;
				int repindex;

				for (int j=0; j<no_frames; j++)
				{
					if (near[j]>max)
					{
						max=near[j];
						repindex=j;
					} /* end if */
				} /* end for */
				
				frame[repindex]=p_reference[i];
				miss_count++;
				dispPages();
				
			} /* end if */
			else
				printf("No page fault");
		} /* end for */
		dispMissCnt();
	} /* end Optimal */
	
	/*
	 * The user enters number to determine the method they like to use, or exit.
	 * @param: void
	 * @return: void
	 */
	void PageReplacement::method(){
		int choice;
		
		printf("Enter a number for method, or 0 to exit:\n1 FIFO\n2 LRU\n3 LFU\n4 MFU\n5 Second Chance\n6 Optimum\n");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				FIFO();
				break;
			case 2:
				LRU();
				break;
			case 3:
				LFU();
				break;
			case 4:
				MFU();
				break;
			case 5:
				second_chance();
				break;
			case 6:
				Optimal();
				break;
			default:
				exit(0);
				break;
		}
	} /* end method */