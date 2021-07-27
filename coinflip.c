#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define BLINKCOUNT 3
#define DICEEYES 6
#define USLEEPNOW 500000

char loading[4] = {'/', '-', '\\', '|'};

void init() {
    srand(time(NULL));
}

int throwDice() {
    int diceCount = 0;

    printf("Rolling dice for rounds to win in coinflip:\n");
    for(int j=0; j<BLINKCOUNT; j++) {
        printf("  %i\r", (rand()%DICEEYES)+1);
        fflush(stdout);
        usleep(USLEEPNOW);
    }
    diceCount = (rand()%DICEEYES)+1;
    for(int i=0; i<BLINKCOUNT; i++) {
        printf("  %i\r", diceCount);
        fflush(stdout);
        usleep(USLEEPNOW);
        printf("   \r");
        fflush(stdout);
        usleep(USLEEPNOW);
    }
    printf("Whichever side of the coin gets %i points first, wins.\n", diceCount);
    return diceCount;
}

int flip(int rounds, char** argv) {
    int head = 0;
    int tail = 0;
    int round = 1;

    printf("HEAD: %s\t\tTAIL: %s\n", argv[1], argv[2]);
    while(head < rounds && tail < rounds) {
        for(int j=0; j<5; j++) {
            printf("  %c\r", loading[j%4]);
            fflush(stdout);
            usleep(USLEEPNOW);
        }
        if (rand()%2 == 0) {
            printf(RED "HEAD!\n" RESET);
            head++;
        } else {
            printf(BLUE "TAIL!\n" RESET);
            tail++;
        }
        printf(YELLOW "HEAD: %i\n" RESET, head);
        printf(YELLOW "TAIL: %i\n" RESET, tail);
        usleep(USLEEPNOW);
    }
    printf(MAGENTA "%s WINS\n" RESET, (head >= rounds) ? argv[1] : argv[2]);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf(RED "Please write your options for head and tails\n" RESET);
        exit(1);
    }
    init();
    flip(throwDice(), argv);
    return 1;
}