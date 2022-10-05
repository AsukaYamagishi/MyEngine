#pragma once
#include <DirectXMath.h>
#include "../Math/Vector3.h"

using namespace DirectX;

class Camera
{
#pragma region 定数
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

#pragma region 関数
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="eye">視点</param>
	/// <param name="target">注視点</param>
	/// <param name="up">上ベクトル</param>
	Camera(Vector3 eye, Vector3 target = { 0,0,0 }, Vector3 up = { 0,1,0 });

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="eye">視点</param>
	/// <param name="target">注視点(0,0,0)</param>
	/// <param name="up">上ベクトル(0,1,0)</param>
	static void Init(const Vector3 eye = { 0,100,100 },
					 const Vector3 target = { 0,0,0 },
					 const Vector3 up = { 0,1,0 });

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();

	/// <summary>
	/// ビュー行列更新
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// 射影行列更新
	/// </summary>
	void UpdateProjectionMatrix();
#pragma endregion

#pragma region ゲッター/セッター
	
	/// <summary>
	/// カメラセット
	/// </summary>
	/// <param name="cam">カメラ情報</param>
	static void SetCam(Camera* cam);

	/// <summary>
	/// ビュー射影行列取得
	/// </summary>
	/// <returns>ビュー射影行列</returns>
	const XMMATRIX& GetViewProjectionMatrix() { return matViewProjection; }
	/// <summary>
	/// 現在のカメラ情報取得
	/// </summary>
	/// <returns>現在のカメラ情報</returns>
	static Camera* GetCam() { return NowMatView; }
	/// <summary>
	/// ビュー行列取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	XMMATRIX GetMatView() { return matView; }
	/// <summary>
	/// プロジェクション行列取得
	/// </summary>
	/// <returns>プロジェクション行列</returns>
	XMMATRIX GetMatProj() { return matProjection; }
#pragma endregion

#pragma region 変数
public:
	Vector3 eye;			//視点座標
	Vector3 target;			//注視点座標
	Vector3 up;				//上方向ベクトル
	Vector3 front;			//正面ベクトル
	Vector3 angle;			//角度

protected:
	//今のカメラ
	static Camera* NowMatView;
	//ビュー行列
	XMMATRIX matView = XMMatrixIdentity();
	//射影行列
	XMMATRIX matProjection = XMMatrixIdentity();
	//ビュー射影行列
	XMMATRIX matViewProjection = XMMatrixIdentity();//現在ののカメラ
#pragma endregion
};

