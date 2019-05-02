#include "basesystem.h"

void BaseSystem::addBase(const std::string & name) {
	//δ���������������
	DataBase *base = new DataBase;
	bases.insert(std::pair<std::string, DataBase*>(name, base));
	base_num++;
}

void BaseSystem::dropBase(const std::string & info) {
	int x = info.find(' ');
	std::string name = info.substr(x + 1);
	if (bases.find(name) == bases.end()) {
		std::cout << "δ�ҵ�Ҫɾ�������ݿ�" << std::endl;
	}
	else {
		delete bases[name];
		bases.erase(name);
	}
}