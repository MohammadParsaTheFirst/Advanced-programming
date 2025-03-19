#include <iostream>
using namespace std;

int MOD = 100000; // = 1000;
// mergesort idea!
long long count_merge(int *start, int *mid, int *end) {
    int left_size = mid - start + 1;
    int right_size = end - mid;
    int *left = new int[left_size];
    int *right = new int[right_size];
    for (int i = 0; i < left_size; ++i) {
        *(left + i) = *(start + i);
    }
    for (int i = 0; i < right_size; ++i) {
        *(right + i) = *(mid + 1 + i);
    }

    long long inv_count = 0;
    int i = 0, j = 0;
    int *current = start;
    while (i < left_size && j < right_size) {
        if (*(left + i) <= *(right + j)) {
            *current = *(left + i);
            i++;
        } else {
            *current = *(right + j);
            j++;
            inv_count += (left_size - i);
        }
        current++;
    }

    while (i < left_size) {
        *current = *(left + i);
        i++;
        current++;
    }

    while (j < right_size) {
        *current = *(right + j);
        j++;
        current++;
    }
    return inv_count % MOD;
}

//recuursiv
long long sort_count(int *start, int *end) {
    if (start >= end) { ///
        return 0;
    }
    // int left = sort_count(start, mid);
    // int right = sort_count(mid + 1, end);
    // int merge = count_merge(start, mid, end);

    int *mid = start + (end - start) / 2; // int bezaram ?????????
    long long sorted_left = sort_count(start, mid);
    long long sorted_right = sort_count(mid + 1, end);
    long long merge = count_merge(start, mid, end);

    return (sorted_left + sorted_right + merge) % MOD;
}




int main() {
    int size;
    cin >> size;



    //
    int *array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> *(array + i);
    }
    cout << sort_count(array, array + size - 1) << endl;

    return 0;
}
