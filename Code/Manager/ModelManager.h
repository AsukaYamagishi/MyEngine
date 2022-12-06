#pragma once
#include <map>
#include <string>
#include "../3d/Obj/ObjLoader.h"

class ModelManager final
{
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager& r) = default;
	ModelManager& operator= (const ModelManager& r) = default;

public:
	////���f���ɕt����^�O��
	//enum ModelName {
	//	PLAYER,
	//	BULLET,
	//	ENEMY,
	//	EBULLET,
	//	WALL,
	//	SKYDOME,

	//	MAX //�ő吔�Ǘ�
	//};

public:
	static ModelManager* GetIns();		//�擾�p

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// ���f���ǂݍ���
	/// </summary>
	/// <param name="modelName">���f���ɕt�������^�O��</param>
	/// <param name="fileName">�t�@�C����</param>
	void LoadModel(std::string fileName);

	/// <summary>
	/// ���f�����̎擾
	/// </summary>
	/// <param name="modelName">���f���̃t�@�C����</param>
	/// <returns>���f�����</returns>
	ObjLoader* GetModel(const std::string& modelName)
	{
		if (model.find(modelName) == model.end())
		{
			//���f���������[�h�Ȃ�ǂݍ���
			LoadModel(modelName);
		}
		return model[modelName]; 
	}

private:
	static map<std::string, ObjLoader* > model;	//���f���i�[�}�b�v
};

