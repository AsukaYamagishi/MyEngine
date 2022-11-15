#include "ScoreManager.h"
#include <iostream>
#include <sstream>

ScoreManager::ScoreManager(DirectXCommon* dxCommon, DebugText* debugText):
	GameObjectBase(dxCommon)
{
	this->dxCommon = dxCommon;
	this->debugText = debugText;
}

void ScoreManager::Draw()
{
	std::ostringstream drawScoreStr;
	drawScoreStr << "SCORE:";

	int buff = 0;
	int tempScore = score;
	while (1)
	{
		tempScore = tempScore / 10;
		buff++;
		if (tempScore <= 0) break;
	}
	for (int i = 0; i < 6 - buff; i++)
	{
		drawScoreStr << 0;
	}
	drawScoreStr << score;
	debugText->PrintDebugText(drawScoreStr.str().c_str(), 0.0f, 20.0f, 2.0f);
}

void ScoreManager::AddScore(int add)
{
	score = score + add;
}

void ScoreManager::SubScore(int sub)
{
	if (score <= 0) return;
	score = score + -sub;
}
