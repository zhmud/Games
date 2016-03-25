#include "show.h"

int game();
int showships(char battleship[][size], const int X, const int Y, const int sizechip, const int orientation, bool paint = true);
void touch(char battleship[][size], const int X, const int Y, const int tou);
int keyEnter(int *x, int *y, int size, bool *flag);
int positionship(char battleship[][size], bool paint = true);
int selfdeploy(char battleship[][size]);
int showtime(char battleship[][size], const int X, const int Y, const int sizechip, const bool orientation, bool cls = false);
int kaput(char battleship[][size], int X, int Y, bool pole = false);
int zalpComp(char battleship[][size], int *X, int *Y, int hard, bool *hit, int *Abulo, int *nea, int *countship);
int AI(char battleship[][size], int X, int Y, int way, int *countship);
int zalpPlayer(char battleship[][10], int *x, int *y, bool *mode, int *countship, bool *autoshow);
int deployship(char battleship[][size], int countship[][4], int deploy);