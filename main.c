/*
Operational Systems class assignment, part 1. It's kind of a 'hello world' for threads.  */


//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>


//Struct definition
struct thread_data
{
    pthread_t thread;
    int id;
};


//Declaration
int number_of_threads_input();
void *print_thread_info(void *thread_data_pointer);


//Main
int main()
{
    struct thread_data *thread_data_array = NULL;
    int number_of_threads;

    number_of_threads = number_of_threads_input();

    printf("Allocating memory for the threads...");
    thread_data_array = malloc(number_of_threads * sizeof(struct thread_data));

    //Creating threads
    for (int counter = 0; counter < number_of_threads; counter++)
        {
        thread_data_array[counter].id = counter + 1;
        pthread_create(&thread_data_array[counter].thread, NULL, print_thread_info, &thread_data_array[counter]);
        }

    printf("\nBehold! %d thread(s) created!\n\n", number_of_threads);

    //Joining threads
    for (int counter = 0; counter < number_of_threads; counter++)
        {
        pthread_join(thread_data_array[counter].thread, NULL);
        }

    printf("\nAnswering the assignment question:\n\n"
           "The difference between gettid() and the pthread_self() is that, while POSIX thread IDs are opaque, \n"
           "assigned and maintained by the pthread implementation, the thread ID (TID) returned by gettid() is \n"
           "a value similar to a process ID (PID) that is assigned by the kernel. \n\n"
           "Besides, pthread IDs are unique only within the process and for the duration of the thread and can \n"
           "be reused. On the other hand, the kernel TID isn't portable and is unique at that time within the \n"
           "the process and across the system. \n\n");

    printf("\nFreeing memory...\n");
    free(thread_data_array);

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
Prints the name and ID of a given (struct thread_data) pointer.  */
void *print_thread_info(void *thread_data_pointer)
{
    //Type casting
    struct thread_data *current_thread = (struct thread_data *) thread_data_pointer;

    printf("\nI'm THREAD %d and, printing myself, we have %lu\n", current_thread->id, current_thread->thread);
    printf("Using pthread_self, my ID is %lu\n", pthread_self());
    printf("Using gettid(), my ID is %ld\n", syscall( __NR_gettid));
    printf("\n");

    return NULL;
}
