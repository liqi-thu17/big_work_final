#pragma once
#include "database.h"

class BaseSystem {
	int base_num = 0;
	DataBase * cur_base;
	std::unordered_map<std::string, DataBase> bases;
public:
	void addBase(const std::string & name);

	void setBase(const std::string & name) {
		//δ�����Ҳ��������
		cur_base = &bases[name];
	}

	void setTable(std::string & _info) {
		cur_base->setTable(_info);
	}

	void updateData(std::string& _info)
	{
		cur_base->updateData(_info);
	}
	void addData(std::string & _info) {
		cur_base->addData(_info);
	}

	void select(std::string & _info) {
		cur_base->select(_info);
	}

	void Delete(std::string & _info) {
		cur_base->Delete(_info);
	}
};