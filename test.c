#include <pthread.h>
#include <stdio.h>

// pthread_mutex_t my_mutex;

// void *my_thread_func(void *arg) {
// 	pthread_mutex_lock(&my_mutex);
// 	printf("Hello from thread!\n");
// 	pthread_mutex_unlock(&my_mutex);
// 	return arg;
// }

// int main() {
// 	pthread_t my_thread[4];
// 	int i = 0;

// 	pthread_mutex_init(&my_mutex, NULL);
// 	while (i < 4)
// 	{
// 		if(pthread_create(&my_thread[i], NULL, *my_thread_func, NULL) != 0)
// 			return (printf("error"),1);
// 		pthread_detach(my_thread[i]);
// 		i++;        
// 	}
// 	// while (i < 4)
// 	// {
// 	//     if(pthread_join(my_thread[i], NULL) != 0)
// 	//         return (printf("error"),1);
// 	//     i++;        
// 	// }
	
// 	printf("Thread completed\n");

// 	pthread_mutex_destroy(&my_mutex);
// 	return 0;
// }


#include <pthread.h>
#include <stdio.h>

void *my_thread_func(void *arg) {
    int *my_arg = (int *) arg;
    printf("Hello from thread! Argument passed was %d\n", *my_arg);
    pthread_exit(NULL);
}

int main() {
    pthread_t my_thread[5];
    int my_arg = 42;
	int i = 1;
	while(i <= 2)
	{
    	pthread_create(&my_thread[i], NULL, my_thread_func, &my_arg);
		i++;
	}
    // Wait for the thread to complete
	while(i <= 2)
	{
    	pthread_join(my_thread[i], NULL);
		i++;
	}
    printf("Thread completed\n");

    return 0;
}
