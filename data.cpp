#include "data.h"
#include <iomanip>

//��str�����е�origin�滻Ϊsub
std::string replaceAll(std::string str, std::string origin, std::string sub) {
	int L1 = origin.length(), L2 = sub.length();
	int x;
	while ((x = str.find(origin)) != str.npos) {
		str.replace(x, L1, sub);
	}
	return str;
}

//�õ�data��һ�еĵ�i������
Data* get_Data_i(Data* data, int i) {
	while (data->getPre() != NULL)
		data = data->getPre();

	while (i--) {
		data = data->getSuc();
	}
	return data;
}

std::string DoubleData::showData() {
	if (data == "") {
		return "NULL";
	}
	else {
		std::string output;
		std::stringstream data;
		data << std::fixed << std::setprecision(4) << value;
		data >> output;
		return output;
	}
}