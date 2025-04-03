#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

class AirportControl {
private:
    int k;
    unordered_map<string, int> planeStatus;
    vector<string> runways;
    set<int> freeRunways;

public:
    AirportControl(int k) : k(k), runways(k + 1, "") {
        for (int i = 1; i <= k; i++) {
            freeRunways.insert(i);
        }
    }

    void addPlane(const string& id) {
        if (planeStatus.find(id) == planeStatus.end()) {
            planeStatus[id] = 1;
        }
    }

    void takeOff(const string& id) {
        if (planeStatus.find(id) == planeStatus.end() || planeStatus[id] == 4) {
            cout << "YOU ARE NOT HERE" << endl;
            return;
        }
        if (planeStatus[id] == 3) {
            cout << "YOU ARE LANDING NOW" << endl;
            return;
        }
        if (planeStatus[id] == 2) {
            cout << "YOU ARE TAKING OFF" << endl;
            return;
        }
        if (freeRunways.empty()) {
            cout << "NO FREE BAND" << endl;
            return;
        }

        int assignedRunway = *freeRunways.begin();
        freeRunways.erase(assignedRunway);
        runways[assignedRunway] = id;
        planeStatus[id] = 2;
    }

    void land(const string& id) {
        if (planeStatus.find(id) != planeStatus.end() && planeStatus[id] == 1) {
            cout << "YOU ARE HERE" << endl;
            return;
        }
        if (planeStatus.find(id) != planeStatus.end() && planeStatus[id] == 2) {
            cout << "YOU ARE TAKING OFF" << endl;
            return;
        }
        if (planeStatus.find(id) != planeStatus.end() && planeStatus[id] == 3) {
            cout << "YOU ARE LANDING NOW" << endl;
            return;
        }
        if (freeRunways.empty()) {
            cout << "NO FREE BAND" << endl;
            return;
        }
        int assignedRunway = *freeRunways.rbegin();
        freeRunways.erase(assignedRunway);
        runways[assignedRunway] = id;
        planeStatus[id] = 3;
    }

    void planeStatusQuery(const string& id) {
        if (planeStatus.find(id) == planeStatus.end()) {
            cout << 4 << endl;
        } else {
            cout << planeStatus[id] << endl;
        }
    }

    void bandStatus(int runway) {
        if (runways[runway].empty()) {
            cout << "FREE" << endl;
        } else {
            cout << runways[runway] << endl;
        }
    }
};

int main() {
    int k;
    cin >> k;
    //string input; cin >> input;
    cin.ignore();

    AirportControl control(k);
    string line;
    while (getline(cin, line)) {
        if (line == "EXIT") break;

        stringstream ss(line);
        string command, id;
        ss >> command;

        if (command == "ADD-PLANE") {
            ss >> id;
            control.addPlane(id);
        } else if (command == "TAKE-OFF") {
            ss >> id;
            control.takeOff(id);
        } else if (command == "LANDING") {
            ss >> id;
            control.land(id);
        } else if (command == "PLANE-STATUS") {
            ss >> id;
            control.planeStatusQuery(id);
        } else if (command == "BAND-STATUS") {
            int runway;
            ss >> runway;
            control.bandStatus(runway);
        }
    }
    return 0;
}
