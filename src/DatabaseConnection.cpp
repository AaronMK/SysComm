#include "private_include/DatabaseConnection.h"

#include "private_include/DatabaseInternal.h"

namespace SysComm
{
	//////////////////////////////////////////////////////////

	DatabaseConnection::DatabaseConnection(Database* database)
	{
		mInternal = database->mInternal;
		mStatements.fill(nullptr);

		if ( mInternal && (SQLITE_OK == sqlite3_open(mInternal->mName.c_str(), &mConnection)) )
		{
		}
	}
		
	DatabaseConnection::~DatabaseConnection()
	{
		for (uint32_t i = 0; i < mStatements.size(); ++i)
			sqlite3_finalize(mStatements[i]);

		sqlite3_close(mConnection);
	}

	int64_t DatabaseConnection::setDatapoint(const std::string &name, const std::string &description, const void* data, int dataSize)
	{
		if (!mInternal)
			return -1;

		if (nullptr == mStatements[SET_DATAPOINT])
		{
			sqlite3_prepare(mConnection,"INSERT OR REPLACE INTO "
			                "DataPoints (name, description, value) VALUES (?, ?, ?)",
			                -1, &mStatements[SET_DATAPOINT], nullptr);
		}

		sqlite3_bind_text(mStatements[SET_DATAPOINT], 1, name.c_str(), name.length(), nullptr);
		sqlite3_bind_text(mStatements[SET_DATAPOINT], 2, description.c_str(), description.length(), nullptr);
		sqlite3_bind_blob(mStatements[SET_DATAPOINT], 3, data, dataSize, SQLITE_STATIC);

		bool ret = (SQLITE_DONE == sqlite3_step(mStatements[SET_DATAPOINT]));
		int64_t rowID = sqlite3_last_insert_rowid(mConnection);

		sqlite3_clear_bindings(mStatements[SET_DATAPOINT]);
		sqlite3_reset(mStatements[SET_DATAPOINT]);

		return rowID;
	}

}