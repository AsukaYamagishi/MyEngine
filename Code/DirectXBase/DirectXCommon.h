#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "../WindowsAPI.h"

class DirectXCommon
{
#pragma region 定数
private: 
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
#pragma endregion

#pragma region 関数
public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="win">windows</param>
	void Init(WindowsAPI* win);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// レンダーターゲットのクリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 深度バッファのクリア
	/// </summary>
	void ClearDepthBuffer();

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns>device</returns>
	ID3D12Device* GetDevice() { return dev.Get(); }

	/// <summary>
	/// 描画コマンドリストの取得
	/// </summary>
	/// <returns>コマンドリスト</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private: //成否判定
	/// <summary>
	/// DXGIデバイス初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitDXGIDevice();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	/// <returns>成否</returns>
	bool CreateSwapChain();

	/// <summary>
	/// コマンド関連初期化
	/// </summary>
	/// <returns>成否</returns>
	bool InitCommand();

	/// <summary>
	/// レンダーターゲット生成
	/// </summary>
	/// <returns>成否</returns>
	bool CreateRenderTarget();

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	/// <returns>成否</returns>
	bool CreateDepthBuffer();

	/// <summary>
	/// フェンス生成
	/// </summary>
	/// <returns>成否</returns>
	bool CreateFence();
#pragma endregion

#pragma region 変数
private: //メンバ変数
	//WindowsAPI管理
	WindowsAPI* winApi;

	//Direct3D関連
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
#pragma endregion
};

