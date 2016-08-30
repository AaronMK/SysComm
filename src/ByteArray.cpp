#include <SysComm/ByteArray.h>

#include <cstdlib>
#include <algorithm>

namespace SysComm
{
	ByteArray::ByteArray(const ByteArray &other)
		: ByteArray()
	{
		resize(other.mDataSize, other.mDataAlignment);
	}

	ByteArray::ByteArray(ByteArray&& other)
	{
		mData = other.mData;
		mDataSize = other.mDataSize;
		mDataAlignment = other.mDataAlignment;

		other.mData = nullptr;
		other.mDataSize = 0;
		other.mDataAlignment = 0;
	}

	ByteArray::ByteArray()
	{
		mData = nullptr;
		mDataSize = 0;
		mDataAlignment = 0;
	}

	ByteArray::ByteArray(uint32_t pSize, uint32_t alignment)
		: ByteArray()
	{
		resize(pSize, alignment);
	}
	
	ByteArray::~ByteArray()
	{
		_aligned_free(mData);
	}

	bool ByteArray::resize(uint32_t pSize, uint32_t alignment)
	{
		alignment = std::max<uint32_t>(1, alignment);

		if (pSize == mDataSize && alignment == mDataAlignment)
			return true;

		if (0 == pSize)
		{
			_aligned_free(mData);
			
			mData = nullptr;
			mDataSize = 0;
			mDataAlignment = 0;

			return true;
		}

		void* ptrAligned = nullptr;
		bool moveNeeded = false;

		if (nullptr == mData)
		{
			ptrAligned = _aligned_malloc(pSize, alignment);
		}
		else if (alignment != mDataAlignment)
		{
			mData = _aligned_malloc(pSize, alignment);
			moveNeeded = true;
		}
		else
		{
			void* ptrAligned = _aligned_realloc(mData, pSize, alignment);
		}

		if (nullptr == ptrAligned)
			return false;

		if (moveNeeded)
		{
			uint32_t copyCount = std::min(pSize, mDataSize);
			memcpy(ptrAligned, mData, copyCount);

			_aligned_free(mData);
		}

		mData = ptrAligned;
		mDataSize = pSize;
		mDataAlignment = alignment;

		return true;
	}

	bool ByteArray::resize(uint32_t pSize)
	{
		return resize(pSize, mDataAlignment);
	}

	uint32_t ByteArray::size() const
	{
		return mDataSize;
	}

	uint32_t ByteArray::alignment() const
	{
		return mDataAlignment;
	}

	void* ByteArray::data()
	{
		return mData;
	}

	const void* ByteArray::data() const
	{
		return mData;
	}
}



namespace Serialize
{
	template<>
	bool read<SysComm::ByteArray>(ByteStream* stream, SysComm::ByteArray *out)
	{
		seek_t seekBack = stream->getSeekPosition();
		uint32_t arraySize = 0;
		uint32_t dataAlignment = 1;

		if ( read<uint32_t>(stream, &arraySize) &&
		     read<uint32_t>(stream, &dataAlignment) &&
		     stream->canRead(arraySize) &&
			 out->resize(arraySize, dataAlignment) &&
			 stream->readRaw(out->data(), arraySize))
		{
			return true;
		}

		stream->seek(seekBack);
		return false;
	}

	template<>
	bool write<SysComm::ByteArray>(ByteStream* stream, const SysComm::ByteArray &val)
	{
		seek_t seekBack = stream->getSeekPosition();

		if ( write(stream, val.size()) && write(stream, val.alignment()) && 
		     stream->writeRaw(val.data(), val.size()) )
		{
			return true;
		}

		stream->seek(seekBack);
		return false;
	}
}