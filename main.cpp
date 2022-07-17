#include"WindowsAPI.h"  //�E�B���h�E�\��
#include"KeyboardInput.h"  //�L�[�{�[�h����
#include"Sprite.h"  //2D�摜(sprite)
#include"CalculationObject.h"  //3D�I�u�W�F�N�g(Object)
#include"Audio.h" //���y�Đ�
#include"DebugText.h" //�f�o�b�O�e�L�X�g
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
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG


	////DirectX�����������@��������
		
	//DirectX�ėp����
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

	//������
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	//�J����
	Camera* camera = nullptr;
	

	ModelInput::StaticInitialize(dxCommon->GetDevice());
	ModelManager::GetIns()->Initialize();

	
	////DirectInput(����)����������
	KeyboardInput* input = KeyboardInput::GetInstance();
	input->Init(win->hwnd);

	////DirectX�����������@�����܂�


	////�`�揉���������@��������
#pragma region �X�v���C�g/3D�I�u�W�F�N�g�ÓI������
	// �X�v���C�g�ÓI������
	if (!Sprite::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3D�I�u�W�F�N�g�ÓI������
	if (!CalculationObject::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	if (!ParticleManager::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	
#pragma endregion

#pragma region 3D���f���ÓI������
	// Obj
	if (!ModelDraw::StaticInitialize(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// FBX
	FbxInput::GetInstance()->Init(dxCommon->GetDevice());

#pragma endregion
	

#pragma region �Q�[���V�[��������
	
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Init(dxCommon, input, audio);

#pragma endregion

	PostEffect* postEffect = nullptr;
	//�|�X�g�G�t�F�N�g������
	postEffect = new PostEffect();
	postEffect->Init();

	MultiRenderTarget* multiRT = nullptr;
	//�}���`�����_�[�^�[�Q�b�g������
	multiRT = new MultiRenderTarget();
	multiRT->Init();
	
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
		input->Update();
		sceneManager->Update();
#pragma endregion
		
#pragma region �`��R�}���h
		//�����_�[�e�N�X�`���ւ̕`��(�|�X�g�G�t�F�N�g����)
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		//multiRT->PreDrawScene(dxCommon->GetCommandList());
		sceneManager->Draw(); //�Q�[���V�[���`��
		postEffect->PostDrawScene(dxCommon->GetCommandList());
		//multiRT->PostDrawScene(dxCommon->GetCommandList());

		//�`��O����
		dxCommon->PreDraw();

		//�|�X�g�G�t�F�N�g�`��
		postEffect->Draw(dxCommon->GetCommandList());
		//multiRT->Draw(dxCommon->GetCommandList());
		//sceneManager->Draw(); //�Q�[���V�[���`��

		//�`��I��
		dxCommon->PostDraw();
#pragma endregion

		////////////////DirectX���t���[������ �����܂�
	}

	//�������
	FbxInput::GetInstance()->Fin();
	delete postEffect;
	delete multiRT;

	//�N���X(new)�̏���
	safe_delete(dxCommon);
	safe_delete(audio);
	safe_delete(sceneManager);

	//�E�B���h�E�N���X��o�^����
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	return 0;
}

