#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
		assert(argc == 2 && "Must provide one argument");

		char line[10];
		int numbers[2000];
		FILE *fp = fopen(argv[1], "r");

		int i = 0;
		while (fgets(line, 10, fp)) {
				sscanf(line, "%d\n", &numbers[i++]);
		}

		int count = 0;
		for (int j = 0; j < i - 1; j++) {
				if (numbers[j] < numbers[j + 1]) {
						count++;
				}
		}

		printf("Part 1: %d\n", count);

		count = 0;
		for (int j = 0; j < i - 3; j++) {
				if (numbers[j] < numbers[j + 3]) {
						count++;
				}
		}

		printf("Part 2: %d\n", count);

}
