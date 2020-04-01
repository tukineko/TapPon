#pragma execution_character_set("utf-8")
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

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

    //音データのプレロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("se/flee1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("se/boyon1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("se/bomb1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("se/correct2.mp3");

    //スコア画像はBatchNodeで処理
    _scoreBatchNode = SpriteBatchNode::create("game/number.png");
    this->addChild(_scoreBatchNode);

    //初期値
    _game_state = GameState::PLAYING;
    
    //背景
    auto bg = Sprite::create("game/bg.png");
    bg->setPosition(Vec2(winSizeCenterW, winSizeCenterH));
    this->addChild(bg, (int)mainZOderList::BG);

    //ライフの表示
    this->ViewLife();

    //スコアの表示
    this->ViewScore();

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
    _boxStart = Barrel::create();
    _boxStart->setPosition(Vec2(BOX_START_POS_X, BOX_START_POS_Y));
    _boxStart->setRotation(180);
    _boxStart->setStageType(3);
    this->addChild(_boxStart, (int)mainZOderList::BOX);

    //ゴールタル
    _boxEnd = Barrel::create();
    _boxEnd->setPosition(Vec2(BOX_END_POS_X, BOX_END_POS_Y));
    _boxEnd->setStageType(2);
    this->addChild(_boxEnd, (int)mainZOderList::BOX);

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

    //プレイング以外はストップ
    if (_game_state == GameState::PLAYING) {
        _boxStart->setState(Barrel::State::MOVING);
        _boxEnd->setState(Barrel::State::MOVING);
    }
    else {
        _boxStart->setState(Barrel::State::STOP);
        _boxEnd->setState(Barrel::State::STOP);
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
    Vec2 location = touch->getLocation();

    if (_game_state == GameState::PLAYING) {
        this->TapAction();
    }

    return true;
}

void GameLayer::ViewLife() {
    for (int i = 0; i < _lifeNum; i++) {
        auto sp = Sprite::create("game/life.png");
        sp->setPosition(Vec2(70 + (i * 120), winSizeH - 70));
        this->addChild(sp, (int)mainZOderList::MENU, "life" + std::to_string(i + 1));
    }
}

void GameLayer::ViewScore() {
    //scoreの名前がついているノードをすべて削除
    this->enumerateChildren("score", [](Node* node) -> bool {
        auto action = RemoveSelf::create();
        node->runAction(action);
        return false;
    });

    auto score = std::to_string(_score);
    int lang = score.length();
    int numberRect = 64;

    for (int i = 0; i < lang; i++) {
        auto number = Sprite::createWithTexture(_scoreBatchNode->getTexture(), Rect(0, 0, numberRect, numberRect));
        number->setPosition(Vec2((winSizeCenterW + 50) + numberRect * i, winSizeH - 50));
        char c = score[i];
        int num = c - '0';
        number->setTextureRect(Rect(numberRect * num, 0, numberRect, numberRect));
        this->addChild(number, (int)mainZOderList::MENU, "score");
    }
}

void GameLayer::TapAction() {    
    _game_state = GameState::CHECK;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se/bomb1.mp3");

    //ボヨヨン
    _boxStart->runAction(
        Sequence::create(
            ScaleTo::create(0.05f, this->getScaleX(), 0.5f),
            EaseElasticOut::create(ScaleTo::create(0.5f, this->getScaleX(), 1.0f)),
            nullptr
        )
    );

    //キャラクター射出
    _chara = Sprite::create("game/chara.png");
    _chara->setPosition(_boxStart->getPosition());
    _chara->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _chara->setRotation(_boxStart->getRotation() - 180);
    this->addChild(_chara, (int)mainZOderList::CHARA);
    
    auto r = CC_DEGREES_TO_RADIANS(_boxStart->getRotation());
    auto x = -winSizeW * cos(r);
    auto y = winSizeW * sin(r);
    CCLOG("%f, %f", x, y);
    _chara->runAction(MoveBy::create(0.5f, Vec2(x, y)));

}

void GameLayer::CheckChara() {
    auto chara_rect = _chara->getBoundingBox();
    auto charaPos = _chara->getPosition();
    
    //タルとの衝突
    _boxEnd->setState(Barrel::State::STOP);
    if (_boxEnd->CheckHitSurface(charaPos)) {
        this->ClearAnime();
    }
    if (_boxEnd->CheckOutSurface(charaPos)) {
        this->MissAnime2();
    }

    //右壁との衝突
    if (charaPos.x < 0 || charaPos.x > winSizeW || charaPos.y < 0 || charaPos.y > winSizeH) {
        this->MissAnime();
    }
}

void GameLayer::ClearAnime() {
    _game_state = GameState::CLEAR;

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se/correct2.mp3");

    _score++;
    this->ViewScore();

    _chara->stopAllActions();
    _chara->removeFromParent();

    _boxEnd->runAction(
        Sequence::create(
            ScaleTo::create(0.05f, 0.5f, this->getScaleY()),
            EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, this->getScaleY())),
            CallFunc::create([=]() {
                this->NextStage();
            }),
            nullptr
        )
    );
}

void GameLayer::MissAnime() {
    _game_state = GameState::MISS;
    _chara->removeFromParent();

    //失敗時のSE
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se/flee1.mp3");

    //ライフのアニメーション
    auto tag_name = "life" + std::to_string(_lifeNum);
    auto life = this->getChildByName(tag_name);
    life->runAction(
        Sequence::create(
            Spawn::create(
                MoveBy::create(0.2f, Vec2(0, 5)),
                FadeOut::create(0.2f),
                nullptr
            ),
            CallFunc::create([=]() {
                _lifeNum--;
                if (_lifeNum == 0) {
                    this->GameOverAnime();
                }else {
                    _game_state = GameState::PLAYING;
                }
            }),
            RemoveSelf::create(),
            nullptr
        )
    );
}

void GameLayer::MissAnime2() {
    _game_state = GameState::MISS;
    _chara->stopAllActions();

    //失敗時のSE
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se/boyon1.mp3");

    _chara->runAction(
        Sequence::create(
            Spawn::create(
                MoveBy::create(0.2f, Vec2(-500, 0)),
                RotateBy::create(0.2f, 720),
                FadeOut::create(0.2f),
                nullptr
            ),
            RemoveSelf::create(),
            nullptr
        )
    );

    //ライフのアニメーション
    auto tag_name = "life" + std::to_string(_lifeNum);
    auto life = this->getChildByName(tag_name);
    life->runAction(
        Sequence::create(
            Spawn::create(
                MoveBy::create(0.2f, Vec2(0, 5)),
                FadeOut::create(0.2f),
                nullptr
            ),
            CallFunc::create([=]() {
                _lifeNum--;
                if (_lifeNum == 0) {
                    this->GameOverAnime();
                }
                else {
                    _game_state = GameState::PLAYING;
                }
            }),
            RemoveSelf::create(),
        nullptr
        )
    );
}

void GameLayer::GameOverAnime() {
    _game_state = GameState::GAMEOVER;

    auto sp = Sprite::create("game/gameover.png");
    sp->setPosition(Vec2(winSizeCenterW, winSizeH + 80));
    this->addChild(sp, (int)mainZOderList::TEXT);

    sp->runAction(
        Sequence::create(
            EaseBackOut::create(MoveTo::create(0.5f, Vec2(winSizeCenterW, winSizeCenterH))),
            nullptr
        )
    );

    auto labelBtnLabel1 = Label::createWithSystemFont("ReStart", "Arial", 48);
    auto mItem1 = MenuItemLabel::create(labelBtnLabel1, CC_CALLBACK_0(GameLayer::nextSceneCallback, this));
    mItem1->setPosition(Vec2(winSizeCenterW, winSizeCenterH - 200));
    mItem1->setAnchorPoint(Point::ZERO);
    mItem1->setColor(Color3B::BLUE);

    auto menu = Menu::create(mItem1, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, (int)mainZOderList::MENU);
}

void GameLayer::NextStage() {
    _game_state = GameState::NEXT;

    auto next = Barrel::create();
    next->setPosition(Vec2(BOX_NEXT_POS_X, BOX_NEXT_POS_Y));
    next->setStageType(3);
    this->addChild(next, (int)mainZOderList::BOX);

    next->runAction(
        Sequence::create(
            MoveTo::create(0.2f, Vec2(BOX_END_POS_X, BOX_END_POS_Y)),
            nullptr
        )
    );

    _boxStart->runAction(
        Sequence::create(
            MoveTo::create(0.2f, Vec2(-110, winSizeCenterH)),
            RemoveSelf::create(),
            nullptr
        )
    );

    _boxEnd->runAction(
        Sequence::create(
            Spawn::create(
                MoveTo::create(0.2f, Vec2(BOX_START_POS_X, BOX_START_POS_Y)),
                RotateTo::create(0.2f, 180),
                nullptr
            ),
            CallFunc::create([=]() {
                _boxStart = _boxEnd;
                _boxStart->setStageType(0);
                _boxEnd = next;
                _game_state = GameState::PLAYING;
            }),
            nullptr
        )
    );

}

void GameLayer::nextSceneCallback() {
    
}