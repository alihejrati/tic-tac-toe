
#include <stdlib.h>
#include <stdio.h>

#define MAP_LENGTH 3

enum State { WINS_X, WINS_O, DRAW } state;

char map[MAP_LENGTH][MAP_LENGTH];
int player = 0;
// 0: The first player with the 'x' symbol
// 1: The second player with the 'o' symbol

void newLine (void);
void fNewLine (FILE *file);
int isGameFinished (void);
void print (void);
void initalization (void);
int validation (int i, int j);
void printFile (void);
void switchTurn (void);
void play (void);

int main (void)
{
  initalization();

  while (isGameFinished() == 0) {
    play();
  }
  print();
  switch (state) {
    case WINS_X:
      printf("x player wins!");
      newLine();
      break;
    case WINS_O:
      printf("o player wins!");
      newLine();
      break;
    case DRAW:
      printf("DRAW!");
      newLine();
      break;
  }
  printFile();

  printf("Press any key to exit the Game!");
  newLine();
  return 0;
}

void newLine (void)
{
  printf("\n");
}
void fNewLine (FILE *file)
{
  fputs("\n", file);
}
int isGameFinished (void)
{
  int i = 0;
  int j = 0;
  int victory = 0;
  int mapIsFilled = 1;
  for (i = 0; i < MAP_LENGTH; i++) {
    for (j = 0; j < MAP_LENGTH; j++) {
      if (map[i][j] == 'E') {
        mapIsFilled = 0;
      }
    }
  }

  if (
    (map[0][0] != 'E' && map[0][0] == map[0][1] && map[0][0] == map[0][2])
    ||
    (map[1][0] != 'E' && map[1][0] == map[1][1] && map[1][0] == map[1][2])
    ||
    (map[2][0] != 'E' && map[2][0] == map[2][1] && map[2][0] == map[2][2])
    ||
    (map[0][0] != 'E' && map[0][0] == map[1][0] && map[0][0] == map[2][0])
    ||
    (map[0][1] != 'E' && map[0][1] == map[1][1] && map[0][1] == map[2][1])
    ||
    (map[0][2] != 'E' && map[0][2] == map[1][2] && map[0][2] == map[2][2])
    ||
    (map[0][0] != 'E' && map[0][0] == map[1][1] && map[0][0] == map[2][2])
    ||
    (map[0][2] != 'E' && map[0][2] == map[1][1] && map[0][2] == map[2][0])
  ) {
    // victory!
    victory = 1;
    if (player==1) {
      // 1: The second player with the 'o' symbol
      // So the player wins the previous stage => x player
      state = WINS_X;
    } else {
      // 0: The first player with the 'x' symbol
      // So the player wins the previous stage => o player
      state = WINS_O;
    }
  } else {
    state = DRAW;
  }
  return victory || mapIsFilled;
}
void print (void)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < MAP_LENGTH; i++) {
    for (j = 0; j < MAP_LENGTH; j++) {
      printf("%c ", map[i][j]);
    }
    newLine();
  }
}
void printFile (void)
{
  FILE *pFile;
  pFile = fopen("GameResults.txt", "a");

  int i = 0;
  int j = 0;
  char temp[3];

  for (i = 0; i < MAP_LENGTH; i++) {
    for (j = 0; j < MAP_LENGTH; j++) {
      temp[0] = map[i][j];
      temp[1] = ' ';
      temp[2] = '\0';
      fputs(temp, pFile);
    }
    fNewLine(pFile);
  }
  switch (state) {
    case WINS_X:
      fprintf(pFile, "x player wins!");
      fNewLine(pFile);
      break;
    case WINS_O:
      fprintf(pFile, "o player wins!");
      fNewLine(pFile);
      break;
    case DRAW:
      fprintf(pFile, "DRAW!");
      fNewLine(pFile);
      break;
  }
  fclose(pFile);
}
void initalization (void)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < MAP_LENGTH; i++) {
    for (j = 0; j < MAP_LENGTH; j++) {
      map[i][j] = 'E';
    }
  }
}
int validation (int i, int j)
{
  if (i>= 0 && i<=2 && j>=0 && j<= 2) {
    // ok!
  } else {
    return 0; // out of range
  }
  if (map[i][j] != 'E') {
    return 0; // It's already full
  }
  return 1;
}
void switchTurn (void)
{
  player = player == 0 ? 1 : 0;
}
void play (void)
{
  int i;
  int j;

  print();
  if (player==1) {
    // 1: The second player with the 'o' symbol
    printf("o turn: ");
  } else {
    // 0: The first player with the 'x' symbol
    printf("x turn: ");
  }
  scanf("%d", &i);
  scanf("%d", &j);
  if (validation(i, j)) {
    map[i][j] = player == 0 ? 'x' : 'o';
    switchTurn();
  } else {
    printf("[warning] validation error please try again.");
    newLine();
    play();
  }
}
