/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Utils / Singleton.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <memory>

////////////////////////////////////////////////////////////////////////////////

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;

private:
	NonCopyable(const NonCopyable &);
	NonCopyable &operator =(const NonCopyable &);
};

////////////////////////////////////////////////////////////////////////////////

class NonMovable
{
protected:
	NonMovable() = default;
	~NonMovable() = default;

private:
	NonMovable(NonMovable &&);
	NonMovable &operator =(NonMovable &&);
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Singleton : public NonCopyable
{
public:
	static T *instance() {
		static std::unique_ptr<T> inst(new T());
		return inst.get();
	}
};