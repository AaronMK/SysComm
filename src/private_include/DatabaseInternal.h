#ifndef _SYS_COMM_DATABASE_INTERNAL_H_
#define _SYS_COMM_DATABASE_INTERNAL_H_

#include <SysComm/Config.h>

#include "../private_include/sqlite3/sqlite3.h"

#include <string>

namespace SysComm
{
	/**
	 * @internal
	 */
	class DatabaseInternal
	{
	public:
		DatabaseInternal(const std::string &name);
		virtual ~DatabaseInternal();

		/**
		 * @brief
		 *  The full name used to open the database.
		 */
		std::string mName;

		/**
		 * @brief
		 *  The handle to the database.
		 */
		sqlite3* mDatabase;
	};
}

#endif // _SYS_COMM_DATABASE_INTERNAL_H_