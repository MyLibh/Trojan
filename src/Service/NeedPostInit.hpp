#pragma once

#ifndef __NEEDPOSTINIT_HPP_INCLUDED__
#define __NEEDPOSTINIT_HPP_INCLUDED__

namespace
{
	template<typename T, typename = void> 
	struct has_default_init : std::false_type
	{ };

	template<typename T> 
	struct has_default_init<T, std::void_t<decltype(std::declval<T>().init())>> : std::true_type
	{ };

	template<typename T>
	constexpr bool has_default_init_v = has_default_init<T>::value;
} // namespace anonymous

class NeedPostInit 
{
protected:
	~NeedPostInit() = default;

public:
	template<typename T, typename... Args>
	static std::shared_ptr<T> create(const Args& ... args);
};

template<typename T, typename... Args>
std::shared_ptr<T> NeedPostInit::create(const Args& ... args)
{
	static_assert(has_default_init_v<T>);

	auto ptr{ std::make_shared<T>() };
	ptr->init(args...);

	return ptr;
}

#endif /* __NEEDPOSTINIT_HPP_INCLUDED__ */