#pragma once
#include <vector>
#include <algorithm>
#include <numeric>

class BoxPlot
{
public:
	static double min(std::vector<double> vec);
	static double lq(std::vector<double> vec);
	static double median(std::vector<double> vec);
	static double mean(std::vector<double> vec);
	static double stddev(std::vector<double> vec);
	static double uq(std::vector<double> vec);
	static double max(std::vector<double> vec);
	static void out(std::vector<double> vec);

	static std::vector<double> IQR(std::vector<double> vec);
};

double BoxPlot::min(const std::vector<double> vec) {
	std::vector<double> tmp = IQR(vec);
	return tmp[0];
}

double BoxPlot::lq(std::vector<double> vec) {
	std::sort(vec.begin(), vec.end());
	return vec[std::ceil(0.25 * vec.size())];
}

double BoxPlot::median(std::vector<double> vec) {
	std::sort(vec.begin(), vec.end());
	return vec[vec.size() / 2];
}

double BoxPlot::mean(std::vector<double> vec) {
	return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double BoxPlot::stddev(std::vector<double> vec) {
	double avg = mean(vec);
	double sum = 0;
	for (size_t i = 0; i < vec.size(); i++) sum += pow(vec[i] - avg, 2);
	return pow(sum / (vec.size() - 1), 0.5);
}

double BoxPlot::uq(std::vector<double> vec) {
	std::sort(vec.begin(), vec.end());
	return vec[std::ceil(0.75 * vec.size()) - 1];
}

double BoxPlot::max(std::vector<double> vec) {
	std::vector<double> tmp = IQR(vec);
	return tmp[tmp.size() - 1];
}

void BoxPlot::out(std::vector<double> vec) {
	double IQRvalue = uq(vec) - lq(vec);
	double min = lq(vec) - 1.5 * IQRvalue;
	double max = uq(vec) + 1.5 * IQRvalue;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] <= min) std::cout << "OutMIN is " << vec[i] << std::endl;
		if (vec[i] >= max) std::cout << "OutMAX is " << vec[i] << std::endl;
	}
}

std::vector<double> BoxPlot::IQR(std::vector<double> vec) {
	double IQRvalue = uq(vec) - lq(vec);
	double min = lq(vec) - 1.5 * IQRvalue;
	double max = uq(vec) + 1.5 * IQRvalue;

	std::vector<double> IQR;
	for (size_t i = 0; i < vec.size(); i++)
		if (vec[i] >= min && vec[i] <= max)
			IQR.push_back(vec[i]);
	std::sort(IQR.begin(), IQR.end());
	return IQR;
}