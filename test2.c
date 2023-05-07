#include <pthread.h>
#include <stdio.h>

// int counter = 0;

// void *my_thread_func(void *arg) {
//     for (int i = 0; i < 1000; i++) {
//         counter++;
//     }
//     return NULL;
// }

// int main() {
//     pthread_t my_thread1, my_thread2;

//     pthread_create(&my_thread1, NULL, my_thread_func, NULL);
//     pthread_create(&my_thread2, NULL, my_thread_func, NULL);

//     pthread_join(my_thread1, NULL);
//     pthread_join(my_thread2, NULL);

//     printf("Counter value: %d\n", counter);

//     return 0;
// }

#include <stdio.h>
#include <sys/time.h>

int main()
{
	struct timeval	start, end;
	long	elapsed;

	gettimeofday(&start, NULL);
	usleep(10);
	gettimeofday(&end, NULL);
	elapsed
		= (end.tv_usec - start.tv_usec);
	long teet = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	long tet = (end.tv_usec) - (start.tv_usec);
	// printf("Elapsed time: %d microseconds\n", end.tv_usec - start.tv_usec);
	// printf("Elapsed time: %ld microseconds\n", elapsed);
	// printf("Elapsed time: %ld microseconds\n", teet);
	printf("Elapsed time: %ld microseconds\n", tet);
	return (0);
}
