#pragma execution_character_set("utf-8")
#include "Barrel.h"

//コンストラクター
//作成されるときに起こる処理
//:以降で数値の初期化をすることが出来る
Barrel::Barrel() :_state(State::STOP)
{
}

//デストラクター
//このクラスが終わるときに起こる処理
Barrel::~Barrel()
{
}

bool Barrel::init()
{
    if (!Sprite::initWithFile("game/box.png")) return false;
    this->setFlippedX(true);

    _hit_area = Sprite::create();
    _hit_area->setTextureRect(Rect(0, 0, 16, 186));
    _hit_area->setColor(Color3B(0, 255, 0));
    _hit_area->setOpacity(128);
    _hit_area->setAnchorPoint(Point::ZERO);
    _hit_area->setPosition(Vec2(0, 0));
    this->addChild(_hit_area);

    _out_box = Sprite::create();
    _out_box->setTextureRect(Rect(0, 0, 200, 186));
    _out_box->setColor(Color3B(255, 0, 0));
    _out_box->setOpacity(128);
    _out_box->setAnchorPoint(Point::ZERO);
    _out_box->setPosition(Vec2(16, 0));
    this->addChild(_out_box);

    /*_scope = DrawNode::create();
    _scope->drawDot(Vec2::ZERO, 5, Color4F::YELLOW);
    _scope->setPosition(Vec2(-30, 93));
    this->addChild(_scope);*/

    scheduleUpdate();

    return true;
}

void Barrel::update(float dt) {

    if (_state == State::STOP) {
        return;
    }

    _cnt += dt;
    if (_stageType == 0) {
        
    }
    else if (_stageType == 1) {
        this->setPositionY(this->getPositionY() + (cos(PI * 0.5 * _cnt) * 5));
    }
    else if (_stageType == 2) {
        this->setPositionY(this->getPositionY() + (cos(PI * 0.5 * _cnt) * 5));
        //this->setRotation(this->getRotation() + (cos(PI * 0.5 * _cnt) * 1));
    }
    else if (_stageType == 3) {
        this->setRotation(this->getRotation() + 1);
    }
}

bool Barrel::CheckHitSurface(Vec2 p) {
    if (_hit_area->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    return false;
}

bool Barrel::CheckOutSurface(Vec2 p) {
    if (_out_box->getBoundingBox().containsPoint(convertToNodeSpace(p))) {
        return true;
    }

    return false;
}
