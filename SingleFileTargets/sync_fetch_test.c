
#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 100

int gCounter = 0;

void *incCounter(void *p) {
	__sync_fetch_and_add(&gCounter, 1);
	return NULL;
}

int main() {
	pthread_t threads[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++)
		pthread_create(&threads[i], NULL, incCounter, NULL);

	for (int i = 0; i < THREAD_COUNT; i++)
		pthread_join(threads[i], NULL);

	printf("%d\n", gCounter);

	return 0;
}
