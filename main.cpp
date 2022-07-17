#include"WindowsAPI.h"  //ウィンドウ表示
#include"KeyboardInput.h"  //キーボード入力
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
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG


	////DirectX初期化処理　ここから
		
	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

	//初期化
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	//カメラ
	Camera* camera = nullptr;
	

	ModelInput::StaticInitialize(dxCommon->GetDevice());
	ModelManager::GetIns()->Initialize();

	
	////DirectInput(入力)初期化処理
	KeyboardInput* input = KeyboardInput::GetInstance();
	input->Init(win->hwnd);

	////DirectX初期化処理　ここまで


	////描画初期化処理　ここから
#pragma region スプライト/3Dオブジェクト静的初期化
	// スプライト静的初期化
	if (!Sprite::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	if (!CalculationObject::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	if (!ParticleManager::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	
#pragma endregion

#pragma region 3Dモデル静的初期化
	// Obj
	if (!ModelDraw::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// FBX
	FbxInput::GetInstance()->Init(dxCommon->GetDevice());

#pragma endregion
	

#pragma region ゲームシーン初期化
	
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Init(dxCommon, input, audio);

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
		input->Update();
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
		postEffect->Draw(dxCommon->GetCommandList());
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

