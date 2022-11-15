#pragma once
#include "../GameObjectBase.h"
#include "../../DirectXBase/DebugText.h"
#include "../../DirectXBase/DirectXCommon.h"

class ScoreManager :
    public GameObjectBase
{
public:
    ScoreManager(DirectXCommon* dxCommon, DebugText* debugText);

    void Draw() override;

    void AddScore(int add);
    void SubScore(int sub);

private:
    DebugText* debugText;
    int score = 0;
    

};

