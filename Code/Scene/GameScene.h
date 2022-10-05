#pragma once
#include "../DIrectXBase/SafeDelete.h"
#include "../DirectXBase/DirectXCommon.h"
#include <DirectXMath.h>
#include "../Sprite.h"
#include "../DirectXBase/DebugText.h"
#include "../Audio/Audio.h"
#include "../Input/KeyboardInput.h"
#include <vector>
#include "../GameObject/Player/PlayerBase.h"
#include "../Collision/Collision.h"
#include "../3d/Fbx/FbxDraw.h"
#include "../GameObject/Enemy/Boss.h"
#include "../2d/Particle/ParticleManager.h"
#include "../Stage.h"
#include "../Manager/GameObjectManager.h"
#include "../Collision/CollisionManager.h"
#include "../Scene/AbstructScene.h"
#include "../GameObject/Enemy/EnemySpawner.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class GameScene:
	public AbstructScene
{
#pragma region 変数
private: //静的メンバ変数
	//デバッグテキスト用のテクスチャ
	static const int debugTextTexNum = 0;

private: //メンバ変数
	DirectXCommon *dxCommon = nullptr;
	Audio *audio = nullptr;
	Camera *camera = nullptr;
	DebugText debugText;
	Sprite *spriteBG;
	std::shared_ptr<GameObjectManager> gameObjManager;
	std::shared_ptr<CollisionManager> collisionManager;

	//ゲームシーン用
	Sprite *sprite = nullptr;
	//音楽
	Audio::SoundData soundData[3];

	//プレイヤー
	PlayerBase* player;	

	
	//ステージ
	Stage* stage;


	//FBXモデル
	std::unique_ptr<FbxModel> testModel = nullptr;
	FbxDraw *testObject = nullptr;

	std::unique_ptr<FbxModel> boxModel = nullptr;
	FbxDraw* boxObject = nullptr;

	//パーティクル
	ParticleManager* particleMan = nullptr;


	//敵
	//Enemy* enemy;

	float angle = 3.14f / 2.0f;

	float radius = XMConvertToRadians(2.0f);

public:
	//ゲームシーン終了用
	bool gameEndFlag = false;

#pragma endregion

#pragma region 静的メンバ関数

private: //静的メンバ関数
public: //静的メンバ関数
#pragma endregion

#pragma region ゲッター/セッター

#pragma endregion

#pragma region メンバ関数

private: //メンバ関数
	int timer = 0;	// フレーム数
public: //メンバ関数
	//コンストラクタ
	GameScene(DirectXCommon* dxCommon, Audio* audio);
	//デストラクタ
	~GameScene();
	//初期化
	void Init() override;
	//毎フレーム更新処理
	void Update()override;
	//描画
	void Draw()override;
#pragma endregion

};

