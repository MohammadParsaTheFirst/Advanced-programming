#include <iostream>
#include <algorithm> // For sorting
#include <iostream>
using namespace std;

int countDigits(long long n) {
    if (n == 0) {
        return 1; // Special case: 0 has 1 digit
    }

    int count = 0;
    while (n != 0) {
        n /= 10; // Remove the last digit
        count++; // Increment the count
    }
    return count;
}

int main() {
    long long n;
    cin >> n;

    int N = countDigits(n);

    int digits[N] = {};
    int count = 0;
    while (n > 0) {
        digits[count++] = n % 10;
        n /= 10;
    }

    std::sort(digits, digits + count);


    long long x = 0;
    for (int i = 0; i < count; ++i) {
        x = x * 10 + digits[count -i -1];
    }

    //cout<<digits[0]<<endl;

    int minNonZero = 9;
    int minIndex = -1;
    for (int i = 0; i < count; ++i) {
        //cout<<digits[i];
        if (digits[i] != 0 && digits[i] < minNonZero) {
            minNonZero = digits[i];
            minIndex = i;
        }
    }
    //cout<<endl;

    // if (digits[0]==0) {
    //     //cout<<" nifn"<<endl;
    //     int temp = digits[0];
    //     digits[0] = digits[minIndex];
    //     digits[minIndex] = temp;
    // }


    long long y = 0;
    for (int j = 0; j < count; j++) {
        y = y * 10 + digits[j];
    }

    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    //std::cout << "x + y: " << x + y << std::endl;
    cout<<x+y<<endl;

    return 0;
}
