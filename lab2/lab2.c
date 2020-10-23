#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* printLines(void* str) {
	for (int i = 1; i <= 10; ++i) {
		printf("[Thread \"%s\"] Line #%d\n", (char*)str, i);
	}

	return (void*)EXIT_SUCCESS;
}

int main() {
	char* firstThreadName = "1st";
	char* secondThreadName = "2nd";
	pthread_t secondThread;

	if (0 != pthread_create(&secondThread, NULL, &printLines, (void*)secondThreadName)) {
		perror("Couldn't create second thread");
		pthread_exit((void*)EXIT_FAILURE);
	}

	if (0 != pthread_join(secondThread, NULL)) {
		perror("Couldn't join second thread");
		pthread_exit((void*)EXIT_FAILURE);
	}

	printLines((void*)firstThreadName);
	pthread_exit((void*)EXIT_SUCCESS);
}
