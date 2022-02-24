#include <vector>
#include <utility>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

class GameOthello{
    private:
    int searchAble(std::pair<int,int>, std::pair<int,int>);
    public:
    int board[8][8]={}; //現在の盤面
    int turn=BLACK; //現在のターン
    int able[8][8]={}; //石を置ける場所と返せる数
    

    GameOthello();
    void updateAble(void);



};