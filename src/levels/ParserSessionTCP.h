
#ifndef SRC_LEVELS_PARSERSESSIONTCP_H_
#define SRC_LEVELS_PARSERSESSIONTCP_H_

#include <string.h>
#include <unordered_map>
#include "ChunkTCP.h"
#include "SessionTCP.h"
#include "../types/Processor.h"
#include "../types/Counter.h"

class SessionID {
public:
	std::string IP1, IP2;
	unsigned short Port1, Port2;
	std::size_t Hash;

	inline bool operator==(const SessionID &other) const {
		return (IP1.compare(other.IP1) == 0
				&& IP2.compare(other.IP2) == 0
				&& Port1 == other.Port1
				&& Port2 == other.Port2);
	}

	SessionID(std::shared_ptr<ChunkTCP> chunk);
};

class SessionIDHasher {
public:
	inline std::size_t operator()(const SessionID &k) const
	{
		return (k.Hash);
	}
};

typedef std::unordered_map<SessionID, std::shared_ptr<SessionTCP>, SessionIDHasher> SessionsMap;

class ParserSessionTCP: public Processor<ChunkTCP, SessionTCP> {
	/**
	 * Collect and build TCP session from chunks.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<SessionTCP> Process(std::shared_ptr<ChunkTCP> parent);

	void AfterRecursionHook(std::shared_ptr<SessionTCP> session, std::exception *exn, bool found);

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

	unsigned long long DeleteClosedAfter = 1000;
	unsigned long long DeleteClosingAfter = 1000;
	unsigned long long DeleteInactiveAfter = 20000;
private:
	SessionsMap SessionsCollector;
	Counter IDGenerator;
};

#endif /* SRC_LEVELS_PARSERSESSIONTCP_H_ */
