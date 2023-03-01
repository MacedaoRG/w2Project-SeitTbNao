#pragma once

template<class T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;

		return instance;
	}

protected:
	Singleton() = default;

private:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator= (Singleton&) = delete;
	Singleton& operator= (const Singleton&&) = delete;
};