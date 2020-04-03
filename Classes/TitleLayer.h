#ifndef __TitleLayer_H__
#define __TitleLayer_H__

#include "Config.h"
#include "GameLayer.h"

USING_NS_CC;

class TitleLayer : public Layer
{
private:
    enum class mainZOderList {
        BG = 0,
        CHARA,
        BOX,
        TITLE,
        MENU
    };

    Sprite* _title;
    Sprite* _start;

    Vector<Sprite*> _sp;

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleLayer);
    virtual void onEnterTransitionDidFinish();
    bool onTouchBegan(Touch* touch, Event* event);

    void nextSceneCallback();
    void doAnime(cocos2d::Ref* ref, int i);
};

#endif // __TitleLayer_H__
