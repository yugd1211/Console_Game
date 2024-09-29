#pragma once

template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
protected:
	Singleton();
	virtual ~Singleton() {};

};

template<typename T>
inline Singleton<T>::Singleton()
{
}
