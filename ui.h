#pragma once
#include <string>

class UI {
public:
	//������ð����򻯵ĸ������ܷ�װ�ɽӿڣ�Ȼ����ͳһ����
	void findKeywords(std::string&);//�����ִ�Сд���ҵ��ؼ��ʣ���ȫ��Ϊ��д
	void No_n(std::string&);//���Ӷ���Ļ��з�
	void NoExtraSpace(std::string&);//ȥ������Ŀո�

	void preProcess(std::string&);
	std::stringstream getCommand();
};