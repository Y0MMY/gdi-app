#include "../../headers/mics/query.hpp"
#ifdef  _DEBUG
#include <thread>
#endif //  _DEBUG
using namespace std;
bool SQLQuery::IsConnected;
HRESULT SQLQuery::connect(std::string query)
{
	if (IsConnected)
	{
#ifdef  _DEBUG

		std::cout << "Already connected to database!" << std::endl;
#endif //  _DEBUG
		return S_FALSE;
	}
	conn = std::make_unique<connection>(query);
	if (conn.get()->is_open()) {
		std::cout << "Opened database successfully: " << conn.get()->dbname() << std::endl;
		IsConnected = true;
	}
	else {
		std::cout << "Can't open database" << std::endl;
		conn.get()->close();
		return S_FALSE;
	}
	return S_OK;
}
result SQLQuery::query(std::string query)
{
#ifdef  _DEBUG
	auto start_time = chrono::high_resolution_clock::now();
#endif //  _DEBUG

	nontransaction N(*conn.get());
	result R(N.exec(query));
#ifdef  _DEBUG
	chrono::duration<float> duration = chrono::high_resolution_clock::now() - start_time;

	std::cout << "Time elapsed: " << duration.count();

#endif //  _DEBUG
	return R;
}

void SQLQuery::queryInsert(std::string str)
{
	work W(*conn.get());

	/* Execute SQL query */
	W.exec(str.c_str());
	W.commit();
}

HRESULT SQLQuery::disconnect()
{
	conn.get()->close();
	IsConnected = false;
#ifdef  _DEBUG
	if (!this->conn.get()->is_open()) {
		std::cout << "Close database successfully" << std::endl;
	}
	else {
#endif //  _DEBUG
		std::cout << "Can't close database" << std::endl;
		return S_FALSE;
#ifdef  _DEBUG
	}
#endif //  _DEBUG
	return S_OK;
}

bool SQLQuery::IsConnect()
{
	return IsConnected;
}
