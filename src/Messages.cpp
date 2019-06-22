#include "Messages.h"

namespace SysComm
{

	NodeEndpoint::NodeEndpoint() noexcept
	{
		Tag = 0;
	}

	bool NodeEndpoint::operator<(const NodeEndpoint& other) const
	{
		if (Tag != other.Tag)
			return Tag < other.Tag;
		else
			return IP < other.IP;
	}

	bool NodeEndpoint::operator==(const NodeEndpoint& other) const
	{
		return (Tag == other.Tag && IP == other.IP);
	}

	bool NodeEndpoint::operator!=(const NodeEndpoint& other) const
	{
		return (Tag != other.Tag || IP != other.IP);
	}

	////////////////////////////////////

	Message::Message() noexcept
	{
		Type = message_t::NONE;
	}

	Message::~Message()
	{
	}
}

namespace Serialize::Binary
{
	using namespace SysComm;
	using namespace StdExt;

	template<>
	void read<Packet>(ByteStream* stream, Packet* out)
	{
		out->Type = stream->read<message_t>();
		out->ActiveSize = stream->read<bytesize_t>();

		if (out->PayloadBuffer.size() < out->ActiveSize)
			out->PayloadBuffer.resize(out->ActiveSize);

		stream->readRaw(out->PayloadBuffer.data(), out->ActiveSize);
	}

	template<>
	void write<Packet> (ByteStream* stream, const Packet& val)
	{
		stream->write<message_t>(val.Type);
		stream->write<bytesize_t>(val.ActiveSize);
		stream->writeRaw(val.PayloadBuffer.data(), val.ActiveSize);
	}
}