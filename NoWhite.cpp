//
// Created by 12744 on 2023/4/4.
//

#include "NoWhite.h"
extern int map[4];//ʹ���ⲿ���ú���extern���ö�����main�еĺ�����ʹ������NoWhite��ʹ��
extern char str[20];
extern char str1[10];
extern int grade;

//�ڷ���λ���±������
void BlackPos(){
    for(int i=0; i<4; i++){
        //ͨ��forѭ����ʹ���������rand����0~32547֮������������4ȡ�࣬��ŵ�һά������
        map[i] = rand()%4;
    }
}

//������Ϸ����
void Init(){
    //�ú������������Ϸ�����Ļ���
    //��ʼ������ͼ
    BeginBatchDraw();
    //����������ɫΪ��ɫ
    setlinecolor(BLUE);
    //���������ɫΪ��ɫ
    setfillcolor(WHITE);
    //���Ʊ���
    for(int i=0; i<4; i++){//����
        for(int j=0; j<4; j++){//����
            fillrectangle(i*100,j*120,(i+1)*100,(j+1)*120);
        }
    }
    //���ƺڷ���
    //���úڷ���������ɫΪ��ɫ
    setfillcolor(BLACK);
    for(int i=0; i<4; i++){
        fillrectangle(map[i]*100,i*120,(map[i]+1)*100,(i+1)*120);
    }
    //����������ͼ
    EndBatchDraw();
}

//�ж��Ƿ�������������һ�еĺڷ���
bool IsFinalBlack(){
    //���Ȼ�������Ϣ
    MOUSEMSG msg = GetMouseMsg();//��ȡ������Ľṹ��
    //��ȡ����ڻ����ڵĵ��λ��
    int x = msg.x/100;
    int y = msg.y/120;
    switch (msg.uMsg) {
        //�ж������Ϣ
        case WM_LBUTTONDOWN:
            //��ʱ���������£���Ҫ�жϰ��������λ��
            if(x == map[3] && y == 3){
                //˵����ʱ���µ���������һ�еĺڷ���
                //��ʱ��Ҫ����������ĺڷ��飬�����������еĺڷ��������������µĺڷ������������һ��
                for(int i=3; i>0; i--){
                    map[i] = map[i-1];
                }
                map[0] = rand()%4;
                grade += 10;
            } else {
                //˵����ʱ���µĲ���������һ�еĺڷ��飬��Ϸ����
                return false;
            }
    }
    return true;
}

//�����������������
void start(){
    BlackPos();
    Init();
    while(1){
        if(!IsFinalBlack()){
            //˵����ʱ��Ϸ�Ѿ���������Ҫ�����ж��Ƿ������Ϸ
            strcpy(str,"��Ϸ�÷֣�");
            strcat(str,itoa(grade,str1,10));
            if(MessageBox(GetHWnd(),str,"��ʾ",MB_YESNO) == IDYES){
                //˵����ʱ���߰��µ��ǵ�����ȷ�ϰ���
                BlackPos();
            } else {
                exit(0);
            }
        }
        Init();
    }
}
