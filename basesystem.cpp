#include "basesystem.h"

void BaseSystem::addBase(const std::string & name) {
	//δ���������������
	DataBase base;
	bases.insert(std::pair<std::string, DataBase>(name, base));
	base_num++;
}