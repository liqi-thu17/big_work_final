#pragma once
#include "attr.h"
#include <map>
#include <string>
#include <vector>
#include <stack>

//��һ���ö��ŷָ�����Ϣ���ҵ���i������
std::string getData(std::string data, int i);


class WhereClause {
	//whereClause�������ȼ�
	std::map<std::string, int> priority;
	//��׺���ʽ
	std::vector<std::string> Postfix;
public:
	WhereClause();
	//���һ��whereclause���ĺ�׺���ʽ
	void setPostfix(std::string _clause);
	//�жϵ�����judge����������data�Ƿ���ȷ,attrsΪ��������
	bool Judge(std::string judge, const std::string & data, const std::vector<Attr*> & attrs);
	//�����׺���ʽ��ArrΪ�������������OperΪ����ջ��dataΪ��ǰ���ݣ�attrsΪ��������
	void Calc(std::stack<std::string> & Oper, std::string & Arr, const std::string & data,const std::vector<Attr*> & attrs);
	//�ж�����data�Ƿ����clause������,attrsΪ��������
	bool whereclause(const std::string & data, const std::string & _clause, const std::vector<Attr*> & attrs);
};

