/*
Part of an Operational Systems class assignment. It's kind of a 'hello world' for threads.  */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Declaration
int number_of_threads_input();
void *print_thread_info(void *thread_number_pointer);
void create_thread(void *thread_number_pointer, pthread_t *thread_pointer);


//Main function
int main()
{
    pthread_t *thread_array = NULL;
    void **variable_array = NULL;
    int number_of_threads;

    number_of_threads = number_of_threads_input();

    printf("\nAllocating memory for the threads...\n\n");

    thread_array = malloc(number_of_threads * sizeof(pthread_t));
    variable_array = malloc(number_of_threads * sizeof(void *));

    for (int counter = 0; counter < number_of_threads; counter++)
        {
        //Passing the variable for pthread_create by reference using variable_array.
        variable_array[counter] = &counter;
        create_thread(variable_array[counter], &thread_array[counter]);
        }

    printf("\nFreeing memory...\n");
    free(variable_array);
    free(thread_array);

    return 0;
}


//Definition
/*
Returns user input regarding the number of threads to be created.  */
int number_of_threads_input()
{
    int amount = 0;

    while (amount == 0)
        {
            printf("\nEnter the number of threads to be created:\t");
            scanf("%d", &amount);
            printf("\n");
        }

    return amount;
}


/*
Prints the thread's name and ID.  */
void *print_thread_info(void *thread_number_pointer)
{
    int thread_number = *(int *)thread_number_pointer;
    printf("\nI'm THREAD_%d and my ID is %ld\n", (thread_number + 1), pthread_self());

    return NULL;
}


/*
Creates a new thread .The pointer to that thread is passed as argument.  */
void create_thread(void *thread_number_pointer, pthread_t *thread_pointer)
{
    pthread_create(thread_pointer, NULL, print_thread_info, thread_number_pointer);
    printf("\nThread created!\n");

    pthread_join(*thread_pointer, NULL);
    printf("\nThread terminated!\n\n");
}