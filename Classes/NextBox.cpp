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

    _out_box = Sprite::create();
    _out_box->setTextureRect(Rect(0, 0, 216, 10));
    _out_box->setColor(Color3B(255, 0, 0));
    _out_box->setOpacity(128);
    _out_box->setAnchorPoint(Point::ZERO);
    _out_box->setPosition(Vec2(0, 10));
    this->addChild(_out_box);

    _out_box2 = Sprite::create();
    _out_box2->setTextureRect(Rect(0, 0, 216, 10));
    _out_box2->setColor(Color3B(255, 0, 0));
    _out_box2->setOpacity(128);
    _out_box2->setAnchorPoint(Point::ZERO);
    _out_box2->setPosition(Vec2(0, 166));
    this->addChild(_out_box2);

    _out_box3 = Sprite::create();
    _out_box3->setTextureRect(Rect(0, 0, 10, 170));
    _out_box3->setColor(Color3B(255, 0, 0));
    _out_box3->setOpacity(128);
    _out_box3->setAnchorPoint(Point::ZERO);
    _out_box3->setPosition(Vec2(220, 10));
    this->addChild(_out_box3);

    scheduleUpdate();

    return true;
}

void NextBox::update(float dt) {

    if (_state == State::STOP) {
        return;
    }

    _nextBoxTime += dt;
    if (_stageType == 1) {
        this->setPositionY(this->getPositionY() + (cos(PI * 0.5 * _nextBoxTime) * 5));
        CCLOG("%f", this->getRotation() + (cos(PI * 0.5 * _nextBoxTime) * 1));
        this->setRotation(this->getRotation() + (cos(PI * 0.5 * _nextBoxTime) * 1));
    }
}

bool NextBox::CheckHitSurface(Vec2 p) {
    if (_hit_area->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    return false;
}

bool NextBox::CheckOutSurface(Vec2 p) {
    if (_out_box->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    if (_out_box2->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    if (_out_box3->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    return false;
}
