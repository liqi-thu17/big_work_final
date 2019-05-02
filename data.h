#pragma once
#include <string>
#include <sstream>

class Data {
protected:
	std::string data;
	Data* pre = NULL;
	Data* suc = NULL;
public:
	Data(std::string _data) {
		data = _data;
	}
	//���ݵ�����
	virtual void setData(std::string _data) {
		data = _data;
	}
	//���ݵĻ�ȡ
	virtual std::string getData() {
		return data;
	}
	//���͵�ʶ��
	virtual std::string getType() {
		return "CHAR";
	}

	void setPre(Data *_pre) {
		pre = _pre;
	}

	void setSuc(Data *_suc) {
		suc = _suc;
	}

	Data* getPre() {
		return pre;
	}

	Data* getSuc() {
		return suc;
	}
};

class IntData : public Data {
protected:
	int value;
public:
	IntData(std::string _data) : Data(_data) {
		value = stoi(data);
	}

	void setData(std::string _data) {
		data = _data;
		value = stoi(data);
	}

	int getValue() {
		return value;
	}

	std::string getType() {
		return "INT";
	}
};

class DoubleData : public Data {
protected:
	double value;
public:
	DoubleData(std::string _data) : Data(_data) {
		std::stringstream data(_data);
		data >> value;
	}

	void setData(std::string _data) {
		data = _data;
		std::stringstream data(_data);
		data >> value;
	}

	double getValue() {
		return value;
	}

	std::string getType() {
		return "DOUBLE";
	}
};