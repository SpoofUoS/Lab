// Created by Spoof_UoS.
#include <stdio.h>
#include <math.h>

typedef struct fraction {
    int numerator;
    int denominator;
    double value;
}fraction;

fraction arr[1000*1000];

int partition(int low, int high) {
    double pivot = arr[high].value;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].value < pivot) {
            i++;
            fraction temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    fraction temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quicksort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

int gcd(int a, int b)
{
    if(a == 0) return b;
    return gcd(b%a, a);
}

int is_coprime(int a, int b)
{
    if(gcd(a, b) == 1) return 1;
    return 0;
}

void make_array(void)
{
    for(int i=1; i<=1000; i++)
    {
        for(int j=1; j<1000; j++)
        {
            arr[(i - 1) * 1000 + j - 1].numerator = i;
            arr[(i - 1) * 1000 + j - 1].denominator = j;
            arr[(i - 1) * 1000 + j - 1].value = (double) i / (double) j;
        }
    }

    quicksort(0, 1000 * 1000 - 1);

    for(int i=0; i<1000*1000; i++)
    {
        if(!is_coprime(arr[i].numerator, arr[i].denominator))
        {
            arr[i].value = -1;
        }
    }
}
fraction decimal_to_fraction(double n)
{
    make_array();

    for(int i=0; i<1000*1000; i++) {
        double error = fabs(arr[i].value - n) / n * 100;
        if (error < 0.01) {
            printf("\n%lf: %3d / %3d | ", n, arr[i].numerator, arr[i].denominator);
            printf("error: %0.3lf %%", error);
        }
    }
}

int main(void)
{
    double n;
    printf("decimal: ");
    scanf("%lf", &n);
    decimal_to_fraction(n);
    return 0;
}
