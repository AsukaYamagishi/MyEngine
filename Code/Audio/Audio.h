#pragma once
#include<Windows.h>
#include<xaudio2.h>
#include<wrl.h>

using namespace Microsoft::WRL;

//�I�[�f�B�I�R�[���o�b�N
class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
	//�{�C�X�����p�X�̊J�n��
	void OnVoiceProcessingPassStart(UINT32 ByteRequired) {};
	//�{�C�X�����p�X�̏I����
	void OnVoiceProcessingPassEnd() {};
	//�o�b�t�@�X�g���[���̍Đ����I��������
	void OnStreamEnd() {};
	//�o�b�t�@�̎g�p�J�n��
	void OnBufferStart(void* pBufferContext) {};
	//�o�b�t�@�̖����ɒB�����Ƃ�
	void OnBufferEnd(void* pBufferContext) { delete[] pBufferContext; };
	//�Đ������[�v�ʒu�ɒB�����Ƃ�
	void OnLoopEnd(void* pBufferContext) {};
	//�{�C�X�̎��s�G���[��
	void OnVoiceError(void* pBufferContext, HRESULT Error) {};
};

//�I�[�f�B�I
class Audio
{
#pragma region �\����

public: //�\����
	//�`�����N�w�b�_
	struct ChunkHeader
	{
		char id[4]; //�`�����N����ID
		int size; //�`�����N�T�C�Y
	};
	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		ChunkHeader chunk; //"RIFF"
		char type[4]; //"WAVE"
	};
	//FMT�`�����N
	struct FormatChunk
	{
		ChunkHeader chunk; //"fmt"
		WAVEFORMATEX fmt; //�g�`�t�H�[�}�b�g
	};
	//�����f�[�^
	struct SoundData
	{
		//�g�`�t�H�[�}�b�g
		WAVEFORMATEX wfex;
		//�o�b�t�@�̐擪�A�h���X
		BYTE* pBuffer;
		//�o�b�t�@�̃T�C�Y
		unsigned int bufferSize;
	};

#pragma endregion

#pragma region �ϐ�

public: //�����o�ϐ�
	ComPtr<IXAudio2> xAudio2;
	//���[�v�����邩
	enum IsLoop {
		not,
		loop
	};

private: //�����o�ϐ�
	IXAudio2MasteringVoice* masterVoice = nullptr;
	XAudio2VoiceCallback voiceCallback;

#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	
	/// <summary>
	/// �����f�[�^�ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <returns>�����f�[�^����</returns>
	SoundData SoundLoadWave(const char* filename);

	/// <summary>
	/// ���y�Đ�(���[�v�Ή�)
	/// </summary>
	/// <param name="xAudio2">�����pAPI</param>
	/// <param name="soundData">�Đ����鉹��</param>
	/// <param name="isLoop">���[�v�����邩</param>
	void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData, IsLoop isLoop = not);

	/// <summary>
	/// �Đ���~
	/// </summary>
	/// <param name="xAudio2">�����pAPI</param>
	/// <param name="soundData">��~���鉹��</param>
	void SoundStop(IXAudio2* xAudio2, const SoundData& soundData);

	/// <summary>
	/// �����f�[�^���
	/// </summary>
	/// <param name="soundData">������鉹���f�[�^</param>
	void SoundUnLoad(SoundData* soundData);

#pragma endregion

};