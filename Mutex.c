//Group members: Ryan Kingsbury | Grayson Marceau | Sascha Rojtas | Luke Noramczyk

/*This project incorporates four threads that are writing the values of two dice that are rolled along with
  there process ID into a file. The mutex funtion only allows for one process to finish before the next. Output 
  of this process can be seen within the file contents*/


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>


FILE *fp;

pthread_mutex_t D_Mutex;

void* thread(void* arg)
{
	

	pthread_mutex_lock (&D_Mutex);

	for (unsigned short Iter = 0; Iter < 2; Iter++)
	{

		//int d1 = rand()%6 + 1;
		//int d2 = rand()%6 + 1;
		//int total = d1 + d2;

			//printf (" %lu %d\n", pthread_self (), total);
			printf ("Semephore Entered CS");
	}

	pthread_mutex_unlock (&D_Mutex);

	return 0;
}

int main ()
{

	pthread_t threadID [4];
	int returnValue;
	srand((unsigned)time(NULL));

	//fp = fopen ("test.txt", "w");
	
		pthread_mutex_init (&D_Mutex, NULL);
	
			/*for (unsigned int Iter = 0; Iter < 4; Iter++)
			{
				if ((returnValue = pthread_create (&threadID [Iter], NULL, Roll,
								    (void*) &threadID [Iter])) != 0)
				{
					printf ("Thread creation error #: %d", returnValue);
				}
			}
	
				for (unsigned int Iter = 0; Iter < 4; Iter++)
			*/


			sem_init(D_Mutex, 0, 1); 
    			pthread_t t1,t2; 
    			pthread_create(&t1,NULL,thread,NULL); 
    			sleep(2); 
    			pthread_create(&t2,NULL,thread,NULL); 
    			pthread_join(t1,NULL); 
    			pthread_join(t2,NULL); 
    			sem_destroy(D_Mutex); 	

			
		//pthread_join (threadID, NULL);

	return(0);
}


