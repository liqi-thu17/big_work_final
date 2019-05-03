﻿#include "basesystem.h"

void BaseSystem::addBase(const std::string & name) {
	//未考虑重命名的情况
	DataBase *base = new DataBase;
	bases.insert(std::pair<std::string, DataBase*>(name, base));
	base_num++;
}

void BaseSystem::dropBase(std::string & base_name) {
	if (bases.find(base_name) == bases.end()) {
		std::cout << "未找到要删除的数据库" << std::endl;
	}
	else {
		delete bases[base_name];
		bases.erase(base_name);
	}
}

void BaseSystem::showBase() {
	std::vector<std::string> bases_name;
	std::cout << "Database" << std::endl;
	for (auto it : bases) {
		bases_name.push_back(it.first);
	}
	sort(bases_name.begin(), bases_name.end());
	for (auto it : bases_name) {
		std::cout << it << std::endl;
	}
}

void BaseSystem::showTable(std::string& base_name) {
	std::cout << "Tables_in_" << base_name << std::endl;
	bases[base_name]->showTable();
}

void BaseSystem::show_table_colums(std::string& base_name, std::string& table_name) {
	bases[base_name]->show_table_colums(table_name);
}

void BaseSystem::dropTable(std::string &base_name,std::string & table_name){
	bases[base_name]->dropTable(table_name);
}