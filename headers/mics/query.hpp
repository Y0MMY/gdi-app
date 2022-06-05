#pragma once
#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include <mutex>
#include <Windows.h>

using namespace pqxx;
class SQLQuery
{
public:
	SQLQuery() = default;
	~SQLQuery() = default;
	HRESULT connect(std::string);
	result query(std::string);
	void queryInsert(std::string);
	HRESULT disconnect();
	bool IsConnect();
private:
	std::unique_ptr<connection> conn;
	std::mutex m_mutex;
	static bool IsConnected;
	
};
