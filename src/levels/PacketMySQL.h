
#ifndef SRC_LEVELS_PACKETMYSQL_H_
#define SRC_LEVELS_PACKETMYSQL_H_

#include "SessionTCP.h"

class MySQLRequest {
public:
	MySQLRequest(char commandType);

	char CommandType;
	std::string Query;
	std::string QueryType;
};

enum responsetype_t { OK, ERROR, AUTH };

class MySQLResponse {
public:
	MySQLResponse(responsetype_t responseType);
	uint64_t AffectedRows = 0; //-V122
	uint64_t LastInsertID = 0; //-V122
	responsetype_t ResponseType;
	uint16_t ErrorCode = 0;
	uint16_t StatusFlags = 0;
};

class PacketMySQL: public Chunk<SessionTCP> {
public:
	/**
	 * Constructor for HTTP chunks
	 * @param baseData Reference to base data (useless)
	 * @param payload Reference to payload
	 * @param parent Reference to TCP session
	 * @param request HTTP request
	 */
	PacketMySQL(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<SessionTCP> &parent
		, std::unique_ptr<MySQLRequest> request
		, std::unique_ptr<MySQLResponse> response
		, uint32_t packetLength);

	/**
	 * Optional reference to HTTP request
	 */
	std::unique_ptr<struct MySQLRequest> Request;

	/**
	 * Optional reference to HTTP response
	 */
	std::unique_ptr<struct MySQLResponse> Response;

	uint32_t PacketLength;
	uint32_t ConnectionID = 0;
	std::string ServerVersion;
	std::string Database;
	std::string Username;
	char Charset = 0;
	uint32_t MaxPktLen = 0;
};

#endif /* SRC_LEVELS_PACKETMYSQL_H_ */
