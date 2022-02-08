#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void create_enemy_number(int *num, int difficulty);
int eat_bite_judge(int my_num[], int ene_num[], int difficulty);
int number_check(int num, int array[], int difficulty);
void num_format(int *num, int difficulty);
void Numer0n(int difficulty);
void high_and_low(int num[], int difficulty);
int slash(int num[], int difficulty);
int target(int num[], int target_num, int difficulty);

//敵の数字を作る関数
void create_enemy_number(int *num, int difficulty){

    int number; //ランダム用変数
    int i,j; //for文用

    srand((unsigned int)time(NULL)); //ランダム種生成

    for(i=0; i<difficulty; i++){
        while(1){
            number = rand() % 10; //一桁だけ生成
            if(number_check(number, num, difficulty)){
                break;
            }
        }
        num[i] = number;
    }
}

//eat,biteの判定かつ発言関数(3hitの場合は1,それ以外は0を返す)
int eat_bite_judge(int my_num[], int ene_num[], int difficulty){

    int eat = 0;
    int bite = 0;
    int i,j; //for文用

    for(i=0; i<difficulty; i++){
        printf("%d",my_num[i]);
    }
    printf("は...\n");

    for(i=0; i<difficulty; i++){
        for(j=0; j<difficulty; j++){
            if(ene_num[i] == my_num[j]){
                if(i == j)
                    eat++;
                else
                    bite++;
            }
        }
    }
        
    sleep(1); //お楽しみ要素
    printf("%d eat %d bite です。\n",eat,bite);

    //クリアかどうか判定
    return ( eat == difficulty ) ? 1 : 0;
}

//数字が配列の中にあるかどうかをチェックする関数(あれば0,なければ1)
int number_check(int num, int array[], int difficulty){
    
    int i; //for文用
    for(i=0; i<difficulty; i++){
        if(array[i] == num){
            return 0;
        }
    }
    return 1;

}

//数列を初期化する関数
void num_format(int *num, int difficulty){
    
    int i;
    for(i=0; i<difficulty; i++){
        num[i] = -1;
    }
}

//数字が0~4ならLow,5~9ならHighと表示する関数
void high_and_low(int num[], int difficulty){
    
    int i;
    printf("１桁目から順に,");

    for(i=0; i<difficulty; i++){
        sleep(1);
        if(num[i] >= 0 && num[i] <=4){
            printf("Low");
        }else{
            printf("High");
        }
        printf(",");
    }
    printf("です.\n\n");
    sleep(1);
}

//数字の最大数から最小数を引いた数を返す関数
int slash(int num[], int difficulty){
    
    int i;
    int max = num[0]; //最大値
    int min = num[0]; //最小値

    for(i=0; i<difficulty; i++){
        if(max < num[i]){
            max = num[i];
        }else if(min > num[i]){
            min = num[i];
        }
    }
    return max - min;
}

//指定した数字がどこの桁にあるのかを返す関数(あればその数字、なければ-1を返す)
int target(int num[], int target_num, int difficulty){

    int i;
    for(i=0; i<difficulty; i++){
        if(num[i] == target_num){
            return i;
        }
    }
    return -1;
}


//ゲームの中身
void Numer0n(int difficulty){
    
    int i,j; //for文用
    int num; //プレイヤーが指定する数字
    int player_num[difficulty]; //自分の数字の配列
    int enemy_num[difficulty]; //敵の数字の配列

    int result = 0; //クリアかどうかの判定用変数
    int command; //コマンド
    int skill = 3; //スキルの残り個数
    int tar; //target用変数
    int sla; //slash用関数
    int target_num; //taget使用時に使用する変数
    
    float flag_skill_HL = 0; //high and lowを使ったかどうかのフラグ
    float flag_skill_slash = 0; //slachを使ったかどうかのフラグ
    float flag_skill_target = 0; //targetを使ったかどうかのフラグ

    //初期化
    num_format(player_num, difficulty);
    num_format(enemy_num, difficulty);

    create_enemy_number(enemy_num, difficulty); //敵の数字を作る

    //仮
    printf("敵の数字は");
    for(i=0; i<difficulty; i++){
        printf("%d",enemy_num[i]);
    }
    puts("");

    do{
        sleep(1);
        if(skill){ //skillが0じゃなかったら
            printf("何をする？\n");
            printf("　1.数字を入力　");
            if(!flag_skill_HL)
                printf("2.high and low　");
            if(!flag_skill_slash)
                printf("3.slash　");
            if(!flag_skill_target)
                printf("4.target　");
            printf("：");
            scanf("%d",&command);
        }else{
            printf("\nスキルがありません。数字を入力してください。\n");
            command = 1;
        }
        sleep(1);

        switch(command){
            case 1: //数字を入力する場合
                num_format(player_num, difficulty); //入力のため再度初期化
                //数字入力
                for(i=0; i<difficulty; i++){
                    while(1){
                        printf("%d桁目を入力してください :",i+1);
                        scanf("%d",&num);

                        if(num < 0 || num > 9){
                            printf("0~9の数字を入力してください.\n\n");
                        }else if(number_check(num, player_num, difficulty)){
                            player_num[i] = num;
                            break;
                        }else{
                            printf("数字は重複しないでください.\n\n");
                        }
                    }
                }

                //数字入力終了後、hit,bite判定
                result = eat_bite_judge(player_num, enemy_num, difficulty);
                break;

            case 2: //high and low を使用する場合
                if(!flag_skill_HL){
                    printf("high and lowを使用します。\n");
                    high_and_low(enemy_num, difficulty);
                    flag_skill_HL = 1;
                    skill--;
                }else{
                    printf("そのスキルは使えません。\n");
                }
                break;
            
            case 3: //slash を使用する場合
                if(!flag_skill_slash){
                    printf("slashを使用します。\n");
                    sla = slash(enemy_num, difficulty);
                    printf("結果は...");
                    sleep(1);
                    printf("「%d」でした。\n",sla);
                    flag_skill_slash = 1;
                    skill--;
                }else{
                    printf("そのスキルは使えません。\n");
                }
                break;

            case 4: //target を使用する場合
                if(!flag_skill_target){
                    printf("targetを使用します。\n");
                    while(1){
                        printf("どの数字を狙いますか？　：");
                        scanf("%d",&target_num);
                        if(target_num >= 0 && target_num <= 9){
                            break;
                        }else{
                            printf("正しい数字を入力してください。\n");
                        }
                    }

                    tar = target(enemy_num, target_num, difficulty);
                    printf("結果...");
                    sleep(1);
                    if(tar >= 0 && tar <= difficulty){
                        printf("%d は　%d 番目にあります。\n",target_num, tar+1);
                    }else{
                        printf("%d はありませんでした。\n",target_num);
                    }
                    flag_skill_target = 1;
                    skill--;
                }else{
                    printf("そのスキルは使えません。\n");
                }
                break;

            default:
                printf("正しい数字を入力してください。\n");
                break;
        }
    }while(!(result == 1));

    sleep(1);
    printf("\n　　ゲームクリア！\n\n");
    sleep(1);
    printf("　　タイトルへ戻ります。\n\n");
    sleep(1);
}

int main(void){

    float flag_rule = 0; //ルール説明したかどうかの関数

    while(1){
        printf("\n------------------------------------\n");
        printf("------------- Numer0n --------------\n");
        printf("------------------------------------\n\n");

        if(!flag_rule){
            printf("　　　～簡単なルール説明～　　\n");
            printf("　1.桁と数字を当てるゲームです。\n");
            printf("　2.数字と桁があっていればhit,\n　　数字のみが当たっていればbiteと表示されます。\n");
            printf("　3.すべての桁と数字を当てることができればクリアです。\n");
            printf("　4.当てるためのスキルがあります。\n");
            printf("　5.スキルは一度しか使えません。\n\n");
            flag_rule = 1;
        }

        printf("難易度を選択してください。\n");
        int difficulty; // 難易度指定用

        printf("1.初心者, 2.上級者, 3.EXIT：");
        scanf("%d", &difficulty);
        if(difficulty == 1 || difficulty == 2){
            difficulty += 2;
            puts("");
            Numer0n(difficulty);
        }else if(difficulty == 3){
            break;
        }else{
            printf("正しい数字を入力してください。\n");
            sleep(1);
        }
 
    }
    return 0;
}
