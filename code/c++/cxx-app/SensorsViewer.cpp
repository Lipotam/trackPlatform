#include "SensorsViewer.h"

	void SensorsViewer::setData(const std::vector<uint32_t>& d, SensorType t) {
		data = d;
		type = t;
	}

	void SensorsViewer::show() {
		if (type == LINE_SENSORS) {
			if (!data.empty()) {
				std::cout << "\r" << "|";
				for (int i = 0; i < data.size(); i++) {
					std::cout << (data[i] ? "@@@" : "   ");
				}
				std::cout << "|";
			}
		}
		else {
			if (!data.empty()) {
				if (system("clear")) system("cls");
				if (data.size() >= 1) std::cout << "       " << std::setw(4) << data[0] << std::endl;
				if (data.size() >= 2) std::cout << "    " << std::setw(4) << data[1] << (data.size() == 2 ? "\n" : "");
				if (data.size() >= 3) std::cout << "   " << std::setw(4) << data[2] << std::endl;
				if (data.size() >= 4) std::cout << " " << std::setw(4) << data[3] << (data.size() == 4 ? "\n" : "");
				if (data.size() >= 5) std::cout << "          " << std::setw(4) << data[4] << std::endl;
			}
		}
	}