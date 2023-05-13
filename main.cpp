#include <bits/stdc++.h>
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
int numberOfteams;
class Round
{
public:
    int homeTeamId, awayTeamId, roundNumber, homeTeamGaols, awayTeamGoals;
    string roundDate;
    bool homeTeamWins = 0, awayTeamWins = 0;
    Round(int roundNumber, int homeTeamId, int awayTeamId, int homeTeamGaols, int awayTeamGoals, string roundDate, char state)
    {
        // stringstream ss;
        // ss << round_num;
        // ss >> roundNumber;
        this->roundNumber = roundNumber;
        this->homeTeamId = homeTeamId;
        this->awayTeamId = awayTeamId;
        // ss << home_goals_str;
        // ss >> homeTeamGaols;
        this->homeTeamGaols = homeTeamGaols;
        // ss << away_goals_str;
        // ss >> awayTeamGoals;
        this->awayTeamGoals = awayTeamGoals;
        this->roundDate = date;
        if (state == 'H')
            homeTeamWins = 1;
        else if (state == 'A')
            awayTeamWins = 1;
    }
    bool operator<(const Round& other) const {
        return isEarlierDate(date, other.roundDate);
    }

    bool operator>(const Round& other) const {
        return other < *this;
    }


};



// TODO: this  is a function that  returns the earlier date, make it a method inside the Round class cuz idk how to do it, thank you!
bool isEarlierDate(const std::string& date1, const std::string& date2) {
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
            return otherDiff < otherDiff;
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

        if (!wantedRound and round.roundDate > wantedDate)
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

void solve(vector<Round> &rounds)
{
    int n;
    // Round r1 = Round(1, 1, 2, 2, 1, "2022/8/5", 'H'); // a wins b lose
    // Round r2 = Round(1, 3, 4, 2, 2, "2022/8/6", 'D'); // draw c d
    // Round r3 = Round(1, 1, 3, 1, 4, "2022/8/7", 'A'); // c wins a lose
    // Round r4 = Round(1, 2, 4, 5, 3, "2022/8/8", 'H'); // b wins d lose
    // vector<Round> v = {r1, r2, r3, r4};
    Solution sol(numberOfteams, rounds, 30);
    auto stand = sol.generateStanding();

    // output file
    ofstream outputFile;
    outputFile.open("outputFile.csv");
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
        cout << i << "   " << it.teamName << " " << it.win << " " << it.draw << " " << it.loss << endl;
    }

    outputFile.close();

    ////
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
int main()
{
    // IO;
    string path;
    cout << "Enter path for csv file: ";
    getline(cin, path);
    cout << path << endl;
    auto rounds = take_input(path);
    solve(rounds);
}
