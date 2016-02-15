#include <map>
#include "common/HisTestHandler.h"

//#include "himsgbus/HiMsgBusTest.h"
//#include "net/HiNetTest.h"
//#include "db/HiDBTest.h"

using namespace std;

void add_test_fun(std::map<std::string,  HisTestHandler::TestObject>& lst)
{
	//lst["HiMsgBusTest"] = std::bind(&HisTestHandler::OnTest_i<HiMsgBusTest>,  std::tr1::placeholders::_1);
	//lst["HiNetTest"] = std::bind(&HisTestHandler::OnTest_i<HiNetTest>,  std::tr1::placeholders::_1);
	//lst["HiDBTest"] = std::bind(&HisTestHandler::OnTest_i<HiDBTest>,  std::tr1::placeholders::_1);
}