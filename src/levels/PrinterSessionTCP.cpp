
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

void PrintFlow(EndPoint *flow, const std::string &who) {
	try {
		if (flow->Payload != nullptr && flow->Payload->CoveredSize) {
			std::string *payload = flow->Payload->GetMaxSubString(0, 20000);
			std::cout << "TCP " << who << " says:\n" << payload[0] << "\n\n";

			delete payload;
		}
	} catch (...) {

	}

}

std::shared_ptr<ChunkRaw> PrinterSessionTCP::Process(std::shared_ptr<SessionTCP> session)
{
	PrintFlow(session->Client, "client");
	PrintFlow(session->Server, "server");

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
