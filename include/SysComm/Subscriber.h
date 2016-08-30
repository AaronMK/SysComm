#ifndef _SYS_COMM_SUBSCRIBER_H_
#define _SYS_COMM_SUBSCRIBER_H_

#include "Config.h"

#include "Internal/DataPoint.h"

#include <Concurrent/Reference.h>

#include <functional>

namespace SysComm
{
	/**
	 * @brief
	 *  A subscribing object for a data point.
	 *
	 *  The value is accessed using the -> operator.
	 */
	template<typename T>
	class Subscriber
	{
	public:
		typedef std::function<void(const T&)> ChangeHandler;

		Subscriber();
		virtual ~Subscriber();

		/**
		 * @brief
		 *  Links the object to a named data point in the passed
		 *  Database, keeping the value updated as publishers update it.
		 */
		void link(Database* database, const std::string &name);
		
		/**
		 * @brief
		 *  Links the object to a named data point in the passed
		 *  Database, calling the passed handler when the value
		 *  is updated.
		 */
		void link(Database* database, const std::string &name, ChangeHandler&& handler);

		/**
		 * @brief
		 *  Access to the value.
		 */
		const T* operator->() const;

	private:
		Concurrent::Reference< DataPoint<T> > mDataPoint;
	};

	////////////////////////////////////

	template<typename T>
	Subscriber<T>::Subscriber()
	{

	}

	template<typename T>
	Subscriber<T>::Subscriber()
	{

	}
	
	template<typename T>
	void Subscriber<T>::link(Database* database, const std::string &name)
	{

	}
	
	template<typename T>
	void Subscriber<T>::link(Database* database, const std::string &name, ChangeHandler&& handler)
	{

	}

	template<typename T>
	const T* Subscriber<T>::operator->() const
	{
		return mDataPoint->dataPtr();
	}
}

#endif // _SYS_COMM_SUBSCRIBER_H_