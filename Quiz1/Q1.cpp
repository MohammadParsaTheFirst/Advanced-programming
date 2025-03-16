
#include <string>
#include <iostream>
#include <vector>

using namespace std;
// 400101204
// M. parsa Dini
bool my_bfs(int i, int j, int index, vector<vector<char>>& grid, string& name) {
    if (index == name.length()) { // naem getting found
        return true;
    }
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != name[index]) {
        return false; //outside of the bloody grid
    }
    char temp = grid[i][j]; //current char
    grid[i][j] = '#';
    bool found = my_bfs(i + 1, j, index + 1, grid, name) ||//R
                 my_bfs(i - 1, j, index + 1, grid, name) || //L
                 my_bfs(i, j + 1, index + 1, grid, name) ||//U
                 my_bfs(i, j - 1, index + 1, grid, name); //D
    grid[i][j] = temp; // my last char
    return found;
}

int main() {
    //handling inputs
    int n, m;
    string name;
    cin >> n >> m;
    cin >> name;

    // worst criteria
    if (name.length() > n * m) {
        cout << "nabood!" << endl;
        return 0;
    }

    vector grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // the alg
    bool name_found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == name[0]) {
                if (my_bfs(i, j, 0, grid, name)){
                    name_found = true;
                    break;
                }
            }
        }
        if (name_found) {
            break;
        }
    }

    if (name_found) {
        cout << "peyda kardam!" << endl;
    } else {
        cout << "nabood!" << endl;
    }

    return 0;
}
