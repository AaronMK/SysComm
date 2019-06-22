#ifndef _SYS_COMM_FUNCTION_H_
#define _SYS_COMM_FUNCTION_H_

#include "LinkPoint.h"
#include "Link.h"

#include <Serialize/Binary/Binary.h>

#include <StdExt/Utility.h>

#include <tuple>
#include <functional>
#include <type_traits>

namespace SysComm
{
	template<typename ret_t, typename ...params_t>
	class Function : public LinkPoint
	{
	public:
		using input_t = std::conditional_t<
			(sizeof...(params_t) > 0),
			std::tuple<params_t...>,
			void
		>;

		using return_t = ret_t;
		using my_type = Function<ret_t, params_t...>;

		Function(const StdExt::String& pName);

		virtual Container clone() const override;

		virtual StdExt::Any deserializeInput(Serialize::Binary::ByteStream* inStream) const override;
		virtual void serializeOutput(const StdExt::Any& value, Serialize::Binary::ByteStream* outStream) const override;
	};

	template<typename ret_t, typename ...params_t>
	class FunctionHandler : public Link
	{
	public:
		using return_t = ret_t;
		using handler_t = std::function<ret_t(params_t...)>;
		using link_t = Function<ret_t, params_t...>;
		
		using input_t = std::conditional_t<
			(sizeof...(params_t) > 0),
			std::tuple<params_t...>,
			void
		>;

	private:
		uint32_t mPassword;
		handler_t mHandler;

	public:
		FunctionHandler();
		FunctionHandler(const handler_t& handler);
		FunctionHandler(handler_t&& handler);

		virtual Permission permission() const override;
		virtual uint32_t password() const override;

		virtual StdExt::Any handleUpdate(const StdExt::Any& update) override;
	};

	/////////////////////////////

	template<typename ret_t, typename ...params_t>
	Function<ret_t, params_t...>::Function(const StdExt::String& pName)
		: LinkPoint(pName)
	{
	}

	template<typename ret_t, typename ...params_t>
	LinkPoint::Container Function<ret_t, params_t...>::clone() const
	{
		return Container::make<my_type>(name());
	}


	template<typename ret_t, typename ...params_t>
	StdExt::Any Function<ret_t, params_t...>::deserializeInput(Serialize::Binary::ByteStream* inStream) const
	{
		if constexpr (sizeof...(params_t) > 0)
		{
			return StdExt::Any::make<input_t>(
				inStream->readTuple<params_t...>()
			);
		}
		else
		{
			return StdExt::Any();
		}
	}

	template<typename ret_t, typename ...params_t>
	void Function<ret_t, params_t...>::serializeOutput(const StdExt::Any& value, Serialize::Binary::ByteStream* outStream) const
	{
		if constexpr (!std::is_void_v<ret_t>)
			Serialize::Binary::write<ret_t>(outStream, *value.cast<ret_t>());
	}

	//////////////////////////////

	template<typename ret_t, typename ...params_t>
	FunctionHandler<ret_t, params_t...>::FunctionHandler()
	{
		mPassword = StdExt::rand<uint32_t>(1);
	}

	template<typename ret_t, typename ...params_t>
	FunctionHandler<ret_t, params_t...>::FunctionHandler(const handler_t& handler)
		: mHandler(handler)
	{
		mPassword = StdExt::rand<uint32_t>(1);
	}

	template<typename ret_t, typename ...params_t>
	FunctionHandler<ret_t, params_t...>::FunctionHandler(handler_t&& handler)
		: mHandler(std::move(handler))
	{
		mPassword = StdExt::rand<uint32_t>(1);
	}

	template<typename ret_t, typename ...params_t>
	Link::Permission FunctionHandler<ret_t, params_t...>::permission() const
	{
		return Permission::ExclusiveReceive;
	}

	template<typename ret_t, typename ...params_t>
	uint32_t FunctionHandler<ret_t, params_t...>::password() const
	{
		return mPassword;
	}

	template<typename ret_t, typename ...params_t>
	StdExt::Any FunctionHandler<ret_t, params_t...>::handleUpdate(const StdExt::Any& update)
	{
		if constexpr (std::is_void_v<return_t>)
		{
			if constexpr (std::is_void_v<input_t>)
				mHandler();
			else
				std::apply(mHandler, *update.cast<input_t>());

			return StdExt::Any();
		}
		else
		{
			if constexpr (std::is_void_v<input_t>)
			{
				return StdExt::Any::make<return_t>(mHandler());
			}
			else
			{
				return StdExt::Any::make<return_t>(
					std::apply(mHandler, *update.cast<input_t>())
				);
			}
		}
	}
}

#endif // _SYS_COMM_FUNCTION_H_