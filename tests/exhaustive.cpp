#define main solution_main
#include "../main.cpp"
#undef main

#include <cassert>
#include <map>

std::map<std::array<char, 9>, std::string> reachable;

// Generate only legal histories, stopping immediately after a win or draw.
void explore(std::array<char, 9>& board, char player) {
    if (reachable.count(board)) return;
    std::string result = "ongoing";
    for (int i = 0; i < 3; ++i) {
        for (char mark : {'x', 'o'}) {
            if ((board[3*i] == mark && board[3*i+1] == mark && board[3*i+2] == mark) ||
                (board[i] == mark && board[i+3] == mark && board[i+6] == mark)) {
                result = mark == 'x' ? "win" : "lose";
            }
        }
    }
    for (char mark : {'x', 'o'}) {
        if ((board[0] == mark && board[4] == mark && board[8] == mark) ||
            (board[2] == mark && board[4] == mark && board[6] == mark)) {
            result = mark == 'x' ? "win" : "lose";
        }
    }
    bool full = true;
    for (char cell : board) full &= cell != '-';
    if (result == "ongoing" && full) result = "tie";
    reachable[board] = result;
    if (result != "ongoing") return;
    for (char& cell : board) {
        if (cell != '-') continue;
        cell = player;
        explore(board, player == 'x' ? 'o' : 'x');
        cell = '-';
    }
}

int main() {
    std::array<char, 9> board;
    board.fill('-');
    explore(board, 'x');
    assert(reachable.size() == 5478);
    constexpr char symbols[] = "-xo";
    for (int state = 0; state < 19683; ++state) {
        int encoded = state;
        for (char& cell : board) {
            cell = symbols[encoded % 3];
            encoded /= 3;
        }
        auto it = reachable.find(board);
        const std::string expected = it == reachable.end() ? "invalid" : it->second;
        assert(classify(board) == expected);
    }
    std::cout << "All 19683 boards passed; 5478 legal positions.\n";
}
