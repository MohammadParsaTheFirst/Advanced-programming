import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Main {

    public static int maxExperience(int n, int k, List<Integer> a, List<Integer> b) {
        int maxExp = 0;
        int currentExp = 0;
        int maxB = 0;

        for (int t = 0; t < Math.min(n, k); t++) {
            currentExp += a.get(t);
            maxB = Math.max(maxB, b.get(t));
            int remaining = k - (t + 1);
            maxExp = Math.max(maxExp, currentExp + remaining * maxB);
        }

        return maxExp;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int k = scanner.nextInt();
        List<Integer> a = new ArrayList<>();
        List<Integer> b = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            a.add(scanner.nextInt());
        }
        for (int i = 0; i < n; i++) {
            b.add(scanner.nextInt());
        }

        System.out.println(maxExperience(n, k, a, b));

        scanner.close();
    }
}
