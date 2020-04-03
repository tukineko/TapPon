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
    
    //音データのプレロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("se/bomb1.mp3");

    //背景
    auto bg = Sprite::create("game/bg.png");
    bg->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(bg, (int)mainZOderList::BG);

    _title = Sprite::create("title/title.png");
    _title->setPosition(Vec2(winSizeCenterW, winSizeCenterH + 200));
    this->addChild(_title, (int)mainZOderList::TITLE);

    _start = Sprite::create("title/start.png");
    _start->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(_start, (int)mainZOderList::TITLE);
    _start->runAction(
        RepeatForever::create(
            Sequence::create(
                FadeOut::create(0.3f),
                FadeIn::create(0.3f),
                nullptr
            )
        )
    );

    for (int i = 0; i < 6; i++) {
        auto sp = Sprite::create("game/box.png");
        sp->setPosition(Vec2(winSizeCenterW, winSizeCenterH - 200));
        sp->setRotation(-90);
        this->addChild(sp, (int)mainZOderList::BOX);
        _sp.pushBack(sp);
    }

    //タッチイベントの設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void TitleLayer::onEnterTransitionDidFinish()
{
    
}

bool TitleLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    this->nextSceneCallback();

    return true;
}

void TitleLayer::nextSceneCallback() {
    this->getEventDispatcher()->setEnabled(false);

    _title->runAction(
        Sequence::create(
            EaseOut::create(MoveBy::create(0.5f, Vec2(0, 300)), 2.0f),
            RemoveSelf::create(),
            nullptr
        )
    );

    _start->removeFromParent();

    auto i = 0;
    for (auto sp : _sp) {
        sp->runAction(
            Sequence::create(
                EaseIn::create(MoveTo::create(0.5f, Vec2(winSizeCenterW - 500 + (200 * i), winSizeCenterH - 200)), 2.0f),
                DelayTime::create(0.3f),
                CallFuncN::create(CC_CALLBACK_1(TitleLayer::doAnime, this, i)),
                nullptr
            )
        );
        i++;
    }
}

void TitleLayer::doAnime(cocos2d::Ref* ref, int i) {
    auto sp = dynamic_cast<Sprite*>(ref);
    auto pos = sp->getPosition();
    sp->runAction(
        Sequence::create(
            DelayTime::create(i * 0.2f),
            CallFunc::create([]() {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se/bomb1.mp3");
            }),
            ScaleTo::create(0.05f, 0.5f, 1.0f),
            CallFunc::create([=]() {
                auto chara = Sprite::create("game/chara.png");
                chara->setPosition(pos);
                chara->setRotation(-90);
                this->addChild(chara, (int)mainZOderList::CHARA);
                chara->runAction(MoveBy::create(0.5f, Vec2(0, winSizeH)));

                auto star = Sprite::create("game/star.png");
                star->setPosition(Vec2(pos.x - 50, pos.y + 110));
                star->setScale(0.5f);
                this->addChild(star, (int)mainZOderList::BOX);
                star->runAction(
                    Sequence::create(
                        Spawn::create(
                            ScaleTo::create(0.2f, 1.0f),
                            EaseOut::create(MoveBy::create(0.2f, Vec2(-30, 30)), 2.0f),
                            nullptr
                        ),
                        RemoveSelf::create(),
                        nullptr
                    )
                );

                auto star2 = Sprite::create("game/star.png");
                star2->setPosition(Vec2(pos.x - 50, pos.y + 110));
                star2->setScale(0.5f);
                this->addChild(star2, (int)mainZOderList::BOX);
                star2->runAction(
                    Sequence::create(
                        Spawn::create(
                            ScaleTo::create(0.2f, 1.0f),
                            EaseOut::create(MoveBy::create(0.2f, Vec2(-30, -30)), 2.0f),
                            nullptr
                        ),
                        RemoveSelf::create(),
                        nullptr
                    )
                );

                auto star3 = Sprite::create("game/star.png");
                star3->setPosition(Vec2(pos.x + 50, pos.y + 110));
                star3->setScale(0.5f);
                this->addChild(star3, (int)mainZOderList::BOX);
                star3->runAction(
                    Sequence::create(
                        Spawn::create(
                            ScaleTo::create(0.2f, 1.0f),
                            EaseOut::create(MoveBy::create(0.2f, Vec2(30, 30)), 2.0f),
                            nullptr
                        ),
                        RemoveSelf::create(),
                        nullptr
                    )
                );

                auto star4 = Sprite::create("game/star.png");
                star4->setPosition(Vec2(pos.x + 50, pos.y + 110));
                star4->setScale(0.5f);
                this->addChild(star4, (int)mainZOderList::BOX);
                star4->runAction(
                    Sequence::create(
                        Spawn::create(
                            ScaleTo::create(0.2f, 1.0f),
                            EaseOut::create(MoveBy::create(0.2f, Vec2(30, -30)), 2.0f),
                            nullptr
                        ),
                        RemoveSelf::create(),
                        nullptr
                    )
                );
            }),
            EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, 1.0f)),
            CallFunc::create([=]() {
                if (i == 5) {
                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene(), Color3B::WHITE));
                }
            }),
            nullptr
        )
    );
}