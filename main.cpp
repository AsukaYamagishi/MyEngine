#include"WindowsAPI.h"  //ウィンドウ表示
#include"KeyboardInput.h"  //キーボード入力
#include"ControllerInput.h" //ゲームパッド入力
#include"Sprite.h"  //2D画像(sprite)
#include"CalculationObject.h"  //3Dオブジェクト(Object)
#include"Audio.h" //音楽再生
#include"DebugText.h" //デバッグテキスト
#include"DirectXCommon.h"
#include"SafeDelete.h"
#include"ModelDraw.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "FbxInput.h"
#include "Camera.h"
#include "PostEffect.h"
#include "MultiRenderTarget.h"


using namespace DirectX;
using namespace Microsoft::WRL;



enum EffectType {
	BASE = 0,
	INV,
	SINPLE,
	BRIGHTNESS,
	CHROMA,
	HUE,
	SCROLL,
	BLUR,
	TILING,
	NOIZE,
	RGB,

	NOEFFECT
};
EffectType type = NOEFFECT;
void ChangeEffectType();
void DrawEffects(DirectXCommon* dxCommon, PostEffect* postEffect);

//Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ
	WindowsAPI* win = nullptr;
	win = new WindowsAPI();
	win->WindowCreate();

	MSG msg{}; //メッセージ


#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG

#pragma region DirecyX初期化
	////DirectX初期化処理　ここから
	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); //やばいエラーで止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); //エラーで止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true); //warningで止まる
	}
#endif // _DEBUG

	//初期化
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	//カメラ
	Camera* camera = nullptr;
	

	ModelInput::StaticInitialize(dxCommon->GetDevice());
	ModelManager::GetIns()->Initialize();

	//入力関係初期化
	KeyboardInput::GetInstance()->Init(win->hwnd);
	ControllerInput::GetInstance()->Init();


	////DirectX初期化処理　ここまで
#pragma endregion

	////描画初期化処理　ここから
#pragma region スプライト/3Dオブジェクト静的初期化
	// スプライト静的初期化
	if (!Sprite::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	if (!CalculationObject::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	if (!ParticleManager::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	
#pragma endregion

#pragma region 3Dモデル静的初期化
	// Obj
	if (!ModelDraw::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	// FBX
	FbxInput::GetInstance()->Init(dxCommon->GetDevice());

#pragma endregion
	

#pragma region ゲームシーン初期化
	
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Init(dxCommon, audio);

#pragma endregion

	PostEffect* postEffect = nullptr;
	//ポストエフェクト初期化
	postEffect = new PostEffect();
	postEffect->Init();

	MultiRenderTarget* multiRT = nullptr;
	//マルチレンダーターゲット初期化
	multiRT = new MultiRenderTarget();
	multiRT->Init();
	
	////描画初期化処理　ここまで

	while (true) //ゲームループ
	{
	#pragma region メッセージ確認
		//メッセージがあるか
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //キー入力メッセージの処理
			DispatchMessage(&msg); //プロシージャにメッセージを送る
		}

		//×ボタンで終了メッセージが来たらゲームループを抜ける
		if (msg.message == WM_QUIT)
		{
			break;
		}
	#pragma endregion

		////////////////DirectX毎フレーム処理 ここから

#pragma region 更新処理
		KeyboardInput::GetInstance()->Update();
		ControllerInput::GetInstance()->Update();
		sceneManager->Update();
#pragma endregion
		
#pragma region 描画コマンド
		//レンダーテクスチャへの描画(ポストエフェクト準備)
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		//multiRT->PreDrawScene(dxCommon->GetCommandList());
		sceneManager->Draw(); //ゲームシーン描画
		postEffect->PostDrawScene(dxCommon->GetCommandList());
		//multiRT->PostDrawScene(dxCommon->GetCommandList());

		//描画前処理
		dxCommon->PreDraw();

		//ポストエフェクト描画
		/*if(input->PressKey(DIK_SPACE))postEffect->Draw(dxCommon->GetCommandList(), "PostEffectTest");
		else postEffect->Draw(dxCommon->GetCommandList(), "InverseColor");*/
		ChangeEffectType();
		DrawEffects(dxCommon, postEffect);
		//multiRT->Draw(dxCommon->GetCommandList());
		//sceneManager->Draw(); //ゲームシーン描画

		//描画終了
		dxCommon->PostDraw();
#pragma endregion

		////////////////DirectX毎フレーム処理 ここまで
	}

	//解放処理
	FbxInput::GetInstance()->Fin();
	delete postEffect;
	delete multiRT;

	//クラス(new)の消去
	safe_delete(dxCommon);
	safe_delete(audio);
	safe_delete(sceneManager);

	//ウィンドウクラスを登録解除
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	return 0;
}

void ChangeEffectType()
{
	if (KeyboardInput::GetInstance()->PressKeyTrigger(DIK_0)) type = BASE;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_1)) type = INV;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_2)) type = SINPLE;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_3)) type = BRIGHTNESS;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_4)) type = CHROMA;
	//else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_5)) type = HUE;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_5)) type = SCROLL;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_6)) type = BLUR;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_7)) type = TILING;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_8)) type = NOIZE;
	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_9)) type = RGB;

	else if(KeyboardInput::GetInstance()->PressKeyTrigger(DIK_RETURN)) type = NOEFFECT;
}

void DrawEffects(DirectXCommon* dxCommon, PostEffect* postEffect)
{

	switch (type)
	{
	case BASE:
		postEffect->Draw(dxCommon->GetCommandList(), "PostEffectTest");
		break;
	case INV:
		postEffect->Draw(dxCommon->GetCommandList(), "InverseColor");
		break;
	case SINPLE:
		postEffect->Draw(dxCommon->GetCommandList(), "SinpleColor");
		break;
	case BRIGHTNESS:
		postEffect->Draw(dxCommon->GetCommandList(), "ChangeBrightness");
		break;
	case CHROMA:
		postEffect->Draw(dxCommon->GetCommandList(), "ChangeChroma");
		break;
	/*case HUE:
		postEffect->Draw(dxCommon->GetCommandList(), "ChangeHue");
		break;*/
	case SCROLL:
		postEffect->Draw(dxCommon->GetCommandList(), "UvScroll");
		break;
	case BLUR:
		postEffect->Draw(dxCommon->GetCommandList(), "PixelBlur");
		break;
	case TILING:
		postEffect->Draw(dxCommon->GetCommandList(), "Tiling");
		break;
	case NOIZE:
		postEffect->Draw(dxCommon->GetCommandList(), "ScanLine");
		break;
	case RGB:
		postEffect->Draw(dxCommon->GetCommandList(), "RGBShift");
		break;

	case NOEFFECT:
		postEffect->Draw(dxCommon->GetCommandList(), "NoEffect");
		break;
	default:
		postEffect->Draw(dxCommon->GetCommandList(), "PostEffectTest");
		break;
	}
}

