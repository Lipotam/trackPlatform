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
			if (system("clear")) system("cls");
			std::cout << "Distance sensors:" << std::endl;
			if (distanceSensors.size() >= 1) std::cout << "       " << std::setw(4) << distanceSensors[0] << std::endl;
			if (distanceSensors.size() >= 2) std::cout << "    " << std::setw(4) << distanceSensors[1] << (distanceSensors.size() == 2 ? "\n" : "");
			if (distanceSensors.size() >= 3) std::cout << "   " << std::setw(4) << distanceSensors[2] << std::endl;
			if (distanceSensors.size() >= 4) std::cout << " " << std::setw(4) << distanceSensors[3] << (distanceSensors.size() == 4 ? "\n" : "");
			if (distanceSensors.size() >= 5) std::cout << "         " << std::setw(4) << distanceSensors[4] << std::endl;
		}
		if (!lineSensors.empty()) {
			std::cout << "Line sensors:" << std::endl;
			std::cout << "|";
			for (int i = 0; i < lineSensors.size(); i++) {
				std::cout << (lineSensors[i] ? "@@@" : "   ");
			}
			std::cout << "|";
		}
	}
	void SensorsViewer::show(SensorType type) {
		if (type == LINE_SENSORS) {
			if (!lineSensors.empty()) {
				std::cout << "\r" << "|";
				for (int i = 0; i < lineSensors.size(); i++) {
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