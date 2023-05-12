#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
vector<string> teamNameWithId = {"no", "a", "b", "c", "d", "e", "f"};
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
        this->roundDate = roundDate;
        if (state == 'H')
            homeTeamWins = 1;
        else if (state == 'A')
            awayTeamWins = 1;
    }
};
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

void solve()
{
    int n;
    Round r1 = Round(1, 1, 2, 2, 1, "2022/8/5", 'H'); // a wins b lose
    Round r2 = Round(1, 3, 4, 2, 2, "2022/8/6", 'D'); // draw c d
    Round r3 = Round(1, 1, 3, 1, 4, "2022/8/7", 'A'); // c wins a lose
    Round r4 = Round(1, 2, 4, 5, 3, "2022/8/8", 'H'); // b wins d lose
    vector<Round> v = {r1, r2, r3, r4};
    Solution sol(4, v, 0, "2022/8/8");
    auto stand = sol.generateStanding();
    for (int i = 1; i < stand.size(); i++)
    {
        auto it = stand[i];
        cout << i << "   " << it.teamName << " " << it.win << " " << it.draw << " " << it.loss << endl;
    }
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
