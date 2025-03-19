import java.util.Scanner;

public class Main {

    public static void insert(int[] M, int[] N, int num) {
        M[N[0]] = num;
        N[0]++;
    }

    public static void pop(int[] N, int[] M, int index) {
        if (index < 0 || index >= N[0]) {
            System.err.println("Invalid index: " + index);
            return;
        }
        for (int i = index; i < N[0] - 1; i++) {
            M[i] = M[i + 1];
        }
        N[0]--;
    }

    public static void swap(int[] M, int[] N, int index1, int index2) {
        if (index1 < 0 || index1 >= N[0] || index2 < 0 || index2 >= N[0]) {
            System.err.println("Invalid indices: " + index1 + " " + index2);
            return;
        }
        int temp = M[index1];
        M[index1] = M[index2];
        M[index2] = temp;
    }

    public static void print(int N, int[] M) {
        for (int i = 0; i < N; i++) {
            System.out.print(M[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input;
        int N[] = {0}; // To simulate a mutable variable in Java
        int[] M = new int[100];

        while (scanner.hasNextLine()) {
            input = scanner.nextLine();
            if (input.equals("exit")) {
                break;
            }

            String[] commands = input.split(" ");
            String command = commands[0];

            if (command.equals("insert")) {
                int num = Integer.parseInt(commands[1]);
                insert(M, N, num);
            } else if (command.equals("print")) {
                print(N[0], M);
            } else if (command.equals("swap")) {
                int index1 = Integer.parseInt(commands[1]);
                int index2 = Integer.parseInt(commands[2]);
                swap(M, N, index1, index2);
            } else if (command.equals("pop")) {
                int index = Integer.parseInt(commands[1]);
                pop(N, M, index);
            }
        }

        scanner.close();
    }
}
