#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <tuple>

using namespace std;

class FIFO {
public:
    vector<tuple<string, int*, int, int, int>> fifoList;

    void createFIFO(const vector<string>& input) {
        const string& name = input[2];
        for (const auto& [fifoName, _, __, ___, ____] : fifoList) {
            if (fifoName == name) {
                cout << "Error! this name is already exist." << endl;
                return;
            }
        }
        int size = stoi(input[5]);
        int* buffer = new int[size]();
        fifoList.emplace_back(name, buffer, -1, -1, size);
        cout << "FIFO " << name << " created." << endl;
    }

    void deleteFIFO(const vector<string>& input) {
        const string& name = input[2];
        for (size_t i = 0; i < fifoList.size(); ++i) {
            if (get<0>(fifoList[i]) == name) {
                delete[] get<1>(fifoList[i]);
                fifoList.erase(fifoList.begin() + i);
                cout << "FIFO " << name << " deleted." << endl;
                return;
            }
        }
        cout << "FIFO doesn't exist." << endl;
    }

    void addNumber(const vector<string>& input) {
        const string& name = input[4];
        int value = stoi(input[1]);

        for (auto& fifo : fifoList) {
            auto& [fifoName, buffer, front, rear, capacity] = fifo;
            if (fifoName == name) {
                if (front == -1 && rear == -1) {
                    buffer[0] = value;
                    front = rear = 0;
                    cout << value << " added successfully!" << endl;
                    return;
                }
                if ((front == rear + 1) || (front == 0 && rear == capacity - 1)) {
                    cout << "FIFO " << name << " is full." << endl;
                    return;
                }
                rear = (rear + 1) % capacity;
                buffer[rear] = value;
                cout << value << " added successfully!" << endl;
                return;
            }
        }
        cout << "FIFO doesn't exist." << endl;
    }

    void deleteNumber(const vector<string>& input) {
        const string& name = input[3];

        for (auto& fifo : fifoList) {
            auto& [fifoName, buffer, front, rear, capacity] = fifo;
            if (fifoName == name) {
                if (front == -1 && rear == -1) {
                    cout << "FIFO " << name << " is empty." << endl;
                    return;
                }

                cout << buffer[front] << endl;

                if (front == rear) {
                    front = rear = -1;
                } else {
                    front = (front + 1) % capacity;
                }
                return;
            }
        }
        cout << "FIFO doesn't exist." << endl;
    }

    void printIndex(const vector<string>& input) {
        const string& name = input[4];
        int index = stoi(input[1]);

        for (const auto& [fifoName, buffer, _, __, ___] : fifoList) {
            if (fifoName == name) {
                cout << buffer[index] << endl;
                return;
            }
        }
        cout << "FIFO doesn't exist." << endl;
    }
};


int main() {
    FIFO manager;
    string line;

    while (true) {
        getline(cin, line);
        if (line == "end") break;

        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token)
            tokens.push_back(token);

        if (tokens.empty())
            continue;
        //create FIFO <name> with size <n>
        if (tokens[0] == "create") {
            manager.createFIFO(tokens);
        }
        //push <number> to FIFO <name>
        else if (tokens[0] == "push") {
            manager.addNumber(tokens);
        }
        //pop from FIFO <name>
        else if (tokens[0] == "pop") {
            manager.deleteNumber(tokens);
        }
        //delete FIFO <name>
        else if (tokens[0] == "delete") {
            manager.deleteFIFO(tokens);
        }
        //print 2 from FIFO A
        else if (tokens[0] == "print") {
            manager.printIndex(tokens);
        }
    }

    return 0;
}
