import java.util.Scanner;

public class Main {

    public static boolean myBFS(int i, int j, int index, char[][] grid, String name) {
        if (index == name.length()) {
            return true; // Name fully matched
        }
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length || grid[i][j] != name.charAt(index)) {
            return false; // Outside grid or character mismatch
        }

        char temp = grid[i][j]; // Current character
        grid[i][j] = '#'; // Mark visited

        boolean found = myBFS(i + 1, j, index + 1, grid, name) || // Down
                        myBFS(i - 1, j, index + 1, grid, name) || // Up
                        myBFS(i, j + 1, index + 1, grid, name) || // Right
                        myBFS(i, j - 1, index + 1, grid, name);  // Left

        grid[i][j] = temp; // Reset cell
        return found;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Handle input
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        scanner.nextLine(); // Consume the newline
        String name = scanner.nextLine();

        // Quick rejection if name length exceeds grid size
        if (name.length() > n * m) {
            System.out.println("nabood!");
            scanner.close();
            return;
        }

        char[][] grid = new char[n][m];
        for (int i = 0; i < n; i++) {
            String line = scanner.nextLine();
            for (int j = 0; j < m; j++) {
                grid[i][j] = line.charAt(j);
            }
        }

        // Algorithm
        boolean nameFound = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == name.charAt(0)) {
                    if (myBFS(i, j, 0, grid, name)) {
                        nameFound = true;
                        break;
                    }
                }
            }
            if (nameFound) {
                break;
            }
        }

        if (nameFound) {
            System.out.println("peyda kardam!");
        } else {
            System.out.println("nabood!");
        }

        scanner.close();
    }
}
