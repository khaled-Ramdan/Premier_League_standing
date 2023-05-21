#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
vector<string> teamNameWithId;
map<string, int> idForTeamName;
string round_num_str, date, home_team, away_team, home_goals_str, away_goals_str, result;
char date_str[10];
int numberOfteams;
bool isEarlierDate(const std::string &date1, const std::string &date2);
string outputfile, outpath;
void gotoxy(short a, short b); // function declaration
class Round
{
public:
    int homeTeamId, awayTeamId, roundNumber, homeTeamGaols, awayTeamGoals;
    string roundDate;
    bool homeTeamWins = 0, awayTeamWins = 0;
    Round(int roundNumber, int homeTeamId, int awayTeamId, int homeTeamGaols, int awayTeamGoals, string roundDate, char state)
    {
        this->roundNumber = roundNumber;
        this->homeTeamId = homeTeamId;
        this->awayTeamId = awayTeamId;
        this->homeTeamGaols = homeTeamGaols;
        this->awayTeamGoals = awayTeamGoals;
        this->roundDate = date;
        if (state == 'H')
            homeTeamWins = 1;
        else if (state == 'A')
            awayTeamWins = 1;
    }
};
bool isValidDate(const std::string &date)
{
    // Check if the string has the correct format "dd/mm/yyyy"
    int cnt = count(date.begin(), date.end(), '/');
    if (cnt != 2)
        return false;
    int day, month, year;
    if (sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
        return false;

    // Check if day, month, and year are within reasonable ranges
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Check for specific month and day ranges
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day > 29)
                return false;
        }
        else
        {
            if (day > 28)
                return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }

    return true;
}

string convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

string Rejust_date(string date_r)
{

    if (date_r[1] == '/' && date_r[3] == '/')
    {
        date_str[0] = '0';
        date_str[1] = date_r[0];
        date_str[2] = '/';
        date_str[3] = '0';
        date_str[4] = date_r[2];
        date_str[5] = '/';
        date_str[6] = date_r[4];
        date_str[7] = date_r[5];
        date_str[8] = date_r[6];
        date_str[9] = date_r[7];
        int date_size = sizeof(date_str) / sizeof(char);
        date_r = convertToString(date_str, date_size);
    }
    else if (date_r[1] == '/' && date_r[3] != '/')
    {
        date_str[0] = '0';
        date_str[1] = date_r[0];
        date_str[2] = '/';
        date_str[3] = date_r[2];
        date_str[4] = date_r[3];
        date_str[5] = '/';
        date_str[6] = date_r[5];
        date_str[7] = date_r[6];
        date_str[8] = date_r[7];
        date_str[9] = date_r[8];
        int date_size = sizeof(date_str) / sizeof(char);
        date_r = convertToString(date_str, date_size);
    }
    else if (date_r[1] != '/' && date_r[4] == '/')
    {
        date_str[0] = date_r[0];
        date_str[1] = date_r[1];
        date_str[2] = '/';
        date_str[3] = '0';
        date_str[4] = date_r[3];
        date_str[5] = '/';
        date_str[6] = date_r[5];
        date_str[7] = date_r[6];
        date_str[8] = date_r[7];
        date_str[9] = date_r[8];
        int date_size = sizeof(date_str) / sizeof(char);
        date_r = convertToString(date_str, date_size);
    }

    return date_r;
}

bool isEarlierDate(const std::string &date1, const std::string &date2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1.c_str(), "%d/%d/%d", &day1, &month1, &year1);
    sscanf(date2.c_str(), "%d/%d/%d", &day2, &month2, &year2);

    if (year1 < year2)
        return true;
    else if (year1 > year2)
        return false;

    if (month1 < month2)
        return true;
    else if (month1 > month2)
        return false;

    if (day1 < day2)
        return true;
    else
        return false;
}

class Team
{
public:
    int teamId, win, draw, loss, goalsFor, goalsAgainst;
    string teamName;
    Team()
    {
        win = draw = loss = goalsFor = goalsAgainst = 0;
    }
    bool operator<(const Team &other) const
    {
        int points = win * 3 + draw;
        int otherPoints = other.win * 3 + other.draw;
        if (points != otherPoints)
            return otherPoints < points;
        int goalDiff = goalsFor - goalsAgainst;
        int otherDiff = other.goalsFor - other.goalsAgainst;
        if (otherDiff != goalDiff)
            return otherDiff < goalDiff;
        if (goalsFor != other.goalsFor)
            return other.goalsFor < goalsFor;
        return goalsAgainst < other.goalsAgainst;
    }
};
class Solution
{
public:
    vector<vector<pair<int, Round>>> leagueGraph;
    vector<bool> visitedTeam;
    int wantedRound;
    string wantedDate;
    vector<Team> answer;
    Solution(int numberOfTeams, vector<Round> leageRounds, int wantedRound = 0, string wantedDate = "")
    {
        this->wantedRound = wantedRound;
        this->wantedDate = wantedDate;
        answer.resize(numberOfTeams + 1); // 21 [0 1 20]
        visitedTeam.resize(numberOfTeams + 1);
        leagueGraph.resize(numberOfTeams + 1);
        for (Round round : leageRounds)
            leagueGraph[round.homeTeamId].push_back({round.awayTeamId, round});

        dfs(1);
    }
    void dfs(int teamId)
    {
        visitedTeam[teamId] = true;
        for (auto &match : leagueGraph[teamId])
        {
            calculate(match.second, teamId, match.first);
            if (!visitedTeam[match.first])
                dfs(match.first);
        }
    }
    void calculate(Round round, int homeTeamId, int awayTeamId)
    {
        if (wantedRound and round.roundNumber > wantedRound) // 17
            return;

        if (!wantedRound and isEarlierDate(wantedDate, round.roundDate))
            return;

        answer[homeTeamId].goalsFor += round.homeTeamGaols; // 2 [1 , 3] ==> [5,2]
        answer[awayTeamId].goalsFor += round.awayTeamGoals;
        answer[homeTeamId].goalsAgainst += round.awayTeamGoals;
        answer[awayTeamId].goalsAgainst += round.homeTeamGaols;
        if (round.homeTeamWins)
        {
            answer[homeTeamId].win++;
            answer[awayTeamId].loss++;
        }
        else if (round.awayTeamWins)
        {
            answer[awayTeamId].win++;
            answer[homeTeamId].loss++;
        }
        else
        {
            answer[homeTeamId].draw++;
            answer[awayTeamId].draw++;
        }
    }
    vector<Team> generateStanding()
    {
        for (int i = 1; i < answer.size(); i++) // int a[20]; [0.. 19]
        {
            answer[i].teamId = i; // pos = 1 => id = 1
            answer[i].teamName = teamNameWithId[i];
        }
        sort(answer.begin() + 1, answer.end());
        return answer;
    }
};

void solve(vector<Round> &rounds, int numOFround, string dateOFmatch = "")
{
    int n;
    Solution sol(numberOfteams, rounds, numOFround, dateOFmatch);
    auto stand = sol.generateStanding();
    // output file
    ofstream outputFile;
    outpath += "\\";
    outputFile.open(outpath + outputfile + ".csv");
    if (!outputFile.is_open())
    {
        cout << "Error in opening the output file\n";
        cout << "Close the output file if it is open....\n";
        return;
    }
    outputFile << "#"
               << ","
               << "Team"
               << ","
               << "MatchPlayed"
               << ","
               << "W"
               << ","
               << "D"
               << ","
               << "L"
               << ","
               << "Goals For"
               << ","
               << "Goals Against"
               << ","
               << "G Diff"
               << ","
               << "Points"
               << endl;

    system("cls"); // clear terminal
    printf("%-4s", "#");
    printf("%-22s", "Team");
    printf("%19s", "MAPL");
    printf("%5s", "W");
    printf("%5s", "D");
    printf("%5s", "L");
    printf("%15s", "Goals For");
    printf("%15s", "Goals Against");
    printf("%10s", "G Diff");
    printf("%10s", "Points\n");

    for (int i = 1; i < stand.size(); i++)
    {
        auto it = stand[i];
        outputFile << i << ","
                   << it.teamName << ","
                   << (it.win + it.draw + it.loss) << ","
                   << it.win << ","
                   << it.draw << ","
                   << it.loss << ","
                   << it.goalsFor << ","
                   << it.goalsAgainst << ","
                   << it.goalsFor - it.goalsAgainst << ","
                   << it.win * 3 + it.draw
                   << endl;

        printf("%-4d", i);
        printf("%-20s", it.teamName.c_str());
        printf("%20d", it.win + it.draw + it.loss);
        printf("%7d", it.win);
        printf("%4d", it.draw);
        printf("%5d", it.loss);
        printf("%15d", it.goalsFor);
        printf("%15d", it.goalsAgainst);
        printf("%10d", it.goalsFor - it.goalsAgainst);
        printf("%10d\n", it.win * 3 + it.draw);

        // coordy++ ;
    }

    outputFile.close();

    ////
}

void outputpath()
{

    cout << "Enter path of the output file : ";
    getline(cin, outpath);
    return;
}
void outfile()
{

    cout << "Enter output file name : ";
    getline(cin, outputfile);
    return;
}
vector<Round> take_input(string path)
{
    vector<Round> inputRounds;
    // Open the CSV file for reading
    ifstream input_file(path);

    // Check if the file was opened successfully
    if (!input_file.is_open())
    {
        cout << "Error: Unable to open input file";
        exit(1);
    }

    string line;

    // Ignore the first line of the file (header row)
    getline(input_file, line);
    int teamId = 1;
    // Read in each line of the CSV file
    while (getline(input_file, line))
    {
        stringstream ss(line);
        // Parse the data fields from the line
        getline(ss, round_num_str, ',');
        getline(ss, date, ',');
        getline(ss, home_team, ',');
        getline(ss, away_team, ',');
        getline(ss, home_goals_str, ',');
        getline(ss, away_goals_str, ',');
        getline(ss, result, ',');
        int home_goals, away_goals, round_num;
        // Convert the numeric fields to integers

        date = Rejust_date(date);

        try
        {
            round_num = stoi(round_num_str);
            home_goals = stoi(home_goals_str);
            away_goals = stoi(away_goals_str);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Error: Invalid integer value for home goals or away goals in line: " << line << '\n';
            continue;
        }

        // Validate the result field
        if (away_goals > home_goals && result != "A")
        {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        }
        else if (home_goals > away_goals && result != "H")
        {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        }
        else if (home_goals == away_goals && result != "D")
        {
            cout << "Error: Invalid result for " << home_team << " vs. " << away_team << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        }
        else if (!isValidDate(date))
        {
            cout << "Error: Invalid Date-> " << date << ", please correct the data in the CSV file and try again.\n";
            exit(1);
        }
        int homeTeamId = 0, awayTeamId = 0;
        if (idForTeamName[home_team])
            homeTeamId = idForTeamName[home_team];
        else
            homeTeamId = idForTeamName[home_team] = teamId++;

        if (idForTeamName[away_team])
            awayTeamId = idForTeamName[away_team];
        else
            awayTeamId = idForTeamName[away_team] = teamId++;

        Round r = Round(round_num, homeTeamId, awayTeamId, home_goals, away_goals, date, result[0]);
        if (home_goals_str != "-" && away_goals_str != "-" && result != "-")
            inputRounds.push_back(r);
    }
    numberOfteams = idForTeamName.size();
    teamNameWithId.resize(numberOfteams + 1);
    for (auto &it : idForTeamName)
    {
        teamNameWithId[it.second] = it.first;
    }
    return inputRounds;
}

void workwithRound()
{

    string input;
    int number;

    do
    {
        cout << "Please enter a number : " << endl;
        getline(cin, input);

        try
        {
            number = stoi(input);
            string path;
            cout << "Enter path for csv file: ";
            getline(cin, path);
            cout << path << endl;
            auto rounds = take_input(path);
            outputpath();
            while (true)
            {

                if (filesystem::exists(outpath))
                {
                    outfile();
                    solve(rounds, 0, date);
                    break;
                }
                else
                {
                    cout << "wrong path  \n";
                    outputpath();
                }
            }
        }
        catch (invalid_argument)
        {

            cout << "invalid input , please enter a valid number ." << endl;
        }

    } while (true);
}

void workwithDate()
{

    string date;

    do
    {
        // Taking input from user
        cout << "Enter date : ";
        getline(cin, date);

        if (isValidDate(date))
        {
            string path;
            cout << "Enter path for csv file: ";
            getline(cin, path);
            cout << path << endl;
            auto rounds = take_input(path);

            outputpath();
            while (true)
            {

                if (filesystem::exists(outpath))
                {
                    outfile();
                    solve(rounds, 0, date);
                    break;
                }
                else
                {
                    cout << "wrong path  \n";
                    outputpath();
                }
            }
        }

        else
        {
            std::cout << "Invalid date format. Please enter a valid date in DD/MM/YYYY format." << std::endl;
        }

    } while (true);
}

// main menu

void MAIN_MENU()
{

    string input;

    do
    {

        cout << "     Main menu : " << endl;
        cout << "*******************" << endl;
        cout << "1. Work with round " << endl;
        cout << "2. Work with date" << endl;
        cout << "                 " << endl;
        cout << "Enter your choice (1 or 2)" << endl;

        getline(cin, input);

        if (input == "1")
        {
            workwithRound();
            break;
        }
        else if (input == "2")
        {
            workwithDate();
            break;
        }
        else
        {
            cout << "invalid choice,please enter(1 or 2)." << endl;
        }

    } while (true);
}

int main()
{
    MAIN_MENU();
}
