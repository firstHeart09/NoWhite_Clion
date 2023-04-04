//
// Created by 12744 on 2023/4/4.
//

#include "NoWhite.h"
extern int map[4];//使用外部调用函数extern调用定义在main中的函数，使其能在NoWhite中使用
extern char str[20];
extern char str1[10];
extern int grade;

//黑方块位置下标的生成
void BlackPos(){
    for(int i=0; i<4; i++){
        //通过for循环，使用随机函数rand生成0~32547之间的随机数并对4取余，存放到一维数组中
        map[i] = rand()%4;
    }
}

//绘制游戏背景
void Init(){
    //该函数负责完成游戏背景的绘制
    //开始批量绘图
    BeginBatchDraw();
    //设置线条颜色为蓝色
    setlinecolor(BLUE);
    //设置填充颜色为白色
    setfillcolor(WHITE);
    //绘制背景
    for(int i=0; i<4; i++){//行数
        for(int j=0; j<4; j++){//列数
            fillrectangle(i*100,j*120,(i+1)*100,(j+1)*120);
        }
    }
    //绘制黑方块
    //设置黑方块的填充颜色为黑色
    setfillcolor(BLACK);
    for(int i=0; i<4; i++){
        fillrectangle(map[i]*100,i*120,(map[i]+1)*100,(i+1)*120);
    }
    //结束批量绘图
    EndBatchDraw();
}

//判断是否点击的是最下面一行的黑方块
bool IsFinalBlack(){
    //首先获得鼠标信息
    MOUSEMSG msg = GetMouseMsg();//获取鼠标点击的结构体
    //获取鼠标在画布内的点击位置
    int x = msg.x/100;
    int y = msg.y/120;
    switch (msg.uMsg) {
        //判断鼠标信息
        case WM_LBUTTONDOWN:
            //此时鼠标左键按下，需要判断按下左键的位置
            if(x == map[3] && y == 3){
                //说明此时按下的是最下面一行的黑方块
                //此时需要消除最下面的黑方块，并将上面三行的黑方块下移且生成新的黑方块放在最上面一行
                for(int i=3; i>0; i--){
                    map[i] = map[i-1];
                }
                map[0] = rand()%4;
                grade += 10;
            } else {
                //说明此时按下的不是最下面一行的黑方块，游戏结束
                return false;
            }
    }
    return true;
}

//整个代码的运行流程
void start(){
    BlackPos();
    Init();
    while(1){
        if(!IsFinalBlack()){
            //说明此时游戏已经结束，需要我们判断是否继续游戏
            strcpy(str,"游戏得分：");
            strcat(str,itoa(grade,str1,10));
            if(MessageBox(GetHWnd(),str,"提示",MB_YESNO) == IDYES){
                //说明此时玩者按下的是弹窗的确认按键
                BlackPos();
            } else {
                exit(0);
            }
        }
        Init();
    }
}
