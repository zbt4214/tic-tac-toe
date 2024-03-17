#include <iostream>
using namespace std;

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player_one_symbol, player_two_symbol, computer_symbol;
string player_one_name, player_two_name;
int player_one_wins = 0, player_two_wins = 0, computer_wins = 0, ties = 0;

void make_board() {
    for (int i = 0; i < 9; ++i) {
        board[i] = '1' + i;
    }
}

void display_board() {
    cout << endl;
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << endl; // Add newline here
}


bool is_valid_move(char move) {
    if (move < '1' || move > '9')
        return false;
    int board_position = move - '1';
    return board[board_position] == move;
}

int check_for_win() {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            if (board[i] == player_one_symbol)
                return 1; // Player one wins
            else if (board[i] == player_two_symbol)
                return 2; // Player two wins
            else if (board[i] == computer_symbol)
                return 3; // Computer wins
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == player_one_symbol)
                return 1; // Player one wins
            else if (board[i] == player_two_symbol)
                return 2; // Player two wins
            else if (board[i] == computer_symbol)
                return 3; // Computer wins
            else
            return 4; // tie
        }
    }

    // Check diagonals
    if ((board[0] == board[4] && board[4] == board[8]) ||
        (board[2] == board[4] && board[4] == board[6])) {
        if (board[4] == player_one_symbol)
            return 1; // Player one wins
        else if (board[4] == player_two_symbol)
            return 2; // Player two wins
        else if (board[4] == computer_symbol)
            return 3; // Computer wins
        else 
        return 4; // tie 
    }

    // Check for tie
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            return 0; // Game is still ongoing
        }
    }
    return 4; // It's a tie
}

void update_scores(int winner) {
    if (winner == 1) {
        player_one_wins++;
    } else if (winner == 2) {
        player_two_wins++;
    } else if (winner == 3) {
        computer_wins++;
    } else if (winner == 4) {
        ties++;
    }
}



void display_scores() {
    cout << "Scores:\n";
    cout << player_one_name << ": " << player_one_wins << "\n";
    if (player_two_name != "")
        cout << player_two_name << ": " << player_two_wins << "\n";
    else
        cout << "Computer: " << computer_wins << "\n";
    cout << "Ties: " << ties << "\n";
}

bool play_again() {
    char choice;
    cout << "Do you want to play again? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

void player_move(string playerName, char playerSymbol) {
    char move;
    bool validMove = false;

    while (!validMove) {
        cout << playerName << "'s turn (" << playerSymbol << "): ";
        cin >> move;

        if (move >= 'a' && move <= 'z')
        {
            move -= 32; // Convert lowercase to uppercase
        }

        validMove = is_valid_move(move);

        if (validMove) 
        {
            int position = move - '1';
            board[position] = playerSymbol;
            display_board(); // Display the board after each player's move
        } else {
            cout << "Invalid move. Please try again." << endl;
        }
    }
}

void computerMove() {
    int position;
    bool validMove = false;

    // Strategic move selection
    for (int i = 0; i < 9; ++i) {
        if (is_valid_move('1' + i)) {
            // Attempt to make a winning move
            board[i] = computer_symbol;
            if (check_for_win() == 3) {
                cout << "Computer's turn:" << endl; // Display computer's move
                return;
            }
            // Block player's winning move
            board[i] = player_one_symbol;
            if (check_for_win() == 1) {
                board[i] = computer_symbol;
                cout << "Computer's turn:" << endl; // Display computer's move
                return;
            }
            board[i] = '1' + i; // Reset the position
        }
    }

    // Center control
    if (is_valid_move('5')) {
        board[4] = computer_symbol;
        cout << "Computer's move:" << endl; // Display computer's move
        return;
    }

    // Fallback to random move
    while (!validMove) {
        position = rand() % 9;
        if (is_valid_move('1' + position)) {
            board[position] = computer_symbol;
            validMove = true;
        }
    }
}

int main() {
    cout << "------------------" << endl;
    cout << "------------------" << endl;
    cout << "Tic Tac Toe Game" << endl;
    cout << "------------------" << endl;
    cout << "------------------" << endl;

    int mode;
    cout << "Would you like to play: " << endl;
    cout << "1. Player vs Player" << endl;
    cout << "2. Player vs Computer" << endl;
    cout << " " << endl;

    cout << "Enter your choice: ";
    cin >> mode;

    cout << "Enter Player 1's name: ";
    cin >> player_one_name;

    if (mode == 1) {
        cout << "Enter Player 2's name: ";
        cin >> player_two_name;
        player_two_symbol = 'O';
    } else {
        player_two_name = "Computer"; // For computer mode, set player two's name to "Computer"
        player_two_symbol = 'X';
    }

    player_one_symbol = 'X';
    computer_symbol = 'O';

    srand(time(0)); // Seed for random number generation

    do {
        make_board(); // Reset the board for each new game
        display_board(); // Display the board before starting the game

        while (true) {
            player_move(player_one_name, player_one_symbol);
            int winner = check_for_win();
            if (winner == 1 || winner == 2 || winner == 3 || winner == 4) {
                update_scores(winner);
                display_scores();
                break;
            }

        if (mode == 1) {
        player_move(player_two_name, player_two_symbol);
        } else {
        computerMove();
        display_board(); // Display the board after computer's move
        int winner = check_for_win();
        if (winner == 1 || winner == 2 || winner == 3 || winner == 4) {
        update_scores(winner);
        display_scores();
        break;
        }
        }

        }
        } while (play_again());

    return 0;
}
