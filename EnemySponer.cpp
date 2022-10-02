#include "EnemySponer.h"

EnemySponer::EnemySponer(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObject(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// ファイル読み込み
	spownDatas = LoadData("Resources/EnemySpownData.csv");
}

void EnemySponer::Update()
{
	if (spownDatas.size() == 0)
	{
		return;
	}
	// プレイヤーがスポーン位置から一定の距離内にいれば先頭のデータをスポーンさせる
	if (playerData->GetPos().z >= spownDatas.front().spownPos.z - 50.0f)
	{
		GameObject::Create<Enemy>(
			dxCommon, gameObjectManager, collisionManager,
			spownDatas.front().spownPos, playerData);
		spownDatas.pop();
	}
}

std::queue<EnemySponer::SpownData> EnemySponer::LoadData(const char* filepath)
{
	std::queue<SpownData> dataTable;

	ifstream fileStream(filepath);
	if (!fileStream) 
	{
		assert(0);
	}
	// 行
	int i = 0;

	//ファイルが終わるまで読み込み
	while (!fileStream.eof())
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		//1行目は列名でデータではないためスキップ
		if (i <= 1) continue;

		//データを項目ごとに抽出
		istringstream stringStream(bufferString);
		vector<string> datas;
		string stemp;
		//カンマ区切りでデータを切り分け
		while (getline(stringStream, stemp, ','))
		{
			datas.push_back(stemp);
		}
		//切り分けたデータを構造体に格納
		SpownData data;
		data.spownPos =
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		dataTable.push(data);
	}
	//ファイルクローズ
	fileStream.close();

	return dataTable;
}
