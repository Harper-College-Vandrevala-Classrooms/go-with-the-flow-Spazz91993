#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
using namespace std;

class HeatFlow {
public:
    HeatFlow(double temp, int sections, double K) : temp(temp), sections(sections), K(K) {
        theBar.resize(sections, temp);
    }
    void add_source(int location, double source_temp) {
        if (location >= 1 && location <= sections) {
            int index = location - 1;
            theBar[index] = source_temp;
            sources.insert(index);
        }
    }
    void tick() {
        vector<double> newBar = theBar;
        for (int i = 0; i < sections; i++) {
            if (sources.find(i) != sources.end()) {
                continue;
            }
            if (i == 0) {
                newBar[i] = theBar[i] + K * (theBar[i + 1] - 2 * theBar[i] + theBar[sections - 1]);
            }
            else if (i == sections - 1) {
                newBar[i] = theBar[i] + K * (theBar[0] - 2 * theBar[i] + theBar[i - 1]);
            }
            else {
                newBar[i] = theBar[i] + K * (theBar[i + 1] - 2 * theBar[i] + theBar[i - 1]);
            }
        }
        theBar = newBar;
    }
    void pretty_print() {
        for (double i : theBar) {
            cout << "+------";
        }
        cout << "+" << endl;
        for (double i : theBar) {
            cout << "| " << i << " ";
        }
        cout << "|" << endl;
        for (double i : theBar) {
            cout << "+------";
        }
        cout << "+" << endl;
    }
private:
    double temp;
    int sections;
    double K;
    vector<double> theBar;
    unordered_set<int> sources;
};

int main() {
    double temp, K;
    int sections;
    int numSources, sourceLocation;
    double sourceTemp;
    do {
        cout << "How many sections would you like the bar to be? (positive integer): ";
        cin >> sections;
        if (cin.fail() || sections <= 0) {
            cout << "Invalid input. Please enter a positive integer for sections." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (sections <= 0);
    do {
        cout << "What would you like the starting temperature of the bar to be? (numeric value): ";
        cin >> temp;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a numeric value for temperature." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cin.fail());
    do {
        cout << "What would you like the coefficient of thermal conductivity of the bar to be? (non-negative value): ";
        cin >> K;
        if (cin.fail() || K < 0) {
            cout << "Invalid input. Please enter a non-negative value for the conductivity." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (K < 0);
    HeatFlow object1(temp, sections, K);
    cout << "How many heat sources would you like to add? ";
    cin >> numSources;
    for (int i = 0; i < numSources; ++i) {
        do {
            cout << "Enter the location (1-" << sections << ") and temperature of source " << i + 1 << ": ";
            cin >> sourceLocation >> sourceTemp;
            if (sourceLocation < 1 || sourceLocation > sections) {
                cout << "Invalid location. Please choose a position between 1 and " << sections << "." << endl;
            }
            if (cin.fail()) {
                cout << "Invalid input. Please enter numeric values." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (sourceLocation < 1 || sourceLocation > sections || cin.fail());
        object1.add_source(sourceLocation, sourceTemp);
    }

    object1.pretty_print();

    int ticks;
    cout << "Enter the number of time steps to simulate: ";
    cin >> ticks;
    for (int t = 0; t < ticks; ++t) {
        object1.tick();
        cout << "Time step " << t + 1 << ":" << endl;
        object1.pretty_print();
        cout << "\n\n\n";
    }
    return 0;
}
