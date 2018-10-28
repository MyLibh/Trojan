#pragma once

#ifndef __NEEDPOSTINIT_HPP_INCLUDED__
#define __NEEDPOSTINIT_HPP_INCLUDED__

namespace
{
	template<typename T, typename = void> 
	struct has_release_func : std::false_type
	{ };

	template<typename T> 
	struct has_release_func<T, std::void_t<decltype(std::declval<T>().release())>> : std::true_type
	{ };

	template<typename T>
	constexpr bool has_release_func_v = has_release_func<T>::value;

	template<typename T>
	class Deleter
	{
	public:
		void operator()(T *ptr)
		{
			static_assert(has_release_func_v<T>);

			if (ptr)
			{
				ptr->release();

#pragma warning(suppress : 26401 26409)
				// warning C26401: Do not delete a raw pointer that is not an owner<T> (i.11).
				// warning C26409: Avoid calling new and delete explicitly, use std::make_unique<T> instead (r.11).
				delete ptr;

				ptr = nullptr;
			}

		}
	};
} // namespace anonymous

class NeedPostInit 
{
protected:
	~NeedPostInit() = default;

public:
	template<typename T, typename... Args>
	static std::shared_ptr<T> create(Args... args);

	template<typename T, typename... Args>
	static std::shared_ptr<T> create_with_deleter(Args... args);
};

template<typename T, typename... Args>
std::shared_ptr<T> NeedPostInit::create(Args... args)
{
	auto ptr{ std::make_shared<T>() }; 
	ptr->init(args...);

	return ptr;
}

template<typename T, typename... Args>
std::shared_ptr<T> NeedPostInit::create_with_deleter(Args... args)
{
	auto ptr{ std::shared_ptr<T>(new T(), Deleter<T>() ) };
	ptr->init(args...);

	return ptr;
}

#endif /* __NEEDPOSTINIT_HPP_INCLUDED__ */