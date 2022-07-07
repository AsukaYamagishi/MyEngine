#pragma once
#include "Sprite.h"

class PostEffect :
    public Sprite
{
#pragma region 変数
public:
    //テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff;
    //SVR用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    //RTV用デスクリプタヒープ(レンダーターゲットビュー)
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用デスクリプタヒープ(デプスステンシルビュー)
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
#pragma endregion

#pragma region 関数
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList); 

   
private:
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
    /// 深度バッファ/デプスステンシルビュー作成
    /// </summary>
    void CreateDSV();


#pragma endregion
};

