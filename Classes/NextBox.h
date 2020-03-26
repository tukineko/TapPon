#ifndef __NextBox_H__
#define __NextBox_H__

#include "Config.h"

USING_NS_CC;

class NextBox : public Sprite {
protected:
    Sprite* _hit_area;
    Sprite* _out_box;
    Sprite* _out_box2;
    Sprite* _out_box3;

    float _nextBoxTime = 0;

public:
    enum class State {
        STOP = 0,
        MOVING
    };

    NextBox();
    ~NextBox();
    virtual bool init();
    CREATE_FUNC(NextBox);
    void update(float dt);

    void CheckHitArea(Vec2 p);

    CC_SYNTHESIZE(State, _state, State);
    CC_SYNTHESIZE(int, _stageType, StageType);
};

#endif // __NextBox_H__
