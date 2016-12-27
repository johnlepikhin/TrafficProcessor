
#ifndef SRC_LEVELS_TCPSESSIONFOLLOWERHOLDER_H_
#define SRC_LEVELS_TCPSESSIONFOLLOWERHOLDER_H_

#include "../types/Processor.h"
#include "SessionTCP.h"
#include <unordered_map>

template <typename RESULT>
class TCPSessionFollowerHolder: public Processor<SessionTCP, RESULT> {
private:
	std::unordered_map<uint64_t, std::shared_ptr<RESULT> > SessionsMap;
	virtual std::shared_ptr<RESULT> FollowerProcess(const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<RESULT> follower) = 0;
public:
	std::shared_ptr<RESULT> Process(const std::shared_ptr<SessionTCP> &session);
	virtual ~TCPSessionFollowerHolder() {};
};

#endif /* SRC_LEVELS_TCPSESSIONFOLLOWERHOLDER_H_ */
