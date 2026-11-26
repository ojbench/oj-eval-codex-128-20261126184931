#include <array>
#include <iostream>
#include <string>

std::string classify(const std::array<char, 9>& board) {
    int crosses = 0;
    int circles = 0;
    for (char cell : board) {
        crosses += cell == 'x';
        circles += cell == 'o';
    }

    constexpr int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    bool cross_wins = false;
    bool circle_wins = false;
    for (const auto& line : lines) {
        if (board[line[0]] == board[line[1]] &&
            board[line[1]] == board[line[2]]) {
            cross_wins |= board[line[0]] == 'x';
            circle_wins |= board[line[0]] == 'o';
        }
    }

    if (crosses < circles || crosses > circles + 1 ||
        (cross_wins && circle_wins) ||
        (cross_wins && crosses != circles + 1) ||
        (circle_wins && crosses != circles)) {
        return "invalid";
    }
    if (cross_wins) return "win";
    if (circle_wins) return "lose";
    return crosses + circles == 9 ? "tie" : "ongoing";
}

int main() {
    std::array<char, 9> board{};
    for (char& cell : board) {
        if (!(std::cin >> cell)) return 0;
    }
    std::cout << classify(board) << '\n';
    return 0;
}
