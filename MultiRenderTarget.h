#pragma once
#include "Sprite.h"

class MultiRenderTarget :
    public Sprite
{
#pragma region 変数
public:
    //テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff[2];
    //SVR用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    //RTV用デスクリプタヒープ(レンダーターゲットビュー)
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用デスクリプタヒープ(デプスステンシルビュー)
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //グラフィックスパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    //ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;
    //画面クリアカラー
    static const float clearColor[4];
#pragma endregion

#pragma region 関数
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MultiRenderTarget();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画後処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);


private:

    /// <summary>
    /// パイプライン生成
    /// </summary>
    void CreateGraphicsPipelineState();

    /// <summary>
    /// テクスチャ生成
    /// </summary>
    void CreateTexture();

    /// <summary>
    /// SRV作成
    /// </summary>
    void CreateSRV();

    /// <summary>
    /// レンダーターゲットビュー作成
    /// </summary>
    void CreateRTV();

    /// <summary>
    /// 深度バッファ生成
    /// </summary>
    void CreateDepthBuff();

    /// <summary>
    /// デプスステンシルビュー作成
    /// </summary>
    void CreateDSV();


#pragma endregion
};

