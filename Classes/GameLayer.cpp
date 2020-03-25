#pragma execution_character_set("utf-8")
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

#define PI 3.14159265358979323846

USING_NS_CC;

Scene* GameLayer::createScene()
{
    Scene* scene = Scene::create();
    GameLayer* layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("----------------GameLayer::init()----------------");

    
    //背景
    auto bg = Sprite::create("game/bg.png");
    bg->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(bg, (int)mainZOderList::BG);

    //雲手前
    _cloud_front1 = Sprite::create("game/cloud_front.png");
    _cloud_front1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_front1->setPosition(Vec2(0, 0));
    this->addChild(_cloud_front1, (int)mainZOderList::CLOUD_FRONT);
    
    _cloud_front2 = Sprite::create("game/cloud_front.png");
    _cloud_front2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_front2->setPosition(Vec2(winSizeW, 0));
    this->addChild(_cloud_front2, (int)mainZOderList::CLOUD_FRONT);

    //雲中間
    _cloud_back1 = Sprite::create("game/cloud_back1.png");
    _cloud_back1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back1->setPosition(Vec2(70, winSizeH - 115));
    this->addChild(_cloud_back1, (int)mainZOderList::CLOUD_BACK2);

    _cloud_back2 = Sprite::create("game/cloud_back1.png");
    _cloud_back2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back2->setPosition(Vec2(520, winSizeH - 260));
    this->addChild(_cloud_back2, (int)mainZOderList::CLOUD_BACK2);

    _cloud_back3 = Sprite::create("game/cloud_back1.png");
    _cloud_back3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back3->setPosition(Vec2(1170, winSizeH - 160));
    this->addChild(_cloud_back3, (int)mainZOderList::CLOUD_BACK2);

    //雲最奥
    _cloud_back4 = Sprite::create("game/cloud_back2.png");
    _cloud_back4->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back4->setPosition(Vec2(277, winSizeH - 200));
    this->addChild(_cloud_back4, (int)mainZOderList::CLOUD_BACK1);

    _cloud_back5 = Sprite::create("game/cloud_back2.png");
    _cloud_back5->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back5->setPosition(Vec2(710, winSizeH - 100));
    this->addChild(_cloud_back5, (int)mainZOderList::CLOUD_BACK1);

    _cloud_back6 = Sprite::create("game/cloud_back2.png");
    _cloud_back6->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _cloud_back6->setPosition(Vec2(1110, winSizeH - 210));
    this->addChild(_cloud_back6, (int)mainZOderList::CLOUD_BACK1);

    //自機タル
    _boxStart = Sprite::create("game/box.png");
    _boxStart->setPosition(Vec2(300, winSizeCenterH));
    this->addChild(_boxStart, (int)mainZOderList::BOX);

    //ゴールタル
    _boxEnd = Sprite::create("game/box.png");
    _boxEnd->setPosition(Vec2(1100, winSizeCenterH));
    this->addChild(_boxEnd, (int)mainZOderList::BOX);

    _game_state = GameState::PLAYING;

    this->scheduleUpdate();

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void GameLayer::onEnterTransitionDidFinish()
{
    
}

void GameLayer::update(float dt) {
    this->CloudAnime();

    if (_game_state == GameState::PLAYING) {
        _boxEndTime += dt;
        _boxEnd->setPositionY(_boxEnd->getPositionY() + (cos(PI * 0.5 * _boxEndTime) * 5));
    }

    if (_game_state == GameState::CHECK) {
        //当たり判定
        this->CheckChara();
    }
}

void GameLayer::CloudAnime() {
    _cloud_front1->setPositionX(_cloud_front1->getPositionX() - 5);
    _cloud_front2->setPositionX(_cloud_front2->getPositionX() - 5);

    if (_cloud_front2->getPositionX() < 0) {
        // 背景Aが画面左外に出きった場合、背景Aを背景Bの右隣に移す
        _cloud_front1->setPositionX(winSizeW);

        // 背景AとBの変数を入れ替える
        auto tmp = _cloud_front2;
        _cloud_front2 = _cloud_front1;
        _cloud_front1 = tmp;
    }

    _cloud_back1->setPositionX(_cloud_back1->getPositionX() - 2);
    if (_cloud_back1->getPositionX() < 0 - _cloud_back1->getContentSize().width) {
        _cloud_back1->setPositionX(winSizeW);
    }

    _cloud_back2->setPositionX(_cloud_back2->getPositionX() - 2);
    if (_cloud_back2->getPositionX() < 0 - _cloud_back2->getContentSize().width) {
        _cloud_back2->setPositionX(winSizeW);
    }

    _cloud_back3->setPositionX(_cloud_back3->getPositionX() - 2);
    if (_cloud_back3->getPositionX() < 0 - _cloud_back3->getContentSize().width) {
        _cloud_back3->setPositionX(winSizeW);
    }

    _cloud_back4->setPositionX(_cloud_back4->getPositionX() - 1);
    if (_cloud_back4->getPositionX() < 0 - _cloud_back4->getContentSize().width) {
        _cloud_back4->setPositionX(winSizeW);
    }

    _cloud_back5->setPositionX(_cloud_back5->getPositionX() - 1);
    if (_cloud_back5->getPositionX() < 0 - _cloud_back5->getContentSize().width) {
        _cloud_back5->setPositionX(winSizeW);
    }

    _cloud_back6->setPositionX(_cloud_back6->getPositionX() - 1);
    if (_cloud_back6->getPositionX() < 0 - _cloud_back6->getContentSize().width) {
        _cloud_back6->setPositionX(winSizeW);
    }
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    if (_game_state == GameState::PLAYING) {
        this->TapAction();
    }

    return true;
}

void GameLayer::TapAction() {
    
    _game_state = GameState::CHECK;
    
    _boxStart->runAction(
        Sequence::create(
            ScaleTo::create(0.05f, this->getScaleX(), 0.5f),
            EaseElasticOut::create(ScaleTo::create(0.5f, this->getScaleX(), 1.0f)),
            nullptr
        )
    );

    _chara = Sprite::create("game/chara.png");
    _chara->setPosition(_boxStart->getPosition());
    this->addChild(_chara, (int)mainZOderList::CHARA);
    _chara->runAction(
        Sequence::create(
            MoveBy::create(0.5f, Vec2(winSizeW, 0)),
            //RemoveSelf::create(),
            nullptr
        )
    );

}

void GameLayer::CheckChara() {
    auto rect = _chara->boundingBox();
    auto rect2 = Rect(winSizeW, 0, 10, winSizeH);

    if (rect.intersectsRect(rect2) ){

        //trueの場合に、何かしらの処理を行う
        CCLOG("hit");
    }
}

void GameLayer::nextSceneCallback() {
    
}