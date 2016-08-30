#ifndef _SYS_COMM_PUBLISHER_H_
#define _SYS_COMM_PUBLISHER_H_

#include "Config.h"

#include "Internal/DataPoint.h"

#include <Concurrent/Reference.h>

namespace SysComm
{
	/**
	 * @brief
	 *  A publishing object for a data point.
	 *
	 *  For any given named datapoint in a database, there can only be one publishing
	 *  object.  This encourages the idea that there should be a single authority for
	 *  a particular state.
	 *
	 *  The value is accessed and manipulated using the -> operator, and publish()
	 *  will send the value to all subscribers of the data point.
	 */
	template<typename T>
	class Publisher
	{
	public:
		Publisher();
		virtual ~Publisher();

		/**
		 * @brief
		 *  Links the object to a named data point in the passed
		 *  Database.
		 */
		void link(Database* database, const std::string &name);
		
		/**
		 * @brief
		 *  Publishes the value of the data point to all subscribers.
		 */
		void publish();

		/**
		 * @brief
		 *  Publishes the value of the data point to all subscribers.
		 */
		T* operator->();

	private:
		Concurrent::Reference< DataPoint<T> > mDataPoint;
	};

	////////////////////////////////////

	template<typename T>
	Publisher<T>::Publisher()
	{

	}

	template<typename T>
	Publisher<T>::Publisher()
	{

	}
	
	template<typename T>
	void Publisher<T>::link(Database* database, const std::string &name)
	{

	}

	template<typename T>
	void Publisher<T>::publish()
	{

	}
	

	template<typename T>
	T* Publisher<T>::operator->()
	{
		return mDataPoint->dataPtr();
	}
}

#endif // _SYS_COMM_PUBLISHER_H_