// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef RECURSIVEDELEGATOR_H_
#define RECURSIVEDELEGATOR_H_

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

namespace RecursiveDelegator {

template<typename PARENT, typename THIS>
class Processor
{
public:
	uint16_t RecursiveParents = 0;

	Processor() {};

	virtual ~Processor()
	{
		for (auto i : Followers) {
			i->RecursiveParents--;
			if (!i->RecursiveParents)
				delete i;
		}
	};

	typedef Processor<THIS, void> FollowerType;

	std::vector<FollowerType *> Followers;

	void AddFollower(FollowerType *follower)
	{
		Followers.push_back(follower);
		follower->RecursiveParents++;
	};

	virtual std::shared_ptr<THIS> Process(const std::shared_ptr<PARENT> &parent) = 0;

	// If returned -1 no followers are allowed
	// If returned 0 followers must be processed in normal way
	// If returned >0 do not process followers and return this value
	virtual int32_t BeforeRecursionHook(const std::shared_ptr<THIS> &got) { return (0); };


	virtual int32_t AfterRecursionHook(const std::shared_ptr<THIS> &got, const std::exception *exn, int32_t processed_followers)
	{
		if (exn != nullptr) {
			throw (*exn);
		} else {
			return (processed_followers);
		};
	};

	Processor<PARENT, void> *AsFollower() { return(reinterpret_cast<Processor<PARENT, void> *>(this)); }

	// Returns -1 if parsing wan't successful
	// Returns number of processed followers
	int32_t Recursive (std::shared_ptr<PARENT> parent)
	{
		std::shared_ptr<THIS> got = Process(parent);
		if (got != nullptr) {
			int32_t found = 0;
			try {
				int32_t result = BeforeRecursionHook(got);
				if (result == -1) {
					return (AfterRecursionHook(got, nullptr, 0));
				} else if (result > 0) {
					return (AfterRecursionHook(got, nullptr, result));
				} else if (result == 0) {
					for (auto f : Followers) {
						int32_t result = f->Recursive(got);
						if (result >= 0) {
							found++;
							break;
						}
					}
				}
			} catch (const std::exception &exn) {
				return (AfterRecursionHook(got, &exn, found));
			}
			return (AfterRecursionHook(got, nullptr, found));
		}
		return (-1);
	}
};

}

// Example usage
/*
template<typename PARENT, typename THIS>
class Base : public Processor<PARENT, THIS>
{
	void AfterRecursionHook(THIS *got)
	{
		delete got;
	}
};

class StringOfInt : public Base<int, std::string>
{
	public:

		std::string *Process(int *p)
		{
			std::cout << "(StringOfInt) My parent is: " << (*p) << std::endl;
			std::string *r = new std::string("hello");
			return (r);
		}
};

class DoubleOfString : public Base<std::string, double>
{
	public:
		double *Process(std::string *p)
		{
			std::cout << "(DoubleOfString) My parent is: " << (*p) << std::endl;
			double *r = new double(3.14);
			return (r);
		}
};

class IntOfDouble : public Base<double, int>
{
	public:
		int *Process(double *p)
		{
			std::cout << "(IntOfDouble) My parent is: " << (*p) << std::endl;
			return (new int(5));
		}
};

int main ()
{
	// accepts string, generates double, calls double->any
	DoubleOfString *doubleOfString = new DoubleOfString;

	// accepts double, generates int, calls int->any
	IntOfDouble *intOfDouble = new IntOfDouble;

	// accepts int, generates string, calls string->any
	StringOfInt *stringOfInt = new StringOfInt;

	doubleOfString->AddFollower((Processor<double, void>*)intOfDouble);
	doubleOfString->AddFollower((Processor<double, void>*)intOfDouble);
	intOfDouble->AddFollower((Processor<int, void>*)stringOfInt);

	std::string *input = new std::string("input data");
	doubleOfString->Recursive(input);

	delete doubleOfString;
	delete intOfDouble;
	delete stringOfInt;
	delete input;
}
*/

#endif
