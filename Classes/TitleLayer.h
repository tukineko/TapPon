#ifndef __TitleLayer_H__
#define __TitleLayer_H__

#include "Config.h"

USING_NS_CC;

class TitleLayer : public Layer
{
private:
    enum class mainZOderList {
        BG = 0,
        MAME,
        TITLE,
        SCORE,
        MENU
    };

    

public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleLayer);
    virtual void onEnterTransitionDidFinish();

    void nextSceneCallback();
};

#endif // __TitleLayer_H__
