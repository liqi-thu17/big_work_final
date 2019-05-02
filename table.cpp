#include "table.h"
#include <sstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>

void Table::init(std::string & _info) {
	std::istringstream info(_info);
	std::string data;
	getline(info, data, '(');
	while (getline(info, data, ',')) {
		if (*data.rbegin() == ')') data.pop_back();
		//��������
		bool iskey = false;
		int x = data.find("PRIMARY KEY");
		if (x != data.npos) {
			int x1 = data.find_first_of('(');
			int x2 = data.find_first_of(')');
			std::string name = data.substr(x1 + 1, x2 - x1 - 1);
			for (size_t i = 0; i < attrs.size(); i++) {
				if (attrs[i]->getName() == name) {
					key = i;
					iskey = true;
					break;
				}
			}
			continue;
		}

		bool notnull = false;
		x = data.find("NOT NULL");
		if (x != data.npos) {
			//���÷ǿ���
			notnull = true;
			not_null.push_back(attr_num);
			//ɾ��NOT NULL
			data.erase(x - 1, 9);
		}

		//�������
		x = data.find(' ');
		std::string name = data.substr(0, x);
		std::string type = data.substr(x + 1);
		Attr *attr = new Attr(name, type);
		if(notnull)	attr->notNull();
		if (iskey) attr->setKey();
		attrs.push_back(attr);
		attr_num++;
	}
}

void Table::addData(std::string & _info) {
	row_num++;
	std::istringstream info(_info);
	std::string data;
	getline(info, data, '(');
	getline(info, data, ')');

	std::vector<int> attrId;
	int x;
	std::string name;

	//�������
	while ((x = data.find_first_of(',')) != data.npos) {
		name = data.substr(0, x);
		data = data.substr(x + 1);

		for (int i = 0; i < attr_num; i++) {
			if (attrs[i]->getName() == name) {
				attrId.push_back(i);
				break;
			}
		}
	}
	for (int i = 0; i < attr_num; i++) {
		if (attrs[i]->getName() == data) {
			attrId.push_back(i);
			break;
		}
	}

	//���notnull
	for (auto it : not_null) {
		if (find(attrId.begin(), attrId.end(), it) == attrId.end()) {
			std::cout << attrs[it]->getName() << "������Ϊ�գ�";
			return;
		}
	}

	//����
	std::string new_row;
	std::vector<Data*> new_attr;
	getline(info, data, '(');
	getline(info, data, ')');
	for (int i = 0; i < attr_num; i++) {
		//�����Ƿ�����Ӧ������
		size_t j;
		for (j = 0; j < attrId.size(); j++) {
			if (attrId[j] == i) {
				break;
			}
		}
		//��ֵ
		if (j != attrId.size()) {
			new_row += getData(data, j);
			Data *p = new Data(getData(data, j));
			new_attr.push_back(p);
		}
		else {
			Data *p = new Data("");
			new_attr.push_back(p);
		}
		if (i != attr_num - 1)
			new_row += ",";
	}
	rows.push_back(new_row);

	//���뵽attr��
	for (size_t i= 0; i < new_attr.size(); i++) {
		if (i == 0) {
			new_attr[i]->setSuc(new_attr[i + 1]);
			attrs[i]->addData(new_attr[i]);
		}
		else if (i == new_attr.size() - 1) {
			new_attr[i]->setPre(new_attr[i - 1]);
			attrs[i]->addData(new_attr[i]);
		}
		else {
			new_attr[i]->setPre(new_attr[i - 1]);
			new_attr[i]->setSuc(new_attr[i + 1]);
			attrs[i]->addData(new_attr[i]);
		}
	}
}

std::string Table::getRow(Data* data) {
	while (data->getPre() != NULL)
		data = data->getPre();
	
	std::string row;

	while (data->getSuc() != NULL) {
		row += data->getData() + ",";
		data = data->getSuc();
	}
	row += data->getData();
	
	return row;
}

void Table::setRows() {
	//���rows
	rows.clear();
	std::list<Data*> temp = attrs[0]->getDatas();
	for (auto it : temp) {
		rows.push_back(getRow(it));
	}
}

std::vector<Data*> Table::separateRow(std::string _row) {
	std::istringstream row(_row);
	std::vector<Data*> datas;
	std::string data;
	while (getline(row, data, ',')) {
		Data * p = new Data(data);
		datas.push_back(p);
	}
	//��������
	for (size_t i = 0; i < datas.size(); i++) {
		if (i == 0) {
			datas[i]->setSuc(datas[i + 1]);
		}
		else if (i == datas.size() - 1) {
			datas[i]->setPre(datas[i - 1]);
		}
		else {
			datas[i]->setPre(datas[i - 1]);
			datas[i]->setSuc(datas[i + 1]);
		}
	}
	return datas;
}

void Table::setAttrs() {
	for (auto it : attrs) {
		it->cleanData();
	}

	for (auto it : rows) {
		std::vector<Data*> datas = separateRow(it);
		for (int i = 0; i < attr_num; i++) {
			attrs[i]->addData(datas[i]);
		}
	}
}

void Table::select(std::string & _info, std::string & Clause) {
	if (_info == "*") {
		//�������?
		for (auto it : rows) {
			if (WC.whereclause(it, Clause,attrs))
				std::cout << it << std::endl;
		}
	}
	else {
		std::istringstream info(_info);
		std::vector<std::string> names;
		std::string name;

		while (getline(info, name, ',')) {
			names.push_back(name);
		}

		std::vector<int> output;
		for (size_t i = 0; i < names.size(); i++) {
			for (int j = 0; j < attr_num; j++) {
				if (attrs[j]->getName() == names[i]) {
					output.push_back(j);
				}
			}
		}

		for (auto row : rows) {
			if (WC.whereclause(row, Clause,attrs)) {
				size_t i = 0;
				for (; i < output.size() - 1; i++) {
					std::cout << getData(row, output[i]) << ",";
				}
				std::cout << getData(row, output[i]) << std::endl;
			}
		}
	}
}

void Table::Delete(std::string & Clause) {
	for (auto it = rows.begin(); it != rows.end();) {
		if (WC.whereclause(*it, Clause,attrs)) {
			it = rows.erase(it);
			row_num--;
		}
		else {
			it++;
		}
	}
	setAttrs();
}

//���Ǵ���������ʵ���߼���������
void Table::updateData(std::istringstream& info)
{
	//UPDATE xxtable SET attrName = attrValue WHERE XXXXX;
	std::string data;
	std::string value;
	info >> data;//"SET"
	info >> std::ws;
	getline(info, data, '=');
	int index = 0;
	while (attrs[index]->getName() != data && index < attr_num)index++;
	if (index == attr_num) std::cout << "error" << std::endl;
	info >> std::ws;//'='
	info >> value;//�õ�value
	info >> data;//"WHERE"
	if (data != "WHERE") data = "";
	else getline(info, data);//�õ��������
	//todo:ʵ��WHERECLAUSE
	for (std::list<std::string>::iterator it = rows.begin(); it != rows.end(); it++)
	{
		if (WC.whereclause(*it, data,attrs))//������������WHERECLAUSE�ҵ���
		{
			std::string& tmprow = *it;
			if (attrs.size() > 1) {
				int x1 = -1;
				for (int kk = 0; kk < index; kk++)
				{
					x1 = tmprow.find(',', x1 + 1);
				}
				int x2 = tmprow.find(',', x1 + 1);
				if (x2 == tmprow.npos) x2 = tmprow.size();
				tmprow.replace(x1 + 1, x2 - x1 - 1, value);
			}
			else tmprow = value;
		}
	}
	setAttrs();
}