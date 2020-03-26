#pragma execution_character_set("utf-8")
#include "NextBox.h"

//コンストラクター
//作成されるときに起こる処理
//:以降で数値の初期化をすることが出来る
NextBox::NextBox() :_state(State::MOVING)
{
}

//デストラクター
//このクラスが終わるときに起こる処理
NextBox::~NextBox()
{
}

bool NextBox::init()
{
    if (!Sprite::initWithFile("game/box.png")) return false;
    this->setFlippedX(true);

    _hit_area = Sprite::create();
    _hit_area->setTextureRect(Rect(0, 0, 15, 130));
    _hit_area->setColor(Color3B(0, 255, 0));
    _hit_area->setOpacity(128);
    _hit_area->setAnchorPoint(Point::ZERO);
    _hit_area->setPosition(Vec2(0, 28));
    this->addChild(_hit_area);

    auto out_box = Sprite::create();
    out_box->setTextureRect(Rect(0, 0, 216, 10));
    out_box->setColor(Color3B(255, 0, 0));
    out_box->setOpacity(128);
    out_box->setAnchorPoint(Point::ZERO);
    out_box->setPosition(Vec2(0, 10));
    this->addChild(out_box);

    auto out_box2 = Sprite::create();
    out_box2->setTextureRect(Rect(0, 0, 216, 10));
    out_box2->setColor(Color3B(255, 0, 0));
    out_box2->setOpacity(128);
    out_box2->setAnchorPoint(Point::ZERO);
    out_box2->setPosition(Vec2(0, 166));
    this->addChild(out_box2);

    auto out_box3 = Sprite::create();
    out_box3->setTextureRect(Rect(0, 0, 10, 170));
    out_box3->setColor(Color3B(255, 0, 0));
    out_box3->setOpacity(128);
    out_box3->setAnchorPoint(Point::ZERO);
    out_box3->setPosition(Vec2(220, 10));
    this->addChild(out_box3);

    scheduleUpdate();

    return true;
}

void NextBox::update(float dt) {
    _nextBoxTime += dt;

    if (_state == State::STOP) {
        return;
    }

    if (_stageType == 1) {
        this->setPositionY(this->getPositionY() + (cos(PI * 0.5 * _nextBoxTime) * 5));
    }
}

void NextBox::CheckHitArea(Vec2 p) {
    
    auto pos = _hit_area->getPosition();
    auto parent = this->getParent();
    auto absolutePoint = parent->convertToWorldSpace(pos);
    CCLOG("x:%f, y:%f", absolutePoint.x, absolutePoint.y);
    /*auto r = _hit_area->getBoundingBox();
    if (r.containsPoint(p)) {
        CCLOG("hit");
    }*/
}
