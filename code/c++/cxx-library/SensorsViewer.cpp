#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "SensorsViewer.h"

void SensorsViewer::showDistanceInfo()
{
	if (!distanceSensors.empty()) {
		//configuration
		const short prefixSymbolNum = 1;
		const short betweenSymbolNum = 1;
		const short oneNumMinSize = 4;
		const char delimiter = ' ';
		std::ostream& os = std::cout;

		const short isParityOn = static_cast<short>(distanceSensors.size() % 2);
		const short stringNums = static_cast<short>(distanceSensors.size() / 2);
		os << "Distance sensors:" << std::endl;
		const auto printChar = [](std::ostream& s, char c, short num) -> std::ostream&
		{
			while (num > 0)
			{
				s << c;
				num--;
			}
			return s;
		};
		if (isParityOn)
		{
			printChar(os, delimiter, prefixSymbolNum + stringNums + oneNumMinSize / 2) <<
				distanceSensors[stringNums] << std::endl;
		}
		for (short i = 0; i < stringNums; ++i)
		{
			printChar(os, delimiter, prefixSymbolNum + stringNums - i - 1) <<
				std::setw(oneNumMinSize) << distanceSensors[stringNums - i - 1];
			printChar(os, delimiter, i * 2 + betweenSymbolNum) << std::setw(oneNumMinSize) <<
				distanceSensors[stringNums + i + isParityOn] << std::endl;
		}
	}
}

void SensorsViewer::showLineInfo()
{
	if (!lineSensors.empty()) {
		std::cout << "Line sensors:" << std::endl;
		std::cout << "|";
		for (unsigned int i = 0; i < lineSensors.size(); i++) {
			std::cout << (lineSensors[i] ? "@@@" : "   ");
		}
		std::cout << "|" << std::endl;
	}
}

void SensorsViewer::setData(const std::vector<uint32_t>& d, SensorType t) {
	if (t == LINE_SENSORS) {
		lineSensors = d;
	}
	else {
		distanceSensors = d;
	}
}

void SensorsViewer::show() {
	if (system("clear")) system("cls");
	showDistanceInfo();
	showLineInfo();
}
void SensorsViewer::show(SensorType type) {
	if (type == LINE_SENSORS) {
		showLineInfo();
	}
	else {
		if (system("clear")) system("cls");
		showDistanceInfo();
	}
}
