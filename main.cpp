#include "WindowsAPI.h"  //�E�B���h�E�\��
#include "KeyboardInput.h"  //�L�[�{�[�h����
#include "Code/Input/ControllerInput.h" //�Q�[���p�b�h����
#include "Sprite.h"  //2D�摜(sprite)
#include "Code/Model/CalculationModel.h"  //3D�I�u�W�F�N�g(Object)
#include "Code/Audio/Audio.h" //���y�Đ�
#include "Code/DirectXBase/DebugText.h" //�f�o�b�O�e�L�X�g
#include "Code/DirectXBase/DirectXCommon.h"
#include "SafeDelete.h"
#include "ModelDraw.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Code/Model/Fbx/FbxLoader.h"
#include "Code/Camera/Camera.h"
#include "PostEffect.h"
#include "MultiRenderTarget.h"

using namespace DirectX;
using namespace Microsoft::WRL;


//Windows�A�v���ł̃G���g���[�|�C���g�imain�֐��j
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E
	WindowsAPI* win = nullptr;
	win = new WindowsAPI();
	win->WindowCreate();

	MSG msg{}; //���b�Z�[�W


#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG

#pragma region DirectX������
	////DirectX�����������@��������
	//DirectX�ėp����
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); //��΂��G���[�Ŏ~�܂�
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); //�G���[�Ŏ~�܂�
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true); //warning�Ŏ~�܂�
	}
#endif // _DEBUG

	//������
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	//�J����
	Camera* camera = nullptr;
	
	//���͊֌W������
	KeyboardInput::GetInstance()->Init(win->hwnd);
	ControllerInput::GetInstance()->Init();


	////DirectX�����������@�����܂�
#pragma endregion

	////�`�揉���������@��������
#pragma region �X�v���C�g/3D�I�u�W�F�N�g�ÓI������
	// �X�v���C�g�ÓI������
	if (!Sprite::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	////�|�X�g�G�t�F�N�g������
	//PostEffect* postEffect = nullptr;
	//postEffect = new PostEffect();
	//postEffect->Init();

	////�}���`�����_�[�^�[�Q�b�g������
	//MultiRenderTarget* multiRT = nullptr;
	//multiRT = new MultiRenderTarget();
	//multiRT->Init();

	// 3D�I�u�W�F�N�g�ÓI������
	if (!CalculationModel::StaticInit(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	if (!ParticleManager::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	
#pragma endregion

#pragma region 3D���f���ÓI������
	ModelInput::StaticInitialize(dxCommon->GetDevice());
	ModelManager::GetIns()->Initialize();

	// Obj
	if (!ModelDraw::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::win_width, WindowsAPI::win_height)) {
		assert(0);
		return 1;
	}

	// FBX
	FbxLoader::GetInstance()->Init(dxCommon->GetDevice());

#pragma endregion
	
#pragma region �Q�[���V�[��������
	
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager(dxCommon, audio);
	sceneManager->Init();

#pragma endregion

	
	////�`�揉���������@�����܂�

	while (true) //�Q�[�����[�v
	{
	#pragma region ���b�Z�[�W�m�F
		//���b�Z�[�W�����邩
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&msg); //�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}

		//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (msg.message == WM_QUIT)
		{
			break;
		}
	#pragma endregion

		////////////////DirectX���t���[������ ��������

#pragma region �X�V����
		KeyboardInput::GetInstance()->Update();
		ControllerInput::GetInstance()->Update();
		sceneManager->Update();
#pragma endregion
		
#pragma region �`��R�}���h
		
		//�`��O����
		dxCommon->PreDraw();

		sceneManager->Draw(); //�Q�[���V�[���`��

		//�`��I��
		dxCommon->PostDraw();
#pragma endregion

		////////////////DirectX���t���[������ �����܂�
	}

	//�������
	FbxLoader::GetInstance()->Fin();

	//�N���X(new)�̏���
	safe_delete(dxCommon);
	safe_delete(audio);
	safe_delete(sceneManager);

	//�E�B���h�E�N���X��o�^����
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	return 0;
}