#include <vector>
#include <iostream>
#include <initializer_list>

#include "olcConsoleGameEngine.h"
using namespace std;
class VisualizationSort : public olcConsoleGameEngine {
public:
	VisualizationSort(initializer_list<int> _list) {
		m_sAppName = L"可视化排序算法";
		vec.assign(_list);
		firstIndex = 0;
		minIndex = 0;
		length = vec.size();
	}
	virtual bool OnUserCreate() override {
		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
		timer += fElapsedTime;
		if (timer >= timeLimit && firstIndex < length) {
			timer = .0f;
			minIndex = firstIndex;
			for (vector<int> ::size_type j = firstIndex; j < length; ++j) {
				if (vec[j] > vec[minIndex]) {
					minIndex = j;
				}
			}
			int tmp = vec[firstIndex];
			vec[firstIndex] = vec[minIndex];
			vec[minIndex] = tmp;

			++firstIndex;
		}
		DrawVector();
		return true;
	}

	void DrawVector() {
		int nPillarSize = 9;
		int nPillarBoard = 2;

		std::size_t length = vec.size();
		for (vector<int> ::size_type i = 0; i < length; ++i) {
			if (i == firstIndex) {
				Fill(i * nPillarSize + nPillarBoard, nPillarBoard, (i + 1) * nPillarSize - nPillarBoard,
					vec[i] * nPillarSize - nPillarBoard, PIXEL_SOLID, FG_RED);
			}
			else if (i == minIndex) {
				Fill(i * nPillarSize + nPillarBoard, nPillarBoard, (i + 1) * nPillarSize - nPillarBoard,
					vec[i] * nPillarSize - nPillarBoard, PIXEL_SOLID, FG_GREEN);
			}
			else {
				Fill(i * nPillarSize + nPillarBoard, nPillarBoard, (i + 1) * nPillarSize - nPillarBoard,
					vec[i] * nPillarSize - nPillarBoard, PIXEL_SOLID, FG_BLUE);
			}
		}
	}
private:
	vector<int> vec;
	vector<int>::size_type firstIndex;
	vector<int>::size_type minIndex;
	std::size_t length;

	float timer;
	constexpr static float timeLimit = 2.f;
};

int main(int argc, char** argv) {
	VisualizationSort demo = { 2,6,1,2,4,3,6,8,1,4,2,1 };
	demo.ConstructConsole(160, 160, 6, 6);
	demo.Start();
	return 0;
}