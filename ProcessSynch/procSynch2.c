#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>



sem_t sem;
pthread_mutex_t mutex;


int numreader = 0;			
int numWrites = 0;				// Global writer
int readerID = 0;				// Global reader

int sleepVal = 10;	
int Counter = 30;

int printWRandoms(int,int,int,int);		//Random # functions (lower, upper, count, return Val)
int printRRandoms(int,int,int,int);
int printSRandoms(int,int,int,int);

void *reader(void *callR)			
{
	int Rnum = 0, delayRub = 500, delayRlb = 100, mod = 1, num = 1;
	double readerDelay, sleepValDelay;



	Rnum = printRRandoms(delayRlb, delayRub, mod, num);
	readerDelay = Rnum * .01;



			pthread_mutex_lock(&mutex);


				readerID++;
				
				numreader++;

				if((numreader == 1) || (numreader > 1))
				{
							 
					printf("Reader ID: %ld in CS reading sleepVal: %d\n",pthread_self(), sleepVal);		// Safetly read sleep val in CS
				}

			pthread_mutex_unlock(&mutex);								// Release the mutex lock


				//printf("Reader ID: %d delay set to (100-500): %f\n", readerID, readerDelay);	// Reader delay 100 - 500 
				sleep(readerDelay);


			pthread_mutex_lock(&mutex);								// Aquire the mutex lock

			   // numreader--;

				if(numreader == 0)
				{
					numreader--;
														// # of readers leaves CS
				}

			pthread_mutex_unlock(&mutex);								// Release the mutex lock

			sleepValDelay = sleepVal * .01;

			//printf("sleepVal delay reader: %f\n", sleepValDelay);
			sleep(sleepValDelay);									// Reader sleeps for sleepVal(milli)

}


void *writer(void *callW)
{
	int Wnum = 0, Snum = 0, delayWub = 1000, delayWlb = 100, sleepWub = 50, sleepWlb = 10, mod = 1, num = 1;
	double writerDelay, writerConv;

	
	Wnum = printWRandoms(delayWlb, delayWub, mod, num);
	writerDelay = Wnum * .001;

	sleep(writerDelay);								// Writer sleep for Rand
		
	pthread_mutex_lock(&mutex);
											
		Snum = printWRandoms(sleepWlb, sleepWub, mod, num);			// sleepVal modified Random # 10 - 50

		sleepVal = Snum;							// Safetly store and mod sleepVal

		writerConv = sleepVal * .01;

		sleep(writerConv);							// sleep for sleepVal in milliseconds
		printf("Writer id: %ld sleepVal: %d\n", pthread_self(), sleepVal);
		numWrites++;								// increment #'s Writer

	
	pthread_mutex_unlock(&mutex);								
		

}

int main(int argc, char *argv[])
{
	int i, argWriter, argReader;


	time_t end;
	time_t start = time(NULL);
	time_t seconds = 10;

	int Wnum = 0, Snum = 0, delayWub = 1000, delayWlb = 100, mod = 1, num = 1;
	double writerDelay, readerConv;


	end = start + seconds;
	pthread_mutex_init(&mutex, NULL);		// Create the mutex lock

	argWriter = atoi(argv[1]);
	argReader = atoi(argv[2]);

	pthread_t read[argReader], write[argWriter];

	printf("Writer threads Created: %d  Reader threads Created: %d\n\n", argWriter, argReader);

	srand(time(0));
	

		do 
		{



			for(i = 0; i < argReader; i++)
			{
				pthread_create(&read[i], NULL, (void *)reader, NULL);
			}


			for(i = 0; i < argWriter; i++)
			{

				pthread_create(&write[i], NULL, (void *)writer, NULL);
			}
			//sleep(1);
			start = time(NULL);
			//printf("loop time is : %s\n", ctime(&start));
			//Counter++;

		}while(start < end);


	
		printf("Number of writes: %d Number of Reads: %d\n", numWrites, readerID);


		
		for(i = 0; i < argReader; i++)
		{
			pthread_join(read[i], NULL);
		}

		
		for(i = 0; i < argWriter; i++)
		{
			pthread_join(write[i], NULL);
		}

		pthread_mutex_destroy(&mutex);		
		//pthread_exit(NULL);

return 0;

}

int printWRandoms(int lower, int upper, int mod, int num)
{
    int i;
    for (i = 0; i < mod; i++) {
        num = (rand() %
           (upper - lower + 1)) + lower;
       
    }

   return num;
}


int printRRandoms(int lower, int upper, int mod, int num)
{
    int i;
    for (i = 0; i < mod; i++) {
        num = (rand() %
           (upper - lower + 1)) + lower;
       
    }

   return num;
}


int printSRandoms(int lower, int upper, int mod, int num)
{
    int i;
    for (i = 0; i < mod; i++) {
        num = (rand() %
           (upper - lower + 1)) + lower;
       
    }

   return num;
}


