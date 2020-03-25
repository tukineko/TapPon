#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "Config.h"

USING_NS_CC;

class GameLayer : public Layer
{
private:
    enum class mainZOderList {
        BG = 0,
        CLOUD_BACK1,
        CLOUD_BACK2,
        CHARA,
        BOX,
        CLOUD_FRONT,
        MAME,
        TITLE,
        SCORE,
        MENU
    };

    enum class GameState {
        DEFAULT = 0,
        PLAYING,
        CHECK,
        RESULT,
    };

    GameState _game_state;

    Sprite* _cloud_front1;
    Sprite* _cloud_front2;
    Sprite* _cloud_back1;
    Sprite* _cloud_back2;
    Sprite* _cloud_back3;
    Sprite* _cloud_back4;
    Sprite* _cloud_back5;
    Sprite* _cloud_back6;
    Sprite* _boxStart;
    Sprite* _boxEnd;
    Sprite* _chara;

    float _boxEndTime = 0;


public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual void onEnterTransitionDidFinish();
    void update(float dt);
    bool onTouchBegan(Touch* touch, Event* event);

    //雲のアニメーション
    void CloudAnime();

    //タップしたときのアクション
    void TapAction();

    //キャラとの当たり判定
    void CheckChara();

    void nextSceneCallback();
};

#endif // __GameLayer_H__
