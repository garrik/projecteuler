# A Game of Chance
## Problem 951

Two players play a game using a deck of cards: red and black.
Initially the deck is shuffled into one of the `C(2n, n)` possible starting configurations. 
Play then proceeds, alternating turns, where a player follows two steps on each turn:

* Remove the top card from the deck, taking note of its colour.
* If there is a next card and it is the same colour as the previous card they toss a fair coin. 
  If the coin lands on heads they remove that card as well; otherwise leave it on top of the deck.

The player who removes the final card from the deck wins the game.

Some starting configurations give an advantage to one of the players; while some starting configurations are fair, in which both players have exactly 50% chance to win the game. For example, if `n = 2`
there are four starting configurations which are fair: RRBB, BBRR, RBBR, BRRB. The remaining two, RBRB and BRBR, result in a guaranteed win for the second player.

Define `F(n)` to be the number of starting configurations which are fair. Therefore `F(2) = 4`. 
You are also given `F(8) = 11892`.

Find `F(26)`.

## Notes
### combinations for n = 2 (6)

combination | # swap | swap index | note
-           | -      | -          |
RRBB        | 0      |            |
BRRB        | 1      | 0, 2       |
BRBR        | 1      | 0, 3       |
            |        |            |
RBRB        | 1      | 1, 2       | duale per BRBR
RBBR        | 1      | 1, 3       | duale per BRRB
BBRR        | 2      | 0 1, 2 3   | duale per RRBB

### combinations for n = 3 (20)

combination | # swap | swap index
-           | -      | -
RRRBBB      | 0      |
            |        |
BRRRBB      | 1      | 0, 3
BRRBRB      | 1      | 0, 4
BRRBBR      | 1      | 0, 5
            |        |
RBRRBB      | 1      | 1, 3
RBRBRB      | 1      | 1, 4
RBRBBR      | 1      | 1, 5
            |        |
RRBRBB      | 1      | 2, 3
RRBBRB      | 1      | 2, 4
RRBBBR      | 1      | 2, 5

### combinations for n = 4 (70)

combination | # swap | swap index
-           | -      | -
RRRR BBBB   | 0      |
            |        |
BRRR RBBB   | 1      | 0, 4
BRRR BRBB   | 1      | 0, 5
BRRR BBRB   | 1      | 0, 6
BRRR BBBR   | 1      | 0, 7
            |        |
RBRR RBBB   | 1      | 1, 4
RBRR BRBB   | 1      | 1, 5
RBRR BBRB   | 1      | 1, 6
RBRR BBBR   | 1      | 1, 7
            |        |
RRBR RBBB   | 1      | 2, 4
RRBR BRBB   | 1      | 2, 5
RRBR BBRB   | 1      | 2, 6
RRBR BBBR   | 1      | 2, 7
            |        |
RRRB RBBB   | 1      | 3, 4
RRRB BRBB   | 1      | 3, 5
RRRB BBRB   | 1      | 3, 6
RRRB BBBR   | 1      | 3, 7
            |        |
BBRR RRBB   | 2      | 0 1, 4 5
BBRR RBRB   | 2      | 0 1, 4 6
BBRR RBBR   | 2      | 0 1, 4 7
BBRR BRRB   | 2      | 0 1, 5 6
BBRR BRBR   | 2      | 0 1, 5 7
BBRR BBRR   | 2      | 0 1, 6 7
            |        |
BRBR RRBB   | 2      | 0 2, 4 5
BRBR RBRB   | 2      | 0 2, 4 6
BRBR RBBR   | 2      | 0 2, 4 7
BRBR BRRB   | 2      | 0 2, 5 6
BRBR BRBR   | 2      | 0 2, 5 7
BRBR BBRR   | 2      | 0 2, 6 7
            |        |
BRRB RRBB   | 2      | 0 3, 4 5
BRRB RBRB   | 2      | 0 3, 4 6
BRRB RBBR   | 2      | 0 3, 4 7
BRRB BRRB   | 2      | 0 3, 5 6
BRRB BRBR   | 2      | 0 3, 5 7
BRRB BBRR   | 2      | 0 3, 6 7
            |        |
RBBR RRBB   | 2      | 1 2, 4 5 duale per BRRB
            |        |
RBRB RRBB   | 2      | 1 3, 4 5 duale per BRBR
            |        |
RRBB RRBB   | 2      | 2 3, 4 5 duale per BBRR

3 swap duale per 1 swap
RBBB duale per BRRR

### combinations for n = 5

combination | # swap | swap index
-           | -      | -
RRRRR BBBBB | 0      |
            |        |
BRRRR RBBBB | 1      | 0, 5
BRRRR BRBBB | 1      | 0, 6
BRRRR BBRBB | 1      | 0, 7
BRRRR BBBRB | 1      | 0, 8
BRRRR BBBBR | 1      | 0, 9
            |        |
RBRRR RBBBB | 1      | 1, 5
RBRRR BRBBB | 1      | 1, 6
RBRRR BBRBB | 1      | 1, 7
RBRRR BBBRB | 1      | 1, 8
RBRRR BBBBR | 1      | 1, 9
            |        |
RRBRR RBBBB | 1      | 2, 5
            |        |
RRRBR RBBBB | 1      | 3, 5
            |        |
RRRRB RBBBB | 1      | 4, 5
            |        |
BBRRR RRBBB | 2      | 0 1, 5 6
BBRRR RBRBB | 2      | 0 1, 5 7
BBRRR RBBRB | 2      | 0 1, 5 8
BBRRR RBBBR | 2      | 0 1, 5 9
BBRRR BRRBB | 2      | 0 1, 6 7
BBRRR BRBRB | 2      | 0 1, 6 8
BBRRR BRBBR | 2      | 0 1, 6 9
BBRRR BBRRB | 2      | 0 1, 7 8
BBRRR BBRBR | 2      | 0 1, 7 9
BBRRR BBBRR | 2      | 0 1, 8 9
            |        |
BRBRR RRBBB | 2      | 0 2, 5 6
BRBRR RBRBB | 2      | 0 2, 5 7
BRBRR RBBRB | 2      | 0 2, 5 8
BRBRR RBBBR | 2      | 0 2, 5 9
BRBRR BRRBB | 2      | 0 2, 6 7
BRBRR BRBRB | 2      | 0 2, 6 8
BRBRR BRBBR | 2      | 0 2, 6 9
BRBRR BBRRB | 2      | 0 2, 7 8
BRBRR BBRBR | 2      | 0 2, 7 9
BRBRR BBBRR | 2      | 0 2, 8 9
            |        |
BRRBR RRBBB | 2      | 0 3, 5 6
BRRBR RBRBB | 2      | 0 3, 5 7
BRRBR RBBRB | 2      | 0 3, 5 8
BRRBR RBBBR | 2      | 0 3, 5 9
BRRBR BRRBB | 2      | 0 3, 6 7
BRRBR BRBRB | 2      | 0 3, 6 8
BRRBR BRBBR | 2      | 0 3, 6 9
BRRBR BBRRB | 2      | 0 3, 7 8
BRRBR BBRBR | 2      | 0 3, 7 9
BRRBR BBBRR | 2      | 0 3, 8 9
            |        |
BRRRB RRBBB | 2      | 0 4, 5 6
BRRRB RBRBB | 2      | 0 4, 5 7
BRRRB RBBRB | 2      | 0 4, 5 8
BRRRB RBBBR | 2      | 0 4, 5 9
BRRRB BRRBB | 2      | 0 4, 6 7
BRRRB BRBRB | 2      | 0 4, 6 8
BRRRB BRBBR | 2      | 0 4, 6 9
BRRRB BBRRB | 2      | 0 4, 7 8
BRRRB BBRBR | 2      | 0 4, 7 9
BRRRB BBBRR | 2      | 0 4, 8 9
            |        |
BBBRR RRRBB | 3      | 0 1 2, 5 6 7
BBBRR RRBRB | 3      | 0 1 2, 5 6 8
BBBRR RRBBR | 3      | 0 1 2, 5 6 9
BBBRR RBRRB | 3      | 0 1 2, 5 7 8
BBBRR RBRBR | 3      | 0 1 2, 5 7 9
BBBRR RBBRR | 3      | 0 1 2, 5 8 9
BBBRR BRRRB | 3      | 0 1 2, 6 7 8
BBBRR BRRBR | 3      | 0 1 2, 6 7 9
BBBRR BRBRR | 3      | 0 1 2, 6 8 9
BBBRR BBRRR | 3      | 0 1 2, 7 8 9

