#include "othello.hpp"
#include <stdio.h>

GameOthello::GameOthello(){
    board[3][3]=BLACK;
    board[3][4]=WHITE;
    board[4][3]=WHITE;
    board[4][4]=BLACK;
}

vec2d<int> vec[8]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
void GameOthello::updateAble(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j]==EMPTY){
                vec2d<int> pos(i,j);
                int count=0;
                std::vector<std::vector<vec2d<int>>> reverse_stones_ij; //i,jに石を置いたときにひっくり返る石
                for(int k=0;k<8;k++){
                    std::vector<vec2d<int>> list;
                    int res=GameOthello::searchAble(pos+vec[k],vec[k],list);
                    reverse_stones_ij.push_back(list);
                    if(res!=-1){
                        count+=res;
                    }
                }
                reverse_stones[i][j]=reverse_stones_ij;
                able[i][j]=count;
            }
			else able[i][j]=0;
        }
    }
}

int GameOthello::searchAble(vec2d<int> pos, vec2d<int> vec){
    if((pos.x<0 || 8<=pos.x) || (pos.y<0 || 8<=pos.y)){
        return -1;
    }
    if(board[pos.x][pos.y]==EMPTY) return -1;
    if(board[pos.x][pos.y]==turn) return 0;
    else{
        int res=searchAble(pos+vec,vec);
        if(res==-1) return -1;
        else return ++res;
    }
}

int GameOthello::searchAble(vec2d<int> pos, vec2d<int> vec, std::vector<vec2d<int>>& list){
    if((pos.x<0 || 8<=pos.x) || (pos.y<0 || 8<=pos.y)){
        return -1;
    }
    if(board[pos.x][pos.y]==EMPTY) return -1;
    if(board[pos.x][pos.y]==turn) return 0;
    else{
        int res=searchAble(pos+vec,vec,list);
        if(res==-1) return -1;
        else {
            list.push_back(pos);
            return ++res;
        }
    }
}

bool GameOthello::put_able(int x,int y){
    if(able[x][y]>0) return true;
    else return false;
}

int GameOthello::change_stones(vec2d<int> pos,vec2d<int> vec){
    for(auto list:reverse_stones[pos.x][pos.y]){
        if(list.empty()) continue;
        for(auto vec:list){
            printf("(%d,%d)\n",vec.x,vec.y);
        }
        printf("\n");
    }
    if((pos.x<0 || 8<=pos.x) || (pos.y<0 || 8<=pos.y)){
        return -1;
    }
    if(board[pos.x][pos.y]==EMPTY) return -1;
    if(board[pos.x][pos.y]==turn) return 0;
    else{
        int res=change_stones(pos+vec,vec);
        if(res==-1) return -1;
        else{
			printf("chahge:%d,%d\n",pos.x,pos.y);
            if(board[pos.x][pos.y]==BLACK) board[pos.x][pos.y]=WHITE;
            else if(board[pos.x][pos.y]==WHITE) board[pos.x][pos.y]=BLACK;
            return ++res;
        }
    }
}
bool GameOthello::put_stone(int x,int y){
	if(!((0<=x&&x<8)&&(0<=y&&y<8))) return false;
    if(!put_able(x,y)) return false;
    else{
        board[x][y]=turn;
        vec2d<int> pos(x,y);
        for(int i=0;i<8;i++){
            change_stones(pos+vec[i],vec[i]);
        }
        changeTurn();
        return true;
    }
}

void GameOthello::changeTurn(){
    if(turn==BLACK) turn=WHITE;
    else if(turn==WHITE) turn=BLACK;
}

bool GameOthello::updatePass(){
	updateAble();
	int sum=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			sum+=able[i][j];
		}
	}
	int sum2=0;
	changeTurn();
	updateAble();
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++){
		sum2+=able[i][j];
	}
	changeTurn();
	updateAble();

	if(sum==0){
		if(sum2==0) return state_gameset=true;
		else return state_pass=true;
	}
	else return state_pass=false;
}