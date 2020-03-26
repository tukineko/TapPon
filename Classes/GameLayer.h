#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "Config.h"
#include "NextBox.h"

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
        MENU,
        TEXT
    };

    enum class GameState {
        DEFAULT = 0,
        PLAYING,
        CHECK,
        CLEAR,
        NEXT,
        MISS,
        GAMEOVER,
        RESULT,
    };

    SpriteBatchNode* _scoreBatchNode;

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

    int _lifeNum = 3;
    int _score = 0;
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

    //ライフの表示
    void ViewLife();

    //スコアの表示
    void ViewScore();

    //タップしたときのアクション
    void TapAction();

    //キャラの当たり判定
    void CheckChara();

    //成功したときのアニメーション
    void ClearAnime();

    //ミスしたときのアニメーション
    void MissAnime();

    //ゲームオーバー
    void GameOverAnime();

    //ネクストステージ処理
    void NextStage();

    void nextSceneCallback();
};

#endif // __GameLayer_H__
