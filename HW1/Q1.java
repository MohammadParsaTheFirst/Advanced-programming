import java.util.Scanner;
import java.util.Arrays;

public class Main {
    public static int countDigits(long n) {
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

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();

        int N = countDigits(n);

        int[] digits = new int[N];
        int count = 0;
        while (n > 0) {
            digits[count++] = (int) (n % 10);
            n /= 10;
        }

        Arrays.sort(digits);

        long x = 0;
        for (int i = 0; i < count; i++) {
            x = x * 10 + digits[count - i - 1];
        }

        int minNonZero = 9;
        int minIndex = -1;
        for (int i = 0; i < count; i++) {
            if (digits[i] != 0 && digits[i] < minNonZero) {
                minNonZero = digits[i];
                minIndex = i;
            }
        }

        long y = 0;
        for (int j = 0; j < count; j++) {
            y = y * 10 + digits[j];
        }

        System.out.println(x + y);

        scanner.close();
    }
}
