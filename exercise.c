#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void	*print_prime(void *string)
{
	int i = 0;
	char *k = (char*)string;
	printf("string is %s\n", k);
	return (NULL);
}

int main()
{
	pthread_t t;
	int i;
	char *a = malloc(sizeof(char ) * 6);
	a = "hello";
	// i = 0;
	// while (i < 10)
	// {
		pthread_create(&t, NULL, &print_prime, a);
		// printf("thread %d has started\n", i);
	// 	i++;
	// }
	// i = 0;
	// while (i < 10)
	// {
		pthread_join(t, NULL);
		// printf("thread %d has ended\n", i);
	// 	i++;
	// }
	return (0);
}