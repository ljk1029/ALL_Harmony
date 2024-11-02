#ifndef _MY_SORT_H__
#define _MY_SORT_H__

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

/**
1. 冒泡排序（Bubble Sort）：   适用于小规模的数据排序，实现简单但效率较低。
2. 选择排序（Selection Sort）：适用于小规模的数据排序，也适合于数据基本有序的情况。
3. 插入排序（Insertion Sort）：适用于对小规模或者基本有序的数据进行排序。
4. 希尔排序（Shell Sort）：对插入排序进行了优化，适用于较大规模的数据排序。
5. 归并排序（Merge Sort）：适用于所有规模的数据排序，效率较高，但需要额外的内存空间。
6. 快速排序（Quick Sort）：适用于所有规模的数据排序，平均情况下效率较高。
7. 堆排序（Heap Sort）：   适用于大规模的数据排序，尤其适用于动态数据集。
8. 计数排序（Counting Sort）：适用于非负整数的排序，且数值范围不大。
9. 桶排序（Bucket Sort）：  适用于非负整数的排序，适合于数据分布均匀的情况。
10. 基数排序（Radix Sort）：适用于数字进行排序，可用于字符串排序。
11. 鸡尾酒排序（Cocktail Sort）：适用于需要稳定排序结果和对数据重复值较多的情况。
12. 梳排序（Comb Sort）：      适用于乱序数据的排序，相对于冒泡排序有较好的性能。
13. 混合排序（Tim Sort）：     适用于大规模的数据排序，结合了归并排序和插入排序的特点。
14. 块排序（Bucket Sort）：    适用于大规模数据排序，利用外部存储进行排序。
15. 外部排序（External Sort）：适用于数据量大于内存容量的情况，利用外部存储进行排序。
*/

namespace sort_tool {
/*
1、冒泡:遍历 比较大的交换到后面，每次后面都是排好的（所有数）。
2、插入:先排好前面，每次后面往比前面小交换，直到到前面比他小，前面是排好的（已排索引号前的数）。
3、快排:每次选取一个数据，将所有比它小的数都放到它的左边，所有比它大的数都放到它的右边。
4、选择:对每个下标i,从i后面的元素中选择最小的那个和s[i]交换，前面是排好（所有数）
5、希尔:先按间距n/2 ... 2 1个数据分组进行插入排序（也可以按3k+1个元素这样分组）
6、并归:分别n/2...分组，最小组先排，小组组成大组排序，最后整个排序。
7、堆:  近似完全二叉树，
        (1)最后子节点往上排，最大点在顶点，次最大点在顶点左右子叶中
        (2)最大点放到最后;剩下的点从顶排序，次最大点会移到顶点，顺着次最大所在子叶会重排
        (3)接着2排到最后
        i的子节点2*i+1 / 2*i+2
8、基:  将数据按位数切割成不同的数字，然后按每个位数分别比较排序，先排个，十，百，千，万顺序
*/

// 1、冒泡排序
void bubble_sort(int array[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// 2、插入排序
void insert_sort(int array[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = array[i];
        for (j = i; j > 0 && array[j - 1] > temp; j--) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}

// 3、快速排序
void quick_sort(int array[], int low, int high) {
    if (low >= high) {
        return;
    }
    int first = low;
    int last = high;
    int key = array[first]; /*用字表的第一个记录作为枢轴*/

    while (first < last) {
        while (first < last && array[last] >= key) {
            --last;
        }

        array[first] = array[last]; /*将比第一个小的移到低端*/

        while (first < last && array[first] <= key) {
            ++first;
        }

        array[last] = array[first]; /*将比第一个大的移到高端*/
    }
    array[first] = key; /*枢轴记录到位*/
    quick_sort(array, low, first - 1);
    quick_sort(array, first + 1, high);
}

// 4、选择排序
void select_sort(int array[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i; //查找最小值
        for (j = i + 1; j < n; j++) {
            if (array[min] > array[j])
                min = j; //交换
        }
        if (min != i) {
            temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }
}

//  5、希尔排序
void _shell_sort(int array[], int n, int t) {
    int gap = n;
    while (gap > 1) {
        gap = gap / t + 1;
        int i = 0;
        for (i = 0; i < n - gap; i++) //从0遍历到size-gap-1
        {
            int end = i;
            int temp = array[end + gap];
            while (end >= 0) {
                if (array[end] > temp) {
                    array[end + gap] = array[end];
                    end -= gap;
                } else {
                    break;
                }
            }
            array[end + gap] = temp; //以 end+gap 作为插入位置
        }
    }
}

void shell_sort(int array[], int n, int t) {
    // 初始间隔 h 的选择，通常使用 Knuth 序列
    int h = 1;
    while (h < n / t) {
        h = t * h + 1; // 1, 4, 13, 40, 121, ...
    }

    // 开始希尔排序
    while (h >= 1) {
        // 对每个子序列进行插入排序
        for (int i = h; i < n; i++) {
            // 将 arr[i] 插入到 arr[i-h], arr[i-2*h], arr[i-3*h]... 之中
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                int temp = array[j];
                array[j] = array[j - h];
                array[j - h] = temp;
            }
        }
        // 缩小间隔
        h /= t;
    }
}

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1; // 左半部分的元素个数
    int n2 = right - mid;    // 右半部分的元素个数

    // 创建临时数组
    int L[n1];
    int R[n2];

    // 将数据复制到临时数组 L 和 R 中
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    // 归并临时数组 L 和 R 到 arr
    int i = 0;    // 初始化左半部分的起始索引
    int j = 0;    // 初始化右半部分的起始索引
    int k = left; // 初始化归并后数组的起始索引

    while (i < n1 || j < n2) {
        if (i == n1) {
            array[k] = R[j];
            j++;
        } else if (j == n2) {
            array[k] = L[i];
            i++;
        } else if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
}

// 6、并归排序
void merge_sort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 计算中间点

        // 递归排序左半部分和右半部分
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        // 合并排序后的两部分
        merge(array, left, mid, right);
    }
}

// 调整节点 i，使其符合最大堆性质
void heapify(int array[], int n, int i) {
    int largest = i;       // 假设当前节点 i 是最大值
    int left = 2 * i + 1;  // 左子节点索引
    int right = 2 * i + 2; // 右子节点索引

    // 如果左子节点大于根节点，则更新最大值索引
    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    // 如果右子节点大于根节点，则更新最大值索引
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    // 如果最大值索引不是根节点，则交换根节点和最大值节点，并递归调整子树
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(array, n, largest);
    }
}

// 7、堆排序
void heap_sort(int array[], int n) {
    // 构建最大堆（从最后一个非叶子节点开始）
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    // 逐步将堆顶元素移动到数组末尾，然后调整堆
    for (int i = n - 1; i > 0; i--) {
        // 将当前堆顶元素（最大值）与堆的最后一个元素交换
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // 调整剩余元素为最大堆
        heapify(array, i, 0);
    }
}

// 获取数字的某一位（从右往左，从0开始）
int get_digit(int num, int digit) {
    return (num / static_cast<int>(pow(10, digit))) % 10;
}

// 使用计数排序对数组按照指定的位数进行排序
void counting_sort(int array[], int n, int exp) {
    int output[n] = {0};
    int count[10] = {0}; // 因为数字是0-9，所以创建大小为10的计数数组

    // 计数每个数字出现的次数
    for (int i = 0; i < n; i++) {
        int digit = get_digit(array[i], exp);
        count[digit]++;
    }

    // 将计数数组转换为前缀和数组
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 根据当前位数的值将元素放入输出数组中
    for (int i = n - 1; i >= 0; i--) {
        int digit = get_digit(array[i], exp);
        output[count[digit] - 1] = array[i];
        count[digit]--;
    }

    // 将输出数组复制回原始数组
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

// 8、基排序
void radix_sort(int array[], int n) {
    int max_value = 0;
    for (int i = 0; i < n; i++) {
        if (max_value < array[i])
            max_value = array[i];
    }

    // 对每一位进行计数排序
    for (int exp = 0; max_value / static_cast<int>(pow(10, exp)) > 0; exp++) {
        counting_sort(array, n, exp);
    }
}

// 二分法查找
void dichotomy() {

}

// 排序测试
void print_sort(const int array[], int len) {
    for (int i = 0; i < len; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

int get_rand_num(int start, int end) {
    int t = rand() % (end - start) + start;
    return t;
}

int genrate_sort(int *&array, int n = 0) {
    // 使用当前时间作为随机数生成器的种子
    srand((unsigned)time(NULL));
    n = (n == 0) ? get_rand_num(5, 10) : n;

    /*
    try {
        array = new int[n];
    } catch (const std::bad_alloc& e) {
        std::cerr << "内存分配失败:" << e.what() << std::endl;
        return false;
    }
    */
    array = new (std::nothrow) int[n];
    if (array == nullptr) {
        std::cerr << "内存分配失败" << std::endl;
    }

    std::cout << "n: " << n << std::endl;
    std::cout << "{ ";
    for (int i = 0; i < n; i++) {
        array[i] = get_rand_num(0, n * 2);
        std::cout << array[i];
        if (i != n - 1)
            std::cout << ", ";
        else
            std::cout << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

// mode 0:不检查排序， 1:升序检查 2:降序检查
void print_sort(int array[], int len, int mode = 0) {
    int last = array[0];
    for (int i = 0; i < len; i++) {
        std::cout << array[i] << ' ';
        if (mode == 1 && last > array[i]) {
            std::cout << "非升序组合\n";
        } else if (mode == 2 && last < array[i]) {
            std::cout << "非降序组合\n";
        }
    }
    std::cout << std::endl;
}

}; // namespace sort_tool

#endif