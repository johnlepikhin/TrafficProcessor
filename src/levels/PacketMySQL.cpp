
#include "PacketMySQL.h"

MySQLRequest::MySQLRequest(char commandType)
	: CommandType(commandType)
{

}

PacketMySQL::PacketMySQL(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<SessionTCP> parent
		, std::unique_ptr<MySQLRequest> request
		, std::unique_ptr<MySQLResponse> response
		, uint32_t packetLength)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, Request(std::move(request))
	, Response(std::move(response))
	, PacketLength(packetLength)
{

}
