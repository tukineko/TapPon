#pragma execution_character_set("utf-8")
#include "TitleLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TitleLayer::createScene()
{
    Scene* scene = Scene::create();
    TitleLayer* layer = TitleLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TitleLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------TitleLayer::init()----------------");

    
    //背景
    auto bg = LayerColor::create(Color4B(109, 195, 236, 255), winSizeW, winSizeH);
    this->addChild(bg, (int)mainZOderList::BG);


    return true;
}

void TitleLayer::onEnterTransitionDidFinish()
{
    
}

void TitleLayer::nextSceneCallback() {
    
}