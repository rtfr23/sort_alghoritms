#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
int max(uint32_t *array, int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}
void countingsort(uint32_t *array, int n)
{
    int k = max(array, n);
    int *c = (int *)malloc((k + 1) * sizeof(*array));
    int *sorted = (int *)malloc(n * sizeof(int));
    memset(sorted, 0, n * sizeof(int));
    memset(c, 0, sizeof(*array) * (k + 1));
    for (int i = 0; i < k; i++)
    {
        c[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        c[array[i]] = c[array[i]] + 1;
    }
    for (int i = 1; i <= k; i++)
    {
        c[i] = c[i] + c[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        c[array[i]]--;
        sorted[c[array[i]]] = array[i];
    }
}
// void countingSort2(int *array, int n)
// {
//     int k = max(array, n);
//     int *c = (int *)malloc((k + 1) * sizeof(*array));
//     memset(c, 0, sizeof(*array) * (k + 1));

//     for (int i = 0; i < n; ++i)
//     {
//         ++c[array[i]];
//     }

//     int b = 0;
//     for (int i = 0; i < k + 1; ++i)
//     {
//         for (int j = 0; j < c[i]; ++j)
//         {
//             array[b++] = i;
//         }
//     }
//     free(c);
// }

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
        countingsort(array, i);
        double time2 = wtime();
        // printf("\nCounting sort: #%d count: %d time: %.5f", j, i, time2 - time1);
        printf("%.5f, ", time2 - time1);
        j++;
    }
    free(array);
    return 0;
}
