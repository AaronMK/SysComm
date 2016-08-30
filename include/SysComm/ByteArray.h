#ifndef _SYS_COMM_BYTE_ARRAY_H_
#define _SYS_COMM_BYTE_ARRAY_H_

#include "Config.h"

#include <Serialize/Serialize.h>

namespace SysComm
{
	class SYS_COMM_EXPORT ByteArray
	{
	public:
		ByteArray(const ByteArray &other);
		ByteArray(ByteArray&& other);

		ByteArray();
		ByteArray(uint32_t pSize, uint32_t alignment = 0);
		
		virtual ~ByteArray();

		/**
		 * @brief
		 *  Reallocates the byte array, keeping any data up to the new
		 *  size.
		 */
		bool resize(uint32_t pSize, uint32_t alignment);

		/**
		 * @brief
		 *  Reallocates the byte array, keeping any data up to the new
		 *  size and the same alignment as the previous allocation.
		 */
		bool resize(uint32_t pSize);

		/**
		 * @brief
		 *  Returns the size of the allocated byte array.
		 */
		uint32_t size() const;

		uint32_t alignment() const;

		void* data();

		const void* data() const;

	private:
		uint32_t mDataSize;
		uint32_t mDataAlignment;
		void* mData;
	};
}

namespace Serialize
{
	template<>
	SYS_COMM_EXPORT bool read<SysComm::ByteArray>(ByteStream* stream, SysComm::ByteArray *out);

	template<>
	SYS_COMM_EXPORT bool write<SysComm::ByteArray>(ByteStream* stream, const SysComm::ByteArray &val);
}

#endif // _SYS_COMM_BYTE_ARRAY_H_