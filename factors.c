#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* main - Factorize as many numbers as possible into a product of
 * two smaller numbers.
 * @argc: argument count
 * @argv: argument array
 */

int main(int argc, char *argv[])
{
	FILE *fd;
	char *line = NULL;
	size_t len = 0;
	long long flag = 1, div, result, no, count;
	ssize_t nread;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = fopen(argv[1], "r");
	if (fd == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, fd)) != -1) {
		flag = 1, div = 2;
		no = atoll(line);
		while (flag) {
			result = no % div;
			if (!result) {
				count = no / div;
				printf("%lld=%lld*%lld\n", no, count, div);
				flag = 0;
			}
			div++;
		}
	}

	free(line);
	fclose(fd);
	exit(EXIT_SUCCESS);
}
