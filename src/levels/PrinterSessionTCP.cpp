// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

void PrintFlow(std::shared_ptr<EndPoint> flow, const std::string &who) {
	try {
		if (flow->Payload != nullptr && flow->Payload->CoveredSize) {
			std::string payload = flow->Payload->GetMaxSubString(0, 20000);
			std::cout << "TCP " << who << " says:\n" << payload[0] << "\n\n";
		}
	} catch (...) {
		return;
	}
}

std::shared_ptr<ChunkRaw> PrinterSessionTCP::Process(const std::shared_ptr<SessionTCP> &session)
{
	PrintFlow(session->Client, "client");
	PrintFlow(session->Server, "server");

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
