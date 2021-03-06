#include<stdio.h>
#include<math.h>
#include<string.h>

#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define ROOK 4
#define KNIGHT 2
#define BISHOP 3
#define KING 6
#define QUEEN 5
#define PAWN 1

static int turn = WHITE;
static int board[8][8] = { {-4, -2, -3, -5, -6, -3, -2, -4},
                            {-1, -1, -1, -1, -1, -1, -1, -1},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1, 1, 1, 1},
                            {4, 2, 3, 5, 6, 3, 2, 4}};

static int isLegalMove(int srcI, int srcJ, int trgI, int trgJ) {
    int i;
    int piece = board[srcI][srcJ];//moved piece...
    int pieceType = abs(piece);

    switch (pieceType) {
    case ROOK: //straight up/down left/right
        if(srcI != trgI && srcJ != trgJ) return 0; //if not moving up/down or left/right
        if (srcJ < trgJ) {//case 1 left to right
            for (i = 1; i < trgJ - srcJ; i++)
                if (board[srcI][srcJ + i] != EMPTY)
                    return 0;
        }else if (srcJ > trgJ) {//case 2 right to left
            for (i = 1; i < srcJ - trgJ; i++)
                if (board[srcI][srcJ - i] != EMPTY)
                    return 0;
        }else if (srcI > trgI) { //going up
            for (i = 1; i < srcI - trgI; i++)
                if (board[srcI - i][srcJ ] != EMPTY)
                    return 0;
        }else { //going down
            for (i = 1; i < trgI - srcI; i++)
                if (board[srcI + i][srcJ] != EMPTY)
                    return 0;
        }
    case PAWN: //one space toward opposite side board or two spaces if first time moving
        int moves = abs(trgI - srcI);
            if(moves < 1 || moves > 2 || (srcJ != trgJ)) { // pawn can never move more than twice and it cant change columns
            printf("pawn cannot move more than 2 or less than 1... and cannot change column \n");
            return 0;
        }
        if(moves == 2 && (srcI == 6 || srcI == 1)){ //if pawn is in starting row, it can move two spaces forward
            if (piece > 0){ //white piece
                for (i = 1; i < 2; i++)
                    if (board[srcI - i][srcJ] != EMPTY)
                        return 0;
                    else{
                        printf("spot clear for white pawn...");
                    }
            }else{ //black piece
                for (i = 1; i < 2; i++)
                    if (board[srcI + i][srcJ] != EMPTY)
                        return 0;
                    else{
                        printf("spot clear for black pawn...");
                    }
            }
        }else{ //only move once space forward
            if((abs(srcI - trgI) > 1) ) return 0;
            else if (turn > 0){ //white piece
                if (board[trgI][trgJ] != EMPTY || (trgI - srcI) != 1)
                    return 0;
            }else{ //black piece
                if (board[trgI][trgJ] != EMPTY || (srcI - trgI) != 1)
                    return 0;
            }
        }
        break;
    case KNIGHT://L shape
        return abs((srcI - trgI) * (srcJ - trgJ)) == 2;
    case BISHOP: //diagonals
        if (abs(srcI - trgI) != abs(srcJ - trgJ)) return 0;
        int change = abs(trgI - srcI);
        if (srcI < trgI && srcJ < trgJ) {//case 1
            for (i = 1; i < change; i++)
                if (board[srcI + i][srcJ + i] != EMPTY)
                    return 0;
        }else if (srcI < trgI && srcJ > trgJ) {//case 2
            for (i = 1; i < change ; i++)
                if (board[srcI + i][srcJ - i] != EMPTY)
                    return 0;
        }else if (srcI > trgI && srcJ < trgJ){ //case 3
            for (i = 1; i < change; i++)
                if (board[srcI - i][srcJ + i] != EMPTY)
                    return 0;
        }else{ //case 4
            for (i = 1; i < change; i++)
                if (board[srcI - i][srcJ - i] != EMPTY)
                    return 0;
        }
        break;
    case QUEEN: //bishop and Rook movements
        if ((abs(srcI - trgI) != abs(srcJ - trgJ)) || (srcI != trgI && srcJ != trgJ)) return 0;
            //Rook move for queen
            if (srcJ < trgJ) {//case 1 left to right
                for (i = 1; i < trgJ - srcJ; i++)
                    if (board[srcI][srcJ + i] != EMPTY)
                        return 0;
            }else if (srcJ > trgJ) {//case 2 right to left
                for (i = 1; i < srcJ - trgJ; i++)
                    if (board[srcI][srcJ - i] != EMPTY)
                        return 0;
            }else if (srcI > trgI) { //going up
                for (i = 1; i < srcI - trgI; i++)
                    if (board[srcI - i][srcJ ] != EMPTY)
                        return 0;
            }else if(srcI < trgI){ //going down
                for (i = 1; i < trgI - srcI; i++)
                    if (board[srcI + i][srcJ] != EMPTY)
                        return 0;
            }
            //Bishop move for queen
            else if (srcI < trgI && srcJ < trgJ) {//case 1
                for (i = 1; i < change; i++)
                    if (board[srcI + i][srcJ + i] != EMPTY)
                        return 0;
            }else if (srcI < trgI && srcJ > trgJ) {//case 2
                for (i = 1; i < change ; i++)
                    if (board[srcI + i][srcJ - i] != EMPTY)
                        return 0;
            }else if (srcI > trgI && srcJ < trgJ){ //case 3
                for (i = 1; i < change; i++)
                    if (board[srcI - i][srcJ + i] != EMPTY)
                        return 0;
            }else{ //case 4
                for (i = 1; i < change; i++)
                    if (board[srcI - i][srcJ - i] != EMPTY)
                        return 0;
            }
            break;
    case KING: //one space any direction
        if ((trgI == srcI + 1 && trgJ == srcJ) ||
            (trgI == srcI - 1 && trgJ == srcJ) ||
            (trgJ == srcJ + 1 && trgI == srcI) ||
            (trgJ == srcJ - 1 && trgI == srcI)){
            break;

        }else { return 0; } //king move not allowed
    }
    return 1;//legal move
}

static int isLegalCapture(int srcI, int srcJ, int trgI, int trgJ) {
    int piece = board[srcI][srcJ];
    int pieceType = abs(piece);
    printf("srcI-> %d \n", srcI);
    printf("srcJ-> %d \n", srcJ);
    printf("trgI-> %d \n", trgI);
    printf("trgJ-> %d \n", trgJ);
    // pawn will eat diagonally one step
    if (pieceType == PAWN) {
        printf("pawn is capturing...\n");
        if (piece < 0){ //black pawn
            printf("black pawn...\n");
            if ((trgJ == srcJ + 1) && (abs(srcI - trgI) == 1)){
                printf("checking if target space has white piece...\n");
                if (board[trgI][trgJ] > 0) return 1; //capturing white piece
                else {
                    printf("black piece cannot capture black\n");
                    return 0;
                }
            } else {
                printf("Invalid capture\n");
                return 0;
            }
        } else { //white pawn
            printf("white pawn...\n");
            if ((trgJ == abs(srcJ - 1)) && (abs(srcI - trgI) == 1)){
                printf("checking if target space has black piece...\n");
                if (board[trgI][trgJ] < 0) return 1; //capturing black piece
                else {
                    printf("white piece cannot capture white\n");
                    return 0;
                }
            } else {
                printf("Invalid capture\n");
                return 0;
            }
        }
    }
    if (isLegalMove(srcI, srcJ, trgI, trgJ) && pieceType != PAWN) {
        if (piece < 0){ //black piece
            if (board[trgI][trgJ] > 0) return 1;
             else {
                 printf("black piece cannot capture black\n");
                 return 0;
             }

        } else{ //white piece
            if (board[trgI][trgJ] < 0) return 1;
            else {
                printf("white piece cannot capture white\n");
                return 0;
            }
        }
    } else {
        printf("cannot capture empty cell...try 'mv' command instead\n");
        return 0;
    }
}


char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
        if (lastCharacter == '\n') {
            command[0] = '\0';
            return lastCharacter;
        }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
void handleMove() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for mv command! It must be in the form of mv ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the rest of illegal command..
        return;
    }
    sourceFile = source[0];//source = "a5", sourceFile = 'a'
    targetFile = target[0];
    sourceRank = source[1] - '0';//source = "a5", sourceRank = 5
    targetRank = target[1] - '0';
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move\n", turn == 1 ? "white" : "black");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        return;
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        return;
    }
    //end of error checking....

    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = EMPTY;
    turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
}
void handleCapture() {
    char source[MAX_COMMAND_TOKEN_LENGTH];
    char target[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    lastCharacter = getCommandWord(source, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter == '\n') {
        printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
        return;
    }
    lastCharacter = getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH);
    if (lastCharacter != '\n') {
        printf("Too many arguments for cp command! It must be in the form of cp ai bj.\n");
        while (getCommandWord(target, MAX_COMMAND_TOKEN_LENGTH) != '\n');
        return;
    }
    sourceFile = source[0];
    targetFile = target[0];
    sourceRank = source[1] - '0';
    targetRank = target[1] - '0';
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("invalid mv arguments\n");
        return;
    }
    //checking the turn first
    if (board[sourceI][sourceJ] * turn < 0) {
        printf("Turn violation, it's %s to move", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] * board[targetI][targetJ] > 0) {
        printf("Violation, %s cannot capture its own piece.", turn == WHITE ? "WHITE" : "BLACK");
        return;
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] == EMPTY) {
        printf("Invalid capture: either source square is empty or target square is empty");
        return;
    }
    if (!isLegalCapture(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess capture");
        return;
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = 0;
    turn *= -1;
}
handleShow() {
    int i, j;
    printf("board\t");
    for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
    for (i = 0; i < 8; i++)//table itself
        for (j = 0; j < 9; j++)
            printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ?  '\n' : '\t');
}
main() {
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    while (1){ //infinite while loop...
        printf("Please enter a new command... quit , mv , cp , show\n");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);

        if (strcmp(command, "quit") == 0){ //if command === "quit"
            printf("Thank you for playing...");
            break;
        }else if (!strcmp(command, "mv")){ //if command == "mv"
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else handleMove();
        }else if (!strcmp(command, "cp")){ //if command == "cp"
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else handleCapture();
        } else if (!strcmp(command, "show")){ //if command == "show"
            if (lastCharacter != '\n'){ //show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the invalid show command...
            } else handleShow();
        }else {
            printf("\n invalid command! Your command must start either with quit, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}
