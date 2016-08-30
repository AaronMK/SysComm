#ifndef _SYS_COMM_DATABASE_H_
#define _SYS_COMM_DATABASE_H_

#include "Config.h"

#include <Concurrent/Reference.h>

#include <string>

namespace SysComm
{
	class DatabaseInternal;

	/**
	 * @brief
	 *  Stores the values of all datapoints in serialized form, and keeps
	 *  track of connections.  It tracks Publishers and Subscribers for each
	 *  DatabaseConnection, passing updates as needed.
	 */
	class SYS_COMM_EXPORT Database
	{
		friend class DatabaseConnection;
	public:
		Database& operator=(const Database&) = delete;
		Database(const Database&) = delete;

		/**
		 * @brief
		 *  Creates a database in memory with the provided name, which can have
		 *  underscores ("_"), numbers, and letters.
		 */
		static Database inMemory(const std::string &name);

		/**
		 * @brief
		 *  Open a database from disk which will have its state updated.
		 */
		static Database inFile(const std::string &name);
		
		/**
		 * @brief
		 *  Move constructor.
		 */
		Database(Database&& other);

	private:
		Database(const std::string &name);

		/**
		 * @brief
		 *  The REAL database object that has shared ownership with all other connecting
		 *  objects.
		 */
		Concurrent::Reference<DatabaseInternal> mInternal;
	};
}

#endif // _SYS_COMM_DATABASE_H_