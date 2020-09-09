

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

    
float timeFirstFit = 0;																				//Time consumed by the first fit algorithm
float timeBestFit = 0;																				//Time consumed by the best fit algorithm
float timeNextFit = 0;																				//Time consumed by the next fit algorithm
float timeWorstFit = 0;																				//Time consumed by the worst fit algorithm

struct taskStream {     																			//Creating a structure of tasks
        int taskSize;																				//Holds the size allocation request
        int taskDuration;																			//Holds the duration
        int flag;																					//Flag: -1 represents unprocessed, 1 represents processed, 2 represents duration reached 0
        int blockLocation;							
};



void print(int n, struct taskStream process[]){														//Print function used to visualize the memory allocations

    //printf("\nSequence#\tTask Size\tBlock#\tProcess Duration\n");
     
    for (int i = 0; i < n; i++) 
    { 
        //printf(" %d\t\t%d\t\t", i+1, process[i].taskSize);
        
        if (process[i].flag != -1){																	//If the process has been allocated, print out the block it is allocated in			
            //printf("%d", process[i].blockLocation+1);
        } 
        else{																						//If the process has not been allocated, print out X
        
            //printf("X");
             
        }
        
        //printf("\t\t%d", process[i].taskDuration);
        
        //printf("\n"); 
    } 
    
    //printf("\n");

}




void firstFit(int blockSize[], int m, struct taskStream process[], int n){ 							//First fit algorithm
  
  
  	bool processed = false;																			//Boolean variable used to control logic statements
	bool allProcessed = false;																		//Boolean variable used to control logic statements
	
	while (allProcessed == false){																	//Keep going until all tasks have been processed
	
		for (int i = 0; i < n; i++){ 																//For all processes, perform the first fit algorithm
    		
    		allProcessed = true;
    		processed = false;
    	
    		if (process[i].flag == -1){																//Only process if the task's flag is -1
    		
    		 	for (int j = 0; j < m; j++){ 														//For all the blocks in memory
            		
            		if (blockSize[j] >= process[i].taskSize){ 										//If allocation is possible
            			
            			process[i].flag = 1;														//Change the process flag to 1 (representing allocated)								
                		blockSize[j] -= process[i].taskSize;										//Compaction sequence to reduce block size  
                		process[i].blockLocation = j; 												//Update block location in the struct   	
            			processed = true;															//Mark the process as processed
                		break; 
            		}
           	 	
        		}
        	
        		if (processed == false){															//If the process was unable to be allocated
        
        			timeFirstFit++;																	//Increment the time consumed

            		for (int i = 0; i < n; i++){													//For all processes
            	
            			if (process[i].flag == 1){													//If the process has been allocated in memory
            			
            				process[i].taskDuration--;												//Decrement the duration			
            		
            				if (process[i].taskDuration == 0){										//If the duration for the process reaches 0
            		
            					process[i].flag = 2; 												//Update flag to exit flag (2)
            					////printf("A process reached 0 duration! Incrementing block %d from %d to", process[i].blockLocation, blockSize[process[i].blockLocation]);
            					blockSize[process[i].blockLocation] += process[i].taskSize;			//Free up the space taken up in the block
            					////printf(" %d\n", blockSize[process[i].blockLocation]);
            	
            		
            				}
            		
            			}
        
        			}

        		}
        	
    		}
    	
    	
    		for (int i = 0; i < n; i++){															//Checking if all tasks have been processed
    	
    			if (process[i].flag == -1){															//If everything has not been processed, ensure the loop keeps executing
    		
    				allProcessed = false;
    		
    			}
    	
    		}
        
    	} 
	
	} 
	
	int maxTime = -200;
	
	for (int i = 0; i < n; i ++){ 																	//Finding the highest remaining duration in memory
		
		if (process[i].taskDuration > maxTime){
		
			maxTime = process[i].taskDuration;
		
		}
	
	
	}
	
	timeFirstFit += maxTime;																		//Adding highest remaining duration to the time consumed
    
    print(n, process);																				//Printing
    
}



void bestFit(int blockSize[], int m, struct taskStream process[], int n){							//Best fit algoritm 
  
  	bool processed = false;																			//Boolean variable used to control logic statements
  	bool allProcessed = false;																		//Boolean variable used to control logic statements
  	
    while (allProcessed == false){																	//Keep going until all tasks have been processed
    	
    	for (int i=0; i<n; i++){																	//For all processes, perform the best fit algorithm 
    		
    		allProcessed = true;
    		processed = false;
    		
        	int index = -1;																			//Index used to store the "best fit" position
        	
        	if (process[i].flag == -1){																//Only process if the task's flag is -1
        		
        		for (int j=0; j<m; j++){															//For all the blocks in memory
        		 
            		if (blockSize[j] >= process[i].taskSize){										//Find the best index
            		 
            	    	if (index == -1){
            	    	
            	    		index = j;
            	    		
            	    	} 
            
                		else if (blockSize[index] > blockSize[j]){
                		
                			index = j;
                			
                		}
                 	   	
            		} 
        		} 


        		if (index != -1){ 																	//If allocation is possible
            		 
            		blockSize[index] -= process[i].taskSize; 										//Compaction sequence to reduce block size
            		process[i].flag = 1;															//Change the process flag to 1 (representing allocated)		
            		process[i].blockLocation = index;												//Update block location in the struct
            		processed = true;																//Mark the process as processed
        		}
        	
        		if (processed == false){															//If the process was unable to be allocated
        
        			timeBestFit++;																	//Increment the time consumed

            		for (int i = 0; i < n; i++){													//For all processes
            			
            			if (process[i].flag == 1){													//If the process has been allocated in memory
            			
            				process[i].taskDuration--;												//Decrement the duration
            		
            				if (process[i].taskDuration == 0){										//If the duration for the process reaches 0
            		
            					process[i].flag = 2; 												//Update flag to exit flag (2)
            					////printf("A process reached 0 duration! Incrementing block %d from %d to", process[i].blockLocation, blockSize[process[i].blockLocation]);
            					blockSize[process[i].blockLocation] += process[i].taskSize;			//Free up the space taken up in the block
            					////printf(" %d\n", blockSize[process[i].blockLocation]);				
            	
            		
            				}
            		
            			}
        
        			}
        		}	
        	
        	} 
        	
        	
        	
        	for (int i = 0; i < n; i++){															//Checking if everything has been processed
    	
    			if (process[i].flag == -1){															//If everything has not been processed, ensure the loop keeps executing
    		
    				allProcessed = false;
    		
    			}
    	
    		}
          	
        	 
    	}
    	
		
    }
    
	int maxTime = -200;
	
	for (int i = 0; i < n; i ++){																	//Finding the highest remaining duration in memory
		
		if (process[i].taskDuration > maxTime){
		
			maxTime = process[i].taskDuration;
		
		}
	
	
	}
	timeBestFit += maxTime;																			//Adding highest remaining duration to the time consumed
    
    print(n, process);																	//Printing
}



   				  
void nextFit(int blockSize[], int m, struct taskStream process[], int n){							//Next fit algoritm 
																
    int j; 

  	bool processed = false;																			//Boolean variable used to control logic statements
	bool allProcessed = false;																		//Boolean variable used to control logic statements
	
	while (allProcessed == false){																	//Keep going until all tasks have been processed
	
		for (int i = 0; i < n; i++){ 																//For all processes, perform the next fit algorithm
    		
    		allProcessed = true;
    		processed = false;
    	
    		if (process[i].flag == -1){																//Only process if the task's flag is -1
		 	    		
    	      	  j = 0;																			//Reset to the first block is j > m
   		
   				  while (j < m){																	//This ensures the last position is used to place the new task
   		
   					if (blockSize[j] >= process[i].taskSize){										//If allocation is possible
   			
   						blockSize[j] -= process[i].taskSize;										//Compaction sequence to reduce block size
   						process[i].flag = 1;														//Change the process flag to 1 (representing allocated)	
   						process[i].blockLocation = j;												//Update block location in the struct	
   						processed = true;															//Mark the process as processed
   						break;
   				
   			
   					}
   					
   					j++;
   					  
   				 }
   			
        		if (processed == false){															//If the process was unable to be allocated
        
        			timeNextFit++;																	//Increment the time consumed	

            		for (int i = 0; i < n; i++){													//For all processes
            	
            			if (process[i].flag == 1){													//If the process has been allocated in memory
            			
            				process[i].taskDuration--;												//Decrement the duration	
            		
            				if (process[i].taskDuration == 0){										//If the duration for the process reaches 0
            		
            					process[i].flag = 2; 												//Update flag to exit flag (2)
            					////printf("A process reached 0 duration! Incrementing block %d from %d to", process[i].blockLocation, blockSize[process[i].blockLocation]);
            					blockSize[process[i].blockLocation] += process[i].taskSize;			//Free up the space taken up in the block
            					////printf(" %d\n", blockSize[process[i].blockLocation]);		
            	
            				}
            		
            			}
        
        			}

        		}
        	
    		}
    	
    	
    		for (int i = 0; i < n; i++){															//Checking if everything has been processed
    	
    			if (process[i].flag == -1){															//If everything has not been processed, ensure the loop keeps executing
    		
    				allProcessed = false;
    	
    			}
    	
    		}
        
    	} 
	
	}
	
	int maxTime = -200;
	
	for (int i = 0; i < n; i ++){																	//Finding the highest remaining duration in memory
		
		if (process[i].taskDuration > maxTime){
		
			maxTime = process[i].taskDuration;																
		
		}
	
	
	}
	timeNextFit += maxTime;																			//Adding highest remaining duration to the time consumed
    
    print(n, process);																				//Printing
}




void worstFit(int blockSize[], int m, struct taskStream process[], int n){							//Worst fit algoritm 
  
  	bool processed = false;																			//Boolean variable used to control logic statements
  	bool allProcessed = false;																		//Boolean variable used to control logic statements
   
   	while (allProcessed == false){																	//Keep going until all tasks have been processed
   		
   		for (int i=0; i<n; i++){																	//For all processes, perform the worst fit algorithm
    		
    		allProcessed = true;							
    		processed = false;
        	
        	int index = -1;
        	
        	if (process[i].flag == -1){																//Only process if the task's flag is -1
        	
        		for (int j=0; j<m; j++){															//For all the blocks in memory
        			 
            		if (blockSize[j] >= process[i].taskSize){										//Find the worst index
            		 
                		if (index == -1){
                			
                			index = j;
                			
                		} 													
                    		 
                		else if (blockSize[index] < blockSize[j]){
                		
                			index = j; 
                		
                		} 
                    
                    		
            		}
            		 
        		} 
  
        		if (index != -1){ 																  	//If allocation is possible
       		
       				blockSize[index] -= process[i].taskSize; 										//Compaction sequence to reduce block size
            		process[i].flag = 1;															//Change the process flag to 1 (representing allocated)		
            		process[i].blockLocation = index;												//Update block location in the struct	
            		processed = true;																//Mark the process as processed
        		}
        	 
        		if (processed == false){															//If the process was unable to be allocated
        		        
        			timeWorstFit++;																	//Increment the time consumed

            		for (int i = 0; i < n; i++){													//For all processes
            	
            			if (process[i].flag == 1){													//If the process has been allocated in memory
            			
            				process[i].taskDuration--;												//Decrement the duration		
            		
            				if (process[i].taskDuration == 0){										//If the duration for the process reaches 0
            		
            					process[i].flag = 2; 												//Update flag to exit flag (2)
            					////printf("A process reached 0 duration! Incrementing block %d from %d to", process[i].blockLocation, blockSize[process[i].blockLocation]);
            					blockSize[process[i].blockLocation] += process[i].taskSize;			//Free up the space taken up in the block
            					////printf(" %d\n", blockSize[process[i].blockLocation]);				
            	
            				}
            		
            			}
        
        			}
        		}	
        	
        	}
        	
        	for (int i = 0; i < n; i++){															//Checking if everything has been processed
    	
    			if (process[i].flag == -1){															//If everything has not been processed, ensure the loop keeps executing
    		
    				allProcessed = false;

    		
    			}
    	
    		} 
        	
    	}
   	
   	}
	
	int maxTime = -200;
	
	for (int i = 0; i < n; i ++){																	//Finding the highest remaining duration in memory
		
		if (process[i].taskDuration > maxTime){
		
			maxTime = process[i].taskDuration;
		
		}
	
	
	}
	timeWorstFit += maxTime;																		//Adding highest remaining duration to the time consumed
    
    print(n, process);																				//Printing
}



void randomize(struct taskStream arrayTasks[], int blockSize[], int numTasks){		//Function used to generate random task size and task duration


    for (int i = 0; i < numTasks; i++){      														//Filling arrayTasks with random values (1-16)

        int randTaskSize = rand() % ((16 + 1)-1) + 1;       										//Task size random min 1, max 16     
        int randTaskDuration = rand() % ((16 + 1) - 1) + 1;											//Task duration random min 1, max 16
    
        arrayTasks[i].taskSize = randTaskSize;														//Assigning the random task size
        arrayTasks[i].taskDuration = randTaskDuration;												//Assigning the random task duration
        arrayTasks[i].flag = -1;																	//Setting flag to -1 to represent unprocessed
    }
    
    blockSize[0] = 16;																				//Splitting the 52 unit block into 5 units of {16, 16, 16, 8, 2}
    blockSize[1] = 16;
    blockSize[2] = 16;
    blockSize[3] = 8;
    blockSize[4] = 2;

} 


 
int main() 
{ 
	//printf("\n");
	
	for (int i = 0; i < 1; i++){
	int numTasks = 1000;																			//The number of tasks that will be processed
	struct taskStream arrayTasks[1000];    														//Structure array of 1000 tasks
	int blockSize[5]; 																				//Initializing 5 blocks in memory
	
    int m = 5;
    int n = numTasks;
    
    randomize(arrayTasks, blockSize, numTasks);											//Randomizing task stream values
    
  	//printf("\n\n");
    //printf("--------- First Fit Algorithm ---------\n");
    firstFit(blockSize, m, arrayTasks, n);															//Calling the firstFit function
    //printf("\nFirst fit algorithm consumed %f units of time.\n\n", timeFirstFit/numTasks);
    
   
   
    randomize(arrayTasks, blockSize, numTasks);											//Randomizing task stream values
    
    //printf("\n\n");
    //printf("--------- Best Fit Algorithm ---------\n");
    bestFit(blockSize, m, arrayTasks, n);															//Calling the bestFit function
    //printf("\nBest fit algorithm consumed %f units of time.\n\n", timeBestFit/numTasks);
    
    
    randomize(arrayTasks, blockSize, numTasks);											//Randomizing task stream values
    
    //printf("\n\n");
    //printf("--------- Worst Fit Algorithm ---------\n");
    worstFit(blockSize, m, arrayTasks, n);															//Calling the worstFit function
    //printf("\nWorst fit algorithm consumed %f units of time.\n\n", timeWorstFit/numTasks);
    
    randomize(arrayTasks, blockSize, numTasks);											//Randomizing task stream values
    
    //printf("\n\n--------- Next Fit Algorithm ---------\n");
	nextFit(blockSize, m, arrayTasks, n);															//Calling the nextFit function
	//printf("\nNext fit algorithm consumed %f units of time.\n\n", timeNextFit/numTasks);
  
	
	//}
	
	printf("\n\n------------ Final Results ------------\n");										//Displaying the final results
  	printf("\nFirst fit algorithm consumed %0.3f units of time.", timeFirstFit/numTasks);
  	printf("\nBest fit algorithm consumed %0.3f units of time.", timeBestFit/numTasks);
  	printf("\nWorst fit algorithm consumed %0.3f units of time.", timeWorstFit/numTasks);
  	printf("\nNext fit algorithm consumed %0.3f units of time.\n\n", timeNextFit/numTasks);
    
    return 0; 
} 