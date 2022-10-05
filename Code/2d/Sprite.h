#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXTex.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")
using namespace Microsoft::WRL;
using namespace DirectX;

class Sprite
{
#pragma region 構造体
public: //構造体
	//頂点データ構造体
	struct VertexPosUv
	{
		XMFLOAT3 pos; //xyz
		XMFLOAT2 uv; //uv
	};
	//定数バッファデータ構造体（送りたいデータが増えたらここに書く）
	struct ConstBufferData
	{
		XMFLOAT4 color; //色(RGBA)
		XMMATRIX mat; //3D変換行列
		float time; //時間
	};
#pragma endregion

#pragma region 変数
protected: //静的メンバ変数
	//テクスチャの最大枚数
	static const int spriteSRVCount = 512; //テクスチャの最大枚数
	//頂点数
	static const int vertNum = 4;
	//デバイス
	static ID3D12Device* device;
	//デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	//コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	//デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//射影行列
	static XMMATRIX matProjection;

protected: //メンバ変数
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//テクスチャ番号
	UINT texNumber = 0;
	//Z軸の回転角
	float rotation = 0.0f;
	//ローカル座標
	XMFLOAT2 position = {};
	//スプライト幅、高さ
	XMFLOAT2 size = { 100.0f,100.0f };
	//アンカーポイント
	XMFLOAT2 anchorpoint = { 0,0 };
	//ワールド変換行列
	XMMATRIX matWorld{};
	//色
	XMFLOAT4 color = { 1,1,1,1 };
	//左右反転
	bool isFlipX = false;
	//上下反転
	bool isFlipY = false;
	//テクスチャ始点
	XMFLOAT2 texBase = { 0,0 };
	//テクスチャ幅、高さ
	XMFLOAT2 texSize = { 100.0f,100.0f };
	
#pragma endregion

#pragma region 関数
public: //静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="dev">デバイス</param>
	/// <param name="window_width">ウィンドウ横長さ</param>
	/// <param name="window_height">ウィンドウ縦長さ</param>
	/// <returns>成否</returns>
	static bool StaticInit(ID3D12Device* dev, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// スプライト(画像)生成
	/// </summary>
	/// <param name="texNumber">テクスチャ保存場所番号</param>
	/// <param name="position">位置</param>
	/// <param name="color">色(RGBA)</param>
	/// <param name="anchorpoint">アンカーポイント(左上)</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	/// <returns>スプライト生成情報</returns>
	static Sprite* CreateSprite(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT2 anchorpoint = { 0.0f,0.0f }, bool isFlipX = false, bool isFlipY = false);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texnumber">テクスチャ保存場所番号</param>
	/// <param name="filename">ファイル名</param>
	/// <returns>成否</returns>
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texNumber">テクスチャ保存場所番号</param>
	/// <param name="position">位置</param>
	/// <param name="size">サイズ</param>
	/// <param name="color">色(RGBA)</param>
	/// <param name="anchorpoint">アンカーポイント(左上)</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlopY">上下反転</param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlopY);
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Init();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 角度変更設定
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(float rotation);
	
	/// <summary>
	/// 座標変更設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT2 position);
	
	/// <summary>
	/// サイズ設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(XMFLOAT2 size);

	/// <summary>
	/// アンカーポイント変更設定
	/// </summary>
	/// <param name="anchorpoint">アンカーポイント(どこを基にするか)</param>
	void SetAnchorPoint(XMFLOAT2 anchorpoint);

	/// <summary>
	/// 左右反転設定
	/// </summary>
	/// <param name="isFlipX">左右反転</param>
	void SetIsFlipX(bool isFlipX);

	/// <summary>
	/// 上下反転設定
	/// </summary>
	/// <param name="isFlipY">上下反転</param>
	void SetIsFlipY(bool isFlipY);
	
	/// <summary>
	/// テクスチャ範囲設定(トリミング)
	/// </summary>
	/// <param name="texBase">テクスチャ始点</param>
	/// <param name="texSize">始点を基にしたサイズ</param>
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

private: //メンバ関数
	/// <summary>
	/// 頂点データ転送
	/// </summary>
	void TransferVertices();

protected:
	/// <summary>
	/// 頂点バッファ生成
	/// </summary>
	void CreateVertBuff();
#pragma endregion

};

