#include <stdbool.h>

bool parseInt(int* value)
{
	return (scanf(" %d", value) == 1 && getchar() == '\n');
}

void clearBuffer(void)
{
	while (getchar() != '\n');
}
