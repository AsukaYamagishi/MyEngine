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
#pragma region �萔
private: 
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="win">windows</param>
	void Init(WindowsAPI* win);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̃N���A
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// �[�x�o�b�t�@�̃N���A
	/// </summary>
	void ClearDepthBuffer();

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns>device</returns>
	ID3D12Device* GetDevice() { return dev.Get(); }

	/// <summary>
	/// �`��R�}���h���X�g�̎擾
	/// </summary>
	/// <returns>�R�}���h���X�g</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }

private: //���۔���
	/// <summary>
	/// DXGI�f�o�C�X������
	/// </summary>
	/// <returns>����</returns>
	bool InitDXGIDevice();

	/// <summary>
	/// �X���b�v�`�F�[���̐���
	/// </summary>
	/// <returns>����</returns>
	bool CreateSwapChain();

	/// <summary>
	/// �R�}���h�֘A������
	/// </summary>
	/// <returns>����</returns>
	bool InitCommand();

	/// <summary>
	/// �����_�[�^�[�Q�b�g����
	/// </summary>
	/// <returns>����</returns>
	bool CreateRenderTarget();

	/// <summary>
	/// �[�x�o�b�t�@����
	/// </summary>
	/// <returns>����</returns>
	bool CreateDepthBuffer();

	/// <summary>
	/// �t�F���X����
	/// </summary>
	/// <returns>����</returns>
	bool CreateFence();
#pragma endregion

#pragma region �ϐ�
private: //�����o�ϐ�
	//WindowsAPI�Ǘ�
	WindowsAPI* winApi;

	//Direct3D�֘A
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

