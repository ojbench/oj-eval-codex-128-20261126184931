# Solution

Count both kinds of marks and inspect the eight winning lines. Reject a
position if x has neither the same number of moves as o nor exactly one more,
if both players win, or if the winner did not make the last move. Otherwise
report the winner, a full-board tie, or an ongoing game.

These conditions are sufficient on a 3 by 3 board. With no winning line,
any alternating ordering of the given marks has no earlier winning line.
For a winning board, the winner has at most five marks. Two winning lines
must intersect (disjoint lines require six marks), and there cannot be three
winning lines with only five marks. Place their intersection last, or any
mark of a single winning line last. Removing that mark leaves no winning
line for either player, and the count checks allow a legal alternating
history for the remaining board.

Time and auxiliary space are both O(1).

# Local verification

Build the submission with `cmake . && make`.

The independent test enumerates legal game histories, stopping at terminal
positions, then compares the classifier against all 3^9 possible boards:

```sh
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic tests/exhaustive.cpp -o /tmp/problem128_test
/tmp/problem128_test
```

All 19,683 boards passed, including 5,478 reachable positions. Both README
examples also passed. The advertised `/workspace/data/128/data_test/`
directory was not present in this environment.
