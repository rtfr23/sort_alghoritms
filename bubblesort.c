#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <inttypes.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void bubblesort(uint32_t *array, int n)
{
    int swapped = 1;
    int i = 0;
    int iter = n - 1;
    do
    {
        swapped = 0;
        i = 0;
        for (; i < iter; i++)
        {
            if (array[i + 1] < array[i])
            {
                swapped = 1;
                swap(&array[i + 1], &array[i]);
            }
        }
        iter--;
    } while (swapped);
}

int main()
{
    int n = 1000000;
    uint32_t *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        array[i] = getrand(0, 100000);
    }
    int j = 1;
    for (int i = 50000; i <= n; i += 50000)
    {
        double time1 = wtime();
        bubblesort(array, i);
        double time2 = wtime();
        printf("\nBubble sort: #%d count: %d time: %.5f", j, i, time2 - time1);
        j++;
    }
    free(array);
    return 0;
}
