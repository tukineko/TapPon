#ifndef __Barrel_H__
#define __Barrel_H__

#include "Config.h"

USING_NS_CC;

class Barrel : public Sprite {
protected:
    Sprite* _hit_area;
    Sprite* _out_box;
    DrawNode* _scope;
    
    float _cnt = 0;

public:
    enum class State {
        STOP = 0,
        MOVING
    };

    Barrel();
    ~Barrel();
    virtual bool init();
    CREATE_FUNC(Barrel);
    void update(float dt);

    //有効な面と衝突したか
    bool CheckHitSurface(Vec2 p);

    //無効な面と衝突したか
    bool CheckOutSurface(Vec2 p);

    CC_SYNTHESIZE(State, _state, State);
    CC_SYNTHESIZE(int, _stageType, StageType);
};

#endif // __Barrel_H__
