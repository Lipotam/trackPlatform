#include "SensorsViewer.h"

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
	if (!distanceSensors.empty()) {
        //configuration
        const short prefixSymbolNum = 1;
        const short betweenSymbolNum = 1;
        const short oneNumMinSize = 4;
        const char delimiter = ' ';
        std::ostream& os = std::cout;

        const short isParityOn = distanceSensors.size() % 2;
        const short stringNums = distanceSensors.size() / 2;
        os << "Distance sensors:" << std::endl;
        auto printChar = [](std::ostream& s, char c, short num) -> std::ostream&
        {
            while(num > 0)
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
                distanceSensors[stringNums + i + isParityOn - 1] << std::endl;
        }
	}
	if (!lineSensors.empty()) {
		std::cout << "Line sensors:" << std::endl;
		std::cout << "|";
		for (unsigned int i = 0; i < lineSensors.size(); i++) {
			std::cout << (lineSensors[i] ? "@@@" : "   ");
		}
		std::cout << "|" << std::endl;
	}
}
void SensorsViewer::show(SensorType type) {
	if (type == LINE_SENSORS) {
		if (!lineSensors.empty()) {
			std::cout << "\r" << "|";
			for (unsigned int i = 0; i < lineSensors.size(); i++) {
				std::cout << (lineSensors[i] ? "@@@" : "   ");
			}
			std::cout << "|";
		}
	}
	else {
		if (!distanceSensors.empty()) {
			if (system("clear")) system("cls");
			std::cout << "Distance sensors:" << std::endl;
			if (distanceSensors.size() >= 1) std::cout << "       " << std::setw(4) << distanceSensors[0] << std::endl;
			if (distanceSensors.size() >= 2) std::cout << "    " << std::setw(4) << distanceSensors[1] << (distanceSensors.size() == 2 ? "\n" : "");
			if (distanceSensors.size() >= 3) std::cout << "   " << std::setw(4) << distanceSensors[2] << std::endl;
			if (distanceSensors.size() >= 4) std::cout << " " << std::setw(4) << distanceSensors[3] << (distanceSensors.size() == 4 ? "\n" : "");
			if (distanceSensors.size() >= 5) std::cout << "          " << std::setw(4) << distanceSensors[4] << std::endl;
		}
	}
}