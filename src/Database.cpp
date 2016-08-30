#include <SysComm/Database.h>

#include "private_include/DatabaseInternal.h"

#include <sstream>

namespace SysComm
{
	using namespace Concurrent;

	Database Database::inMemory(const std::string &name)
	{
		std::stringstream ss;
		ss << "file:" << name << "?mode=memory&cache=shared";

		return Database(ss.str());
	}

	Database Database::inFile(const std::string &name)
	{
		return Database(name);
	}

	Database::Database(Database&& other)
	{
		mInternal = other.mInternal;
		other.mInternal = nullptr;
	}

	Database::Database(const std::string &name)
	{
		mInternal = Reference<DatabaseInternal>::create(name);
	}
}