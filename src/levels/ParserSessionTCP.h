
#ifndef SRC_LEVELS_PARSERSESSIONTCP_H_
#define SRC_LEVELS_PARSERSESSIONTCP_H_

#include <string.h>
#include <unordered_map>
#include "ChunkTCP.h"
#include "SessionTCP.h"
#include "../types/Processor.h"
#include "../types/Counter.h"

/**
 * This class represents session ID based on IP addresses and ports
 */
class SessionID {
public:
	/**
	 * First IP address of the session
	 */
	std::string IP1;

	/**
	 * Second IP address of the session
	 */
	std::string IP2;

	/**
	 * First TCP port of the session
	 */
	unsigned short Port1;

	/**
	 * Second TCP port of the session
	 */
	unsigned short Port2;

	/**
	 * Hash value of IPs+ports
	 */
	uint64_t Hash; //-V122

	/**
	 * Compare this session ID with another
	 * @param other Other session ID
	 * @return True if they are equal
	 */
	inline bool operator==(const SessionID &other) const {
		return (IP1.compare(other.IP1) == 0
				&& IP2.compare(other.IP2) == 0
				&& Port1 == other.Port1
				&& Port2 == other.Port2);
	}

	/**
	 * Create session ID from TCP fragment
	 * @param chunk TCP fragment
	 */
	SessionID(const std::shared_ptr<ChunkTCP> &chunk);
};

/**
 * Hashing class for SessionID
 */
class SessionIDHasher {
public:
	/**
	 * Returns hash value for SessionID
	 * @param k Key (SessionID)
	 * @return Hash value
	 */
	inline std::size_t operator()(const SessionID &k) const
	{
		return (k.Hash);
	}
};

typedef std::unordered_map<SessionID, std::shared_ptr<SessionTCP>, SessionIDHasher> SessionsMap;

/**
 * Build TCP serssions from TCP fragments
 */
class ParserSessionTCP: public Processor<ChunkTCP, SessionTCP> {
public:
	/**
	 * Collect and build TCP session from chunks.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<SessionTCP> Process(const std::shared_ptr<ChunkTCP> &parent);

	virtual void AfterProcess(const std::shared_ptr<SessionTCP> &session);
	virtual int32_t BeforeRecursionHook(const std::shared_ptr<SessionTCP> &session);

	virtual int32_t AfterRecursionHook(const std::shared_ptr<SessionTCP> &session, const std::exception *exn, int32_t followersProcessed);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description();

	void GarbageCollector();

	bool IsFuzzy = false;

	unsigned long long DeleteClosedAfter = 1000;
	unsigned long long DeleteClosingAfter = 1000;
	unsigned long long DeleteInactiveAfter = 10000;
private:
	SessionsMap SessionsCollector;
	Counter IDGenerator;
	Counter SessionIDGenerator;
};

#endif /* SRC_LEVELS_PARSERSESSIONTCP_H_ */
