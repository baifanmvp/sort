#include <stdio.h>
#include "sort.h"
/* static void swap(KEY_T* a, int i, int j) */
/* { */
/*     if(j==i)return; */
/*     a[i] += a[j]; */
/*     a[j] = a[i] - a[j]; */
/*     a[i] = a[i] - a[j]; */
/* } */


static void swap(KEY_T* a, int i, int j)
{
    if(j==i)return;
    long temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


static void vecswap(KEY_T* x, int a, int b, int n)
{
    int i ;
    for (i = 0; i < n; i++, a++, b++)
        swap(x, a, b);
}
static int med3(KEY_T* x, int a, int b, int c)
{
    return x[a] < x[b] ? (x[b] < x[c] ? b : x[a] < x[c] ? c : a)
        : x[b] > x[c] ? b : x[a] > x[c] ? c : a;
}



void superqsort(KEY_T* x, int p, int r)
{
    if (p >= r)
        return;

//在数组大小小于7的情况下使用快速排序
    if(r - p + 1 < 7)
    {
        int i;
        for (i = p; i <= r; i++)
        {
            int j;
            for (j = i; j > p && x[j - 1] > x[j]; j--) {
                swap(x, j, j - 1);
            }
        }
        return;
    }

    // 选择中数，与qsort6相同。
    int len = r - p + 1;
    int m = p + (len >> 1);
    if (len > 7) {
        int l = p;
        int n = p + len - 1;
        if (len > 40) {
            int s = len / 8;
            l = med3(x, l, l + s, l + 2 * s);
            m = med3(x, m - s, m, m + s);
            n = med3(x, n - 2 * s, n - s, n);
        }
        m = med3(x, l, m, n);
    }

    int v = x[m];

    // a,b进行左端扫描，c,d进行右端扫描
    int a = p, b = a, c = p + len - 1, d = c;
    while (1) {
        // 尝试找到大于pivot的元素
        while (b <= c && x[b] <= v) {
            // 与pivot相同的交换到左端
            if (x[b] == v)
                swap(x, a++, b);
            b++;
        }
        // 尝试找到小于pivot的元素
        while (c >= b && x[c] >= v) {
            // 与pivot相同的交换到右端
            if (x[c] == v)
                swap(x, c, d--);
            c--;
        }
        if (b > c)
            break;
        // 交换找到的元素
        swap(x, b++, c--);
    }

    // 将相同的元素交换到中间
    int s, n = p + len;
    s = (a - p) < (b - a) ? a - p : b - a;
    vecswap(x, p, b - s, s);
    s = (d - c) < (n - d - 1)? d - c : n - d - 1;
    vecswap(x, b, n - s, s);

    // 递归调用子序列
    if ((s = b - a) > 1)
        superqsort(x, p, s + p - 1);
    if ((s = d - c) > 1)
        superqsort(x, n - s, n - 1);

}

