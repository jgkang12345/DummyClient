#include "pch.h"
#include "DataManager.h"

DataManager::DataManager()
{
	std::vector<Pos> villageStartPosVector;
	villageStartPosVector.push_back({ 53,70 });
	villageStartPosVector.push_back({ 104,70 });
	villageStartPosVector.push_back({ 180,70 });
	villageStartPosVector.push_back({ 180,144 });
	villageStartPosVector.push_back({ 232,144 });
	villageStartPosVector.push_back({ 103,144 });
	villageStartPosVector.push_back({ 49,144 });
	villageStartPosVector.push_back({ 86,211});
	villageStartPosVector.push_back({ 51,172});
	villageStartPosVector.push_back({ 146,80});

	std::vector<Pos> noviceStartPosVector;
	noviceStartPosVector.push_back({134,134});
	noviceStartPosVector.push_back({195,173});
	noviceStartPosVector.push_back({136,222});
	noviceStartPosVector.push_back({63,187});
	noviceStartPosVector.push_back({74,82});
	noviceStartPosVector.push_back({90,167});
	noviceStartPosVector.push_back({178,206});
	noviceStartPosVector.push_back({ 209,81 });
	noviceStartPosVector.push_back({ 89,110});
	noviceStartPosVector.push_back({ 243,142});

	std::vector<Pos> intermediateStartPosVector;
	intermediateStartPosVector.push_back({ 50, 54 });
	intermediateStartPosVector.push_back({ 50, 119 });
	intermediateStartPosVector.push_back({ 50, 190 });
	intermediateStartPosVector.push_back({ 135, 190 });
	intermediateStartPosVector.push_back({ 135, 114 });
	intermediateStartPosVector.push_back({ 135, 45 });
	intermediateStartPosVector.push_back({ 208, 54 });
	intermediateStartPosVector.push_back({ 208, 114 });
	intermediateStartPosVector.push_back({ 208, 180 });
	intermediateStartPosVector.push_back({ 145, 206 });

	std::vector<Pos> highStartPosVector;
	highStartPosVector.push_back({ 47, 42 });
	highStartPosVector.push_back({ 47, 120 });
	highStartPosVector.push_back({ 47, 196 });
	highStartPosVector.push_back({ 112,196 });
	highStartPosVector.push_back({ 112, 117 });
	highStartPosVector.push_back({ 112,44 });
	highStartPosVector.push_back({ 178,196 });
	highStartPosVector.push_back({ 178, 117 });
	highStartPosVector.push_back({ 178,44 });
	highStartPosVector.push_back({ 208,175 });

	startPos.insert({ ServerType::NOVICE, noviceStartPosVector });
	startPos.insert({ ServerType::VILLAGE, villageStartPosVector });
	startPos.insert({ ServerType::INTERMEDIATE, intermediateStartPosVector });
	startPos.insert({ ServerType::HIGH, highStartPosVector });
}
