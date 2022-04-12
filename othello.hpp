#pragma once
#include <vector>
#include <utility>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

template<class T> struct vec2d{
    T x;
    T y;

    vec2d(int x,int y):x(x),y(y){}
    vec2d(const vec2d &v){
        this->x = v.x;
        this->y = v.y;
    }
    vec2d():x(-1),y(-1){}
    vec2d operator - () const{
        return vec2d(-this->x, -this->y);
    }
    vec2d operator + (const vec2d &p2) const{
        return vec2d(this->x+p2.x,this->y+p2.y);
    }
    vec2d operator - (const vec2d &p2) const{
        return vec2d(this->x-p2.x,this->y-p2.y);
    }
    vec2d operator += (const vec2d &p2){
        this->x+=p2.x;
        this->y+=p2.y;
        return *this;
    }
    vec2d operator -= (const vec2d &p2){
        this->x-=p2.x;
        this->y-=p2.y;
        return *this;
    }
};

class GameOthello{
    private:
    int searchAble(vec2d<int>, vec2d<int>);
    int searchAble(vec2d<int>, vec2d<int>, std::vector<vec2d<int>>& );
    int change_stones(vec2d<int> pos,vec2d<int> vec);
    public:
    int board[8][8]={}; //現在の盤面
    int turn=BLACK; //現在のターン
    int able[8][8]={}; //石を置ける場所と返せる数
    std::vector<std::vector<vec2d<int>>> reverse_stones[8][8]; //石を置いたときにひっくり返る石のリスト
    bool state_pass=false;
    bool state_gameset=false;
    

    GameOthello();
    void updateAble(void);
    bool put_able(int,int);
    bool put_stone(int,int);
    void changeTurn(void);
    bool updatePass(void);

};