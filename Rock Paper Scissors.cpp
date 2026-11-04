/*
    Project Title : Rock Paper Scissors Game
    Student Name  : Shivam
    Student ID    : 25BCA20007
    Language      : C++
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>

using namespace std;

// Class that handles the game logic
class RockPaperScissors {
private:
    string playerName;
    int playerScore;
    int computerScore;
    int draws;
    int rounds;
    int streak;      // current winning streak
    int bestStreak;  // longest winning streak

    // Convert choice number to its name
    string getMoveName(int move) {
        if (move == 1) return "Rock";
        if (move == 2) return "Paper";
        return "Scissors";
    }

    // Computer picks a random move (1 = Rock, 2 = Paper, 3 = Scissors)
    int getComputerMove() {
        return rand() % 3 + 1;
    }

    // Returns 0 for draw, 1 if player wins, 2 if computer wins
    int findWinner(int player, int computer) {
        if (player == computer) return 0;
        if ((player == 1 && computer == 3) ||
            (player == 2 && computer == 1) ||
            (player == 3 && computer == 2)) {
            return 1;
        }
        return 2;
    }

public:
    // Constructor
    RockPaperScissors(string name) {
        playerName = name;
        playerScore = 0;
        computerScore = 0;
        draws = 0;
        rounds = 0;
        streak = 0;
        bestStreak = 0;
    }

    // Play one round (returns false if input is closed)
    bool playRound() {
        int choice;

        cout << "\n1. Rock\n2. Paper\n3. Scissors\n";

        // Keep asking until the player enters a valid choice
        while (true) {
            cout << "Enter your choice (1-3): ";

            if (!(cin >> choice)) {
                if (cin.eof()) return false;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: Please enter a number.\n";
            } else if (choice < 1 || choice > 3) {
                cout << "Error: Choice must be between 1 and 3.\n";
            } else {
                break;
            }
        }

        int computerChoice = getComputerMove();

        int winner = findWinner(choice, computerChoice);
        rounds++;

        cout << "\n--- Round " << rounds << " ---" << endl;
        cout << playerName << " chose: " << getMoveName(choice) << endl;
        cout << "Computer chose: " << getMoveName(computerChoice) << endl;

        if (winner == 0) {
            draws++;
            cout << "Result: It's a draw! Great minds think alike." << endl;
        } else if (winner == 1) {
            playerScore++;
            streak++;
            if (streak > bestStreak) bestStreak = streak;
            cout << "Result: " << playerName << " wins this round!" << endl;
            if (streak >= 3)
                cout << "You are on fire! " << streak << " wins in a row!" << endl;
        } else {
            computerScore++;
            streak = 0;
            cout << "Result: Computer wins this round!" << endl;
        }

        cout << "Score -> " << playerName << ": " << playerScore
             << " | Computer: " << computerScore << endl;
        return true;
    }

    // Show final scoreboard
    void showResult() {
        double winPercent = 0;
        if (rounds > 0) winPercent = playerScore * 100.0 / rounds;

        cout << fixed << setprecision(1);
        cout << "\n--- FINAL SCOREBOARD ---" << endl;
        cout << "Player Name: " << playerName << endl;
        cout << "Total Rounds: " << rounds << endl;
        cout << "Rounds Won: " << playerScore << endl;
        cout << "Rounds Lost: " << computerScore << endl;
        cout << "Rounds Drawn: " << draws << endl;
        cout << "Best Winning Streak: " << bestStreak << endl;
        cout << "Win Percentage: " << winPercent << "%" << endl;

        if (playerScore > computerScore)
            cout << "Overall Winner: " << playerName << endl;
        else if (computerScore > playerScore)
            cout << "Overall Winner: Computer" << endl;
        else
            cout << "Overall Result: Tie" << endl;

        // Fun rating based on win percentage
        if (rounds > 0) {
            if (winPercent >= 70)      cout << "Rating: Rock Paper Scissors Master!" << endl;
            else if (winPercent >= 40) cout << "Rating: Nice game, well played!" << endl;
            else                       cout << "Rating: Better luck next time!" << endl;
        }
        cout << "-------------------------------" << endl;
    }
};

int main() {
    string name;
    char again;

    srand(time(0));

    cout << "Enter player name: ";
    getline(cin, name);

    RockPaperScissors game(name);

    do {
        if (!game.playRound()) break;

        cout << "\nDo you want to play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    game.showResult();

    return 0;
}
