#include "othello.hpp"
#include <bits/stdc++.h>

using namespace std;

void print(GameOthello *GO){
    printf(" ");
    for(int i=0;i<8;i++) printf("%d",i); printf("\n");
    for(int i=0;i<8;i++){
        printf("%d",i);
        for(int j=0;j<8;j++){
            switch(GO->board[i][j]){
                case EMPTY:
                    if(GO->able[i][j]) printf("*");
                    else printf("-");
                    break;
                case BLACK:
                    printf("B");
                    break;
                case WHITE:
                    printf("W");
                    break;
            }
        }
        printf("\n");
    }
}

int main(){
    GameOthello othello;


    int x,y;
    //Game Loop
    while(1){
        othello.updatePass();
        if(othello.state_gameset){
            printf("\nGAME SET\n");
            break;
        }
        if(othello.state_pass){
            printf("\nPASS\n");
            othello.changeTurn();
            continue;
        }
        
        printf("turn=%s\n",othello.turn==BLACK?"BLACK":"WHITE");
        print(&othello);
        scanf("%d%d",&x,&y);
        bool res = othello.put_stone(x,y);
        printf("%s\n",res?"YES":"NO");
        
        printf("\n");
    }
}