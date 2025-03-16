#include <iostream>
#include <sstream>
using namespace std;

void insert(int &N, int* M, int num) {
    *(M + N) = num;
    N++;
}

void pop(int &N, int* M, int index) {
    if (index < 0 || index >= N) {
        cerr << "Invalid index: " << index << endl;
        return;
    }
    for (int i = index; i < N - 1; i++) {
        *(M + i) = *(M + i + 1);
    }
    N--;
}

void swap(int *M, int &N, int index1, int index2) {
    if (index1 < 0 || index1 >= N || index2 < 0 || index2 >= N) {
        cerr << "Invalid indices: " << index1 << " " << index2 << endl;
        return;
    }
    int temp = *(M + index1);
    *(M + index1) = *(M + index2);
    *(M + index2) = temp;
}

void print(int N, int *M) {
    for (int i = 0; i < N; i++) {
        cout << *(M + i) << " ";
    }
    cout << endl;
}

int main() {
    string input;
    int N = 0;
    int *M = new int[100];

    while (getline(cin, input)) {
        if (input == "exit") {
            break;
        }
        istringstream iss(input);
        string command;
        iss >> command;

        if (command == "insert") {
            int num;
            iss >> num;
            insert(N, M, num);
        } else if (command == "print") {
            print(N, M);
        } else if (command == "swap") {
            int index1, index2;
            iss >> index1 >> index2;
            swap(M, N, index1, index2);
        } else if (command == "pop") {
            int index;
            iss >> index;
            pop(N, M, index);
        }
    }
    //delete[] M;
    return 0;
}
