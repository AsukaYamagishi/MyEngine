#include "DirectXBase/WindowsAPI.h"  //ウィンドウ表示
#include "DirectXBase/DebugText.h" //デバッグテキスト
#include "DirectXBase/DirectXCommon.h"
#include "DirectXBase/SafeDelete.h"
#include "Input/KeyboardInput.h"  //キーボード入力
#include "Input/ControllerInput.h" //ゲームパッド入力
#include "Audio/Audio.h" //音楽再生
#include "Camera/Camera.h"
#include "Manager/SceneManager.h"
#include "Manager/ModelManager.h"
#include "2d/Sprite.h"  //2D画像(sprite)
#include "2d/PostEffect/PostEffect.h"
#include "2d/PostEffect/MultiRenderTarget.h"
#include "3d/CalculationModel.h"  //3Dオブジェクト(Object)
#include "3d/Obj/ObjDraw.h"
#include "3d/Fbx/FbxLoader.h"

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
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG

#pragma region DirectX初期化
	////DirectX初期化処理　ここから
	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

#ifdef _DEBUG
	//エラー絶対炙り出すマン
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); //やばいエラーで止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); //エラーで止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true); //warningで止まる
	}
#endif // _DEBUG

	//オーディオ生成
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	//カメラ生成
	Camera* camera = nullptr;
	
	//入力機器関係初期化
	KeyboardInput::GetIns()->Init(win->hwnd);
	ControllerInput::GetIns()->Init();


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
	if (!CalculationModel::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	if (!ParticleManager::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

#pragma endregion

#pragma region 3Dモデル静的初期化
	// Obj
	ObjLoader::StaticInit(dxCommon->GetDevice());
	if (!ObjDraw::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	// FBX
	FbxLoader::GetIns()->Init(dxCommon->GetDevice());

	//モデルマネージャ
	ModelManager::GetIns()->Init();
#pragma endregion
	
#pragma region ゲームシーン初期化
	
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager(dxCommon, audio);
	sceneManager->Init();

#pragma endregion

	
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
		KeyboardInput::GetIns()->Update();
		ControllerInput::GetIns()->Update();
		sceneManager->Update();
#pragma endregion
		
#pragma region 描画コマンド
		//描画前処理
		dxCommon->PreDraw();

		sceneManager->Draw(); //ゲームシーン描画

		//描画終了
		dxCommon->PostDraw();
#pragma endregion

		//Escキーを押したらゲームを終了する
		if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_ESCAPE)) break;

		////////////////DirectX毎フレーム処理 ここまで
	}

	//解放処理
	FbxLoader::GetIns()->Fin();

	//クラス(new)の消去
	safe_delete(dxCommon);
	safe_delete(audio);
	safe_delete(sceneManager);

	//ウィンドウクラスを登録解除
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	return 0;
}