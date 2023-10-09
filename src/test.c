#include <stdio.h>

int main(int argc, char **argv)
{
    int j = 0;
	int i = -1;
	while (i++ < argc - 3)
		j++;
    printf("%d\n", i);
}