#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define NUM_SNAKES 5
#define NUM_LADDERS 5
#define DEFAULT_FINAL_SQUARE 100

// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void displayBoard(int numPlayers, char player[][20], int position[])
{
    printf("\nCurrent Board:\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s: %d\t", player[i], position[i]);
    }
    printf("\n\n");
}

void playGame(int numPlayers, int finalSquare)
{
    char player[numPlayers][20];
    int position[numPlayers];
    int consecutiveSixCount[numPlayers];

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    for (int i = 0; i < numPlayers; i++)
    {
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
        position[i] = 0;
        consecutiveSixCount[i] = 0;
    }

    // Define snakes and ladders
    int snakes[NUM_SNAKES][2] = {{17, 7}, {54, 34}, {92, 78}, {95, 72}, {99, 2}};
    int ladders[NUM_LADDERS][2] = {{3, 21}, {19, 42}, {25, 65}, {38, 89}, {60, 81}};

    int turn = 0;
    while (1)
    {
        printf("\n%s's turn:\n", player[turn % numPlayers]);

        int current = rand() % 6 + 1;
        printf("Rolled a %d \n", current);
        sleep(1000);

        // Check for snakes and ladders
        for (int i = 0; i < NUM_SNAKES; i++)
        {
            if (position[turn % numPlayers] == snakes[i][0])
            {
                printf("%sOh no! Encountered a snake! Sliding down to %d.%s\n", ANSI_COLOR_RED, snakes[i][1], ANSI_COLOR_RESET);
                position[turn % numPlayers] = snakes[i][1]; // Corrected line
            }
        }

        for (int i = 0; i < NUM_LADDERS; i++)
        {
            if (position[turn % numPlayers] == ladders[i][0])
            {
                printf("%sYay! Found a ladder! Climbing up to %d.%s\n", ANSI_COLOR_GREEN, ladders[i][1], ANSI_COLOR_RESET);
                position[turn % numPlayers] = ladders[i][1];
            }
        }

        // Move the player
        position[turn % numPlayers] += current;

        // Check if the player reaches or passes the final square
        if (position[turn % numPlayers] >= finalSquare)
        {
            printf("%sCongratulations! %s reached the final square! They are the winner!%s\n", ANSI_COLOR_GREEN, player[turn % numPlayers], ANSI_COLOR_RESET);
            displayBoard(numPlayers, player, position);
            return;
        }

        printf("%s%s's current position is now %d %s\n", ANSI_COLOR_YELLOW, player[turn % numPlayers], position[turn % numPlayers], ANSI_COLOR_RESET);

        // Check for collisions with other players
        for (int i = 0; i < numPlayers; i++)
        {
            if (i != turn % numPlayers && position[i] == position[turn % numPlayers])
            {
                printf("%sOh no! Collision with %s! %s eliminates %s, sending them back to square 1.%s\n", ANSI_COLOR_RED, player[i], player[turn % numPlayers], player[i], ANSI_COLOR_RESET);
                position[i] = 1; 
                printf("%s gets another chance",player[turn % numPlayers]);
            }
        }

        // Check for consecutive sixes
        if (current == 6)
        {
            consecutiveSixCount[turn % numPlayers]++;
            if (consecutiveSixCount[turn % numPlayers] == 3)
            {
                printf("%sOh no! %s rolled three consecutive 6s and gets a penalty of -6!%s\n", ANSI_COLOR_RED, player[turn % numPlayers], ANSI_COLOR_RESET);
                position[turn % numPlayers] -= 6;
                consecutiveSixCount[turn % numPlayers] = 0;
            }
            else
            {
                printf("%sWow! %s rolled a 6 and gets another chance.%s\n", ANSI_COLOR_GREEN, player[turn % numPlayers], ANSI_COLOR_RESET);
                continue; // Bonus chance for rolling a 6
            }
        }
        else
        {
            consecutiveSixCount[turn % numPlayers] = 0;
        }

        displayBoard(numPlayers, player, position);

        printf("%s%s is rolling now .... %s\n", ANSI_COLOR_BLUE, player[turn % numPlayers], ANSI_COLOR_RESET);
        sleep(15000);
        turn += 1;
    }
}

int main()
{
    int numPlayers;

    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    playGame(numPlayers, DEFAULT_FINAL_SQUARE);

    return 0;
}
