// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PacketMySQL.h"

MySQLRequest::MySQLRequest(char commandType)
	: CommandType(commandType)
{

}

PacketMySQL::PacketMySQL(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<SessionTCP> &parent
		, std::unique_ptr<MySQLRequest> request
		, std::unique_ptr<MySQLResponse> response
		, uint32_t packetLength)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, Request(std::move(request))
	, Response(std::move(response))
	, PacketLength(packetLength)
{

}
