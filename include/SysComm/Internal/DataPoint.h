#ifndef _SYS_COMM_DATA_POINT_H_
#define _SYS_COMM_DATA_POINT_H_

#include "../ByteArray.h"

#include <Serialize/ByteStream.h>

#include <typeinfo>
#include <cassert>
#include <memory>

namespace SysComm
{
	/**
	 * @internal
	 *
	 * @brief
	 *  The base class for value data stored on the client side.  This serves as an
	 *  interface for DataPoint objects that uses its type parameter to implement
	 *  the pure virtuals of this class.
	 */
	class SYS_COMM_EXPORT DataPointBase
	{
	public:
		DataPointBase();
		virtual ~DataPointBase();

	protected:

		/**
		 * @brief
		 *  A numeric ID that is unique within the owning SysComm instance.
		 */
		uint64_t id();

		/**
		 * @brief
		 *  De-serializes data from inStream at its current seek point
		 *  to set the value of the DataPoint.
		 */
		virtual bool deserialize(Serialize::ByteStream* inStream) = 0;

		/**
		 * @brief
		 *  Writes the value of the DataPoint into outStream.
		 */
		virtual bool serialize(Serialize::ByteStream* outStream) const = 0;

	private:

		uint64_t mID;
	};

	/**
	 * @internal
	 *
	 * Datapoints are stored within clients of a Database.  While the Database will always
	 * store, send, and receive values as serialized data, Datapoints store the actual
	 * value.  The DataPointBase
	 */
	template<typename T>
	class DataPoint : public DataPointBase
	{
	public:
		DataPoint();
		virtual ~DataPoint();

		virtual const std::type_info& type() override;

		T* dataPtr();
		const T* dataPtr() const;

	protected:
		virtual bool deserialize(Serialize::ByteStream* inStream) override;
		virtual bool serialize(Serialize::ByteStream* outStream) const override;

		T mData;
	};

	//////////////////////////////////////

	template<typename T>
	const std::type_info& DataPoint<T>::type()
	{
		return typeid(T);
	}
	
	template<typename T>
	bool DataPoint<T>::deserialize(Serialize::ByteStream* inStream)
	{
		using namespace Serialize;
		return read<T>(stream, &mData);
	}

	template<typename T>
	bool DataPoint<T>::serialize(Serialize::ByteStream* outStream) const
	{
		using namespace Serialize;

		assert((stream->getFlags() & ByteStream::READ_ONLY) == 0);
		return write<T>(outStream, mData);
	}

	
	template<typename T>
	T* DataPoint<T>::dataPtr()
	{
		return &mData;
	}

	
	template<typename T>
	const T* DataPoint<T>::dataPtr() const
	{
		return &mData;
	}
}

#endif // _SYS_COMM_DATA_POINT_H_