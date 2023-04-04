#include "NoWhite.h"
int map[4];//用来保存黑方块的位置下标
char str[20];
char str1[10];
int grade = 0;

int main() {
    initgraph(400,480);
    srand((unsigned )time(nullptr));
    start();
    system("pause");
    closegraph();
    return 0;
}
