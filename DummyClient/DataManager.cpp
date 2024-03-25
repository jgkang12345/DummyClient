#include "pch.h"
#include "DataManager.h"

DataManager::DataManager()
{
	std::vector<Pos> villageStartPosVector;
	villageStartPosVector.push_back({ 111,78 });
	villageStartPosVector.push_back({ 167,72 });
	villageStartPosVector.push_back({ 153,130 });
	villageStartPosVector.push_back({ 97,148 });
	villageStartPosVector.push_back({ 30,95 });
	villageStartPosVector.push_back({ 142,202 });

	std::vector<Pos> noviceStartPosVector;
	noviceStartPosVector.push_back({134,134});
	noviceStartPosVector.push_back({195,173});
	noviceStartPosVector.push_back({136,222});
	noviceStartPosVector.push_back({63,187});
	noviceStartPosVector.push_back({74,82});
	noviceStartPosVector.push_back({90,167});

	std::vector<Pos> intermediateStartPosVector;
	noviceStartPosVector.push_back({ 50, 54 });
	noviceStartPosVector.push_back({ 50, 119 });
	noviceStartPosVector.push_back({ 50, 190 });
	noviceStartPosVector.push_back({ 135, 190 });
	noviceStartPosVector.push_back({ 135, 114 });
	noviceStartPosVector.push_back({ 135, 45 });

	std::vector<Pos> highStartPosVector;
	highStartPosVector.push_back({ 47, 42 });
	highStartPosVector.push_back({ 47, 120 });
	highStartPosVector.push_back({ 47, 196 });
	highStartPosVector.push_back({ 112,196 });
	highStartPosVector.push_back({ 112, 117 });
	highStartPosVector.push_back({ 112,44 });

	startPos.insert({ ServerType::NOVICE, noviceStartPosVector });
	startPos.insert({ ServerType::VILLAGE, villageStartPosVector });
	startPos.insert({ ServerType::INTERMEDIATE, intermediateStartPosVector });
	startPos.insert({ ServerType::HIGH, highStartPosVector });
}
