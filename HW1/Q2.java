import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Integer> trainTimes = new ArrayList<>();
        ArrayList<String> trainTypes = new ArrayList<>();

        // Read input data
        while (true) {
            String line = scanner.nextLine();
            if (line.equals("end")) break;

            String[] parts = line.split(" ");
            if (parts.length == 2) {
                try {
                    int num = Integer.parseInt(parts[0]);
                    String type = parts[1];
                    trainTimes.add(num);
                    trainTypes.add(type);
                } catch (NumberFormatException e) {
                    // Ignore invalid input
                }
            }
        }

        int K = scanner.nextInt();
        int T = scanner.nextInt();
        int n = trainTimes.size();

        // Algorithm for finding K consecutive Gold wagons with sum == T
        int sum = 0, count = 0, start = -1;

        for (int i = 0, j = 0; i < n; i++) {
            if (trainTypes.get(i).equals("Gold")) {
                sum += trainTimes.get(i);
                count++;
                if (count > K) {
                    sum -= trainTimes.get(j);
                    j++;
                    count--;
                }
                if (count == K && sum == T) {
                    System.out.println(j + 1);
                    scanner.close();
                    return;
                }
            } else {
                sum = 0;
                count = 0;
                j = i + 1;
            }
        }

        // If no such order is found
        int minSum = Integer.MAX_VALUE, bestStart = -1;
        sum = 0;

        for (int i = 0; i < K; i++) {
            sum += trainTimes.get(i);
        }
        minSum = sum;
        bestStart = 1;

        for (int i = K; i < n; i++) {
            sum += trainTimes.get(i) - trainTimes.get(i - K);
            if (sum < minSum) {
                minSum = sum;
                bestStart = i - K + 2;
            }
        }

        System.out.println(bestStart);
        scanner.close();
    }
}
