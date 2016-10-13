
#ifndef SRC_LEVELS_LEAFPROCESSOR_H_
#define SRC_LEVELS_LEAFPROCESSOR_H_

#include "../types/Processor.h"
#include "ChunkRaw.h"
#include "ChunkEtherNet.h"
#include "ChunkEtherNetDIX.h"
#include "ChunkIPv4.h"

template <class THIS>
class LeafProcessor: public Processor<THIS, ChunkRaw> {
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkEtherNet> parent)
	{
		std::cout << "Ethernet!\n";
		return (std::shared_ptr<ChunkRaw>(nullptr));
	}

	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkEtherNetDIX> parent)
	{
		std::cout << "DIX!\n";
		return (std::shared_ptr<ChunkRaw>(nullptr));
	}

	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkIPv4> parent)
	{
		std::cout << "IPv4!\n";
		return (std::shared_ptr<ChunkRaw>(nullptr));
	}


	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID()
	{
		return (std::string("Leaf_test"));
	}

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description()
	{
		return (std::string("Test"));
	}
};

#endif /* SRC_LEVELS_LEAFPROCESSOR_H_ */
