﻿#include "database.h"
#include <sstream>
#include <iostream>

void DataBase::setTable(std::string & _info) {
	std::istringstream info(_info);
	std::string Tablename;
	getline(info, Tablename, '(');

	Table *table = new Table;
	table->init(_info);
	tables[Tablename] = table;
	table_num++;
}
void DataBase::updateData(std::string& _info)
{
	std::istringstream info(_info);
	std::string Tablename;
	info >> Tablename;
	if (tables[Tablename] == NULL)
	{
		std::cout << "ERROR:未找到数据表'" << Tablename << "'" << std::endl;
	}
	else tables[Tablename]->updateData(info);
}

void DataBase::addData(std::string & _info) {
	std::istringstream info(_info);
	std::string Tablename;
	getline(info, Tablename, ' ');
	getline(info, Tablename, '(');
	if (tables[Tablename] == NULL)
	{
		std::cout << "ERROR:未找到数据表'"<<Tablename <<"'"<< std::endl;
	}
	else tables[Tablename]->addData(_info);
}

void DataBase::select(std::string & _info) {
	int x1 = _info.find("FROM");
	std::string name = _info.substr(x1 + 5);
	_info = _info.substr(0, x1 - 1);

	int x2 = name.find("WHERE");
	std::string whereClause;
	if (x2 != name.npos) {
		whereClause = name.substr(x2 + 6);
		name = name.substr(0, x2 - 1);
	}
	else {
		whereClause = "";
	}
	if (tables[name] == NULL)
	{
		std::cout << "ERROR:未找到数据表'" <<name<<"'"<< std::endl;
	}
	else tables[name]->select(_info, whereClause);
}

void DataBase::Delete(std::string & _info) {
	int x1 = _info.find("FROM");
	if (x1 == _info.npos)
	{
		std::cout << "ERROR:未识别的命令" << std::endl;
		return;
	}
	std::string name = _info.substr(x1 + 5);

	int x2 = name.find("WHERE");
	std::string whereClause;
	if (x2 != name.npos) {
		whereClause = name.substr(x2 + 6);
		name = name.substr(0, x2 - 1);
	}
	else {
		whereClause = "";
	}
	if (tables[name] == NULL)
	{
		std::cout << "ERROR:未找到数据表'" <<name<<"'"<< std::endl;
	}
	else tables[name]->Delete(whereClause);
}

void DataBase::showTable() {//输出表名 
	bool isnull = true;
	for (auto it = tables.begin(); it != tables.end(); it++) {
		if (it->second != NULL)
		{
			isnull = false;
			auto its = find(table_header.begin(), table_header.end(), it->first);
			if (its == table_header.end())
				table_header.push_back(it->first);
		}
	}
	if (isnull)
	{
		std::cout << "NULL" << std::endl;
		return;
	}
	sort(table_header.begin(), table_header.end());
	for (auto it = table_header.begin(); it != table_header.end(); it++) {
		std::cout << *it << std::endl;
	}
}

void DataBase::show_table_colums(const std::string& table_name) {
	auto its = tables.find(table_name);
	if (its != tables.end()) {
		tables[table_name]->show_table_colums();
	}
	else std::cout << "ERROR:未找到数据表'" <<table_name<<"'"<< std::endl;
}

void DataBase::dropTable(std::string& table_name) {
	if (tables.find(table_name) == tables.end()) {
		std::cout << "ERROR:未找到数据表'" <<table_name<<"'"<< std::endl;
	}
	else {
		auto era = find(table_header.begin(), table_header.end(), table_name);
		delete tables[table_name];
		tables.erase(table_name);
		table_header.erase(era);
	}
}