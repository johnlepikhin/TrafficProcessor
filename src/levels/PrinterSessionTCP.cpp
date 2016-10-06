
#include "PrinterSessionTCP.h"

#include <iostream>

std::string PrinterSessionTCP::ID()
{
	return (std::string("TCP_Session_Printer"));
}

std::string PrinterSessionTCP::Description()
{
	return (std::string("TCP session printer"));
}

void PrintFlow(std::shared_ptr<Flow> flow, const std::string &who) {
	try {
		if (flow != nullptr && flow->Payload != nullptr) {
			std::string *payload = flow->Payload->GetSubStringOrFail(0, 20);
			std::cout << "TCP " << who << " says:\n" << payload[0] << "\n\n";

			delete payload;
		}
	} catch (...) {

	}

}

std::shared_ptr<ChunkRaw> PrinterSessionTCP::Process(std::shared_ptr<SessionTCP> session)
{
	PrintFlow(session->ServerFlow, "server");
	PrintFlow(session->ClientFlow, "client");

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
