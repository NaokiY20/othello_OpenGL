#include "othello.h"

GameOthello::GameOthello(){
    board[3][3]=BLACK;
    board[3][4]=WHITE;
    board[4][3]=WHITE;
    board[4][4]=BLACK;
}

void GameOthello::updateAble(){

}

int GameOthello::searchAble(std::pair<int,int> pos, std::pair<int,int> vec){
    if((pos.first<0 || 8<=pos.first) || (pos.second<0 || 8<=pos.second)){
        return -1;
    }
    
}