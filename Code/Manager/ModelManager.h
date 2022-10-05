#pragma once
#include <map>
#include <string>
#include "../3d/Obj/ObjLoader.h"

class ModelManager final
{
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager &r) = default;
	ModelManager &operator= (const ModelManager &r) = default;

public:
	//���f���ɕt����^�O��
	enum ModelName {
		PLAYER,
		BULLET,
		ENEMY,
		WALL,

		MAX //�ő吔�Ǘ�
	};

public:
	static ModelManager *GetIns();		//�擾�p

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// ���f���ǂݍ���
	/// </summary>
	/// <param name="modelName">���f���ɕt�������^�O��</param>
	/// <param name="fileName">�t�@�C����</param>
	void LoadModel(const ModelName modelName, std::string fileName);

	/// <summary>
	/// ���f�����̎擾
	/// </summary>
	/// <param name="modelName">���f���̃^�O��</param>
	/// <returns>�^�O�ɑΉ��������f�����</returns>
	ObjLoader *GetModel(ModelName modelName) { return model[modelName]; }

private:
	static map<ModelName, ObjLoader*> model;	//���f���i�[�}�b�v
};

