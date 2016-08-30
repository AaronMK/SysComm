#include "private_include/DatabaseInternal.h"

#include <Concurrent/Mutex.h>
#include <Concurrent/MutexLocker.h>

#include <atomic>

namespace SysComm
{
	using namespace Concurrent;
	
	static std::atomic<uint32_t> sqlCount(0);
	static Mutex                 sqlInit;

	bool acquireSqlite()
	{
		MutexLocker lock(&sqlInit);

		if (0 == sqlCount.fetch_add(1))
		{
			sqlite3_config(SQLITE_CONFIG_URI, 1);
			sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
			sqlite3_initialize();
		}

		return true;
	}

	void releaseSqlite()
	{
		MutexLocker lock(&sqlInit);

		if (1 == sqlCount.fetch_sub(1))
		{
			sqlite3_shutdown();
		}
	}

	//////////////////////////////////////////////////////

	DatabaseInternal::DatabaseInternal(const std::string &name)
	{
		acquireSqlite();

		mDatabase = nullptr;
		mName = name;

		if (SQLITE_OK == sqlite3_open(mName.c_str(), &mDatabase))
		{
			sqlite3_exec(mDatabase,
				"CREATE TABLE IF NOT EXISTS DataPoints(rowid, name STRING PRIMARY KEY, "
				"description STRING, value BLOB)",
				nullptr, nullptr, nullptr);
		}
	}

	DatabaseInternal::~DatabaseInternal()
	{
		sqlite3_close(mDatabase);
		releaseSqlite();
	}
}