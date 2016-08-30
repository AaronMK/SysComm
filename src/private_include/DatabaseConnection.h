#ifndef _SYS_COMM_DATABASE_CONNECTION_H_
#define _SYS_COMM_DATABASE_CONNECTION_H_

#include <SysComm/Database.h>

#include <Concurrent/Reference.h>

#include "../private_include/sqlite3/sqlite3.h"

#include <array>

namespace SysComm
{
	class DatabaseConnection
	{
	public:
		DatabaseConnection(Database* database);
		virtual ~DatabaseConnection();

		int64_t setDatapoint(const std::string &name, const std::string &description, const void* data = nullptr, int dataSize = 0);

	private:
		enum SqlStatements
		{
			SET_DATAPOINT = 0,
			NUM_STATEMENTS
		};

		sqlite3* mConnection;
		std::array<sqlite3_stmt*, NUM_STATEMENTS> mStatements;

		Concurrent::Reference<DatabaseInternal> mInternal;
	};
}




#endif // _SYS_COMM_DATABASE_CONNECTION_H_