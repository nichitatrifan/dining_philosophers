#define HAVE_STRUCT_TIMESPEC
#define NUM 10

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int phil[NUM];
int phil_state[NUM];
sem_t chopstick[NUM];

void* philosopher(void* philNum)
{
    
    int* numPtr = philNum;
    int actualNum = *numPtr;
    
    while (1)
    {   
        printf("Philosopher %d is hungry\n", actualNum);
        
        sleep(1);

        if (actualNum % 2 == 0)
        {
            printf("Philosopher %d is thinking\n", actualNum);
            sem_wait(&chopstick[actualNum]);
            //printf("Philosopher %d got %d stick\n", actualNum, actualNum);
            sem_wait(&chopstick[(actualNum + 1) % (NUM - 1)]);
            //printf("Philosopher %d got %d stick\n", actualNum, (actualNum + 1) % (NUM - 1));

        }else{

            printf("Philosopher %d is thinking\n", actualNum);
            sem_wait(&chopstick[(actualNum + 1) % (NUM - 1)]);
            //printf("Philosopher %d got %d stick\n", actualNum, (actualNum + 1) % (NUM - 1));
            sem_wait(&chopstick[actualNum]);
            //printf("Philosopher %d got %d stick\n", actualNum, actualNum);
        }
        
        printf("\n--- Philosopher %d eats ---\n\n", actualNum);
        sleep(1); // eating

        if (actualNum % 2 == 0)
        {
            
            sem_post(&chopstick[actualNum]);
            sem_post(&chopstick[(actualNum + 1) % (NUM - 1)]);

        }else{

            sem_post(&chopstick[(actualNum + 1) % (NUM - 1)]);
            sem_post(&chopstick[actualNum]);
        
        }
    
    }
    


}


int main(void)
{       

    /*
     * 
     * This program solves the Dining Philosophers problem, by
     * forcing two adjacent philosophers to compete for the same stick
     * to avoid deadlock situation.
     * 
     * To change the number of philosophers - change the macros 'NUM'
     *
     * */

    pthread_t thread_ID[NUM];
	
    
    // initializing numbering for philosophers
    for(size_t i = 0; i<NUM; i++)
    {
    
        phil[i] = i;
        
    }

    
    // initializing the chopsticks

    for (size_t i = 0; i < NUM; i++)
    {

        sem_init(&chopstick[i], 0, 1);
	
    }
	
        
    // creating threads
    for (size_t i = 0; i < NUM; i++)	
    {

        pthread_create(&thread_ID[i], NULL, philosopher, &phil[i]);
	
    }
        
        
    // starting threads	
    for (size_t i = 0; i < NUM; i++)
	
    {
        pthread_join(thread_ID[i], NULL);
	    
    }

}
