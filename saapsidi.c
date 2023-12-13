#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_SNAKES 5
#define NUM_LADDERS 5
#define DEFAULT_FINAL_SQUARE 100

void displayBoard(int numPlayers, char player[][20], int position[]) {
    printf("\nCurrent Board:\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%s: %d\t", player[i], position[i]);
    }
    printf("\n\n");
}

void playGame(int numPlayers, int finalSquare) {
    char player[numPlayers][20];
    int position[numPlayers];

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    for (int i = 0; i < numPlayers; i++) {
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
        position[i] = 0;
    }

    // Define snakes and ladders
    int snakes[NUM_SNAKES][2] = {{17, 7}, {54, 34}, {92, 78}, {95, 72}, {98, 79}};
    int ladders[NUM_LADDERS][2] = {{3, 21}, {19, 42}, {25, 65}, {38, 89}, {60, 81}};

    int turn = 0;
    while (1) {
        printf("\n%s's turn:\n", player[turn % numPlayers]);

        int current = rand() % 6 + 1;
        printf("Rolled a %d \n", current);
        sleep(1);

        // Check for snakes and ladders
        for (int i = 0; i < NUM_SNAKES; i++) {
            if (position[turn % numPlayers] == snakes[i][0]) {
                printf("Oh no! Encountered a snake! Sliding down to %d.\n", snakes[i][1]);
                position[turn % numPlayers] = snakes[i][1];
            }
        }

        for (int i = 0; i < NUM_LADDERS; i++) {
            if (position[turn % numPlayers] == ladders[i][0]) {
                printf("Yay! Found a ladder! Climbing up to %d.\n", ladders[i][1]);
                position[turn % numPlayers] = ladders[i][1];
            }
        }

        // Move the player
        position[turn % numPlayers] += current;

        // Check if the player reaches or passes the final square
        if (position[turn % numPlayers] >= finalSquare) {
            printf("Congratulations! %s reached the final square! They are the winner!\n", player[turn % numPlayers]);
            displayBoard(numPlayers, player, position);
            return;
        }

        printf("%s's current position is now %d \n", player[turn % numPlayers], position[turn % numPlayers]);

        // Check for collisions with other players
        for (int i = 0; i < numPlayers; i++) {
            if (i != turn % numPlayers && position[i] == position[turn % numPlayers]) {
                printf("Oh no! Collision with %s! %s eliminates %s, sending them back to square 1.\n", player[i], player[turn % numPlayers], player[i]);
                position[i] = 1; // The latest player eliminates the previous one
            }
        }

        displayBoard(numPlayers, player, position);

        printf("Loading next turn .... \n");
        sleep(1.5);
        turn += 1;
    }
}

int main() {
    int numPlayers;

    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    playGame(numPlayers, DEFAULT_FINAL_SQUARE);

    return 0;
}
