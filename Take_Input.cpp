#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // Open the CSV file for reading
    ifstream input_file("games.csv");

    // Check if the file was opened successfully
    if (!input_file.is_open()) {
        cout << "Error: Unable to open input file";
        return 1;
    }

    string line;

    // Ignore the first line of the file (header row)
    getline(input_file, line);


    // Read in each line of the CSV file
    while (getline(input_file, line)){
        stringstream ss(line);
        string round, date, home_team, away_team, home_goals_str, away_goals_str, result;

        // Parse the data fields from the line
        getline(ss, round, ',');
        getline(ss, date, ',');
        getline(ss, home_team, ',');
        getline(ss, away_team, ',');
        getline(ss, home_goals_str, ',');
        getline(ss, away_goals_str, ',');
        getline(ss, result, ',');

        int home_goals, away_goals;

        // Convert the numeric fields to integers
        try {
            home_goals = stoi(home_goals_str);
            away_goals = stoi(away_goals_str);
        } catch (const invalid_argument& e) {
            cerr << "Error: Invalid integer value for home goals or away goals in line: " << line << '\n';
            continue;
        }

        // Validate the result field
        if (away_goals > home_goals && result != "A") {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        } else if (home_goals > away_goals && result != "H") {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        } else if (home_goals == away_goals && result != "D") {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        }

        // Do something with the data, such as printing it out
        cout << round << ", " << date << ", " << home_team << ", " << away_team << ", " << home_goals << "-" << away_goals << ", " << result << endl;
    }

    // Close the input file
    input_file.close();

    return 0;
}
