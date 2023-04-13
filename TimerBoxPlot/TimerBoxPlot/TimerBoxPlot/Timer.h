#pragma once
#include <chrono>

template <typename T>
class Timer
{
public:
	static void reset();
	static T elapsed_nanoseconds();
	static T elapsed_microseconds();
	static T elapsed_milliseconds();
	static T elapsed_seconds();
	static T elapsed_minutes();
private:
	typedef std::chrono::high_resolution_clock clock_;
	static std::chrono::time_point<std::chrono::high_resolution_clock> beg_;
};

template <typename T>
void Timer<T>::reset() {
	beg_ = clock_::now();
}

template <typename T>
T Timer<T>::elapsed_nanoseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1, 1000000000> >>(clock_::now() - beg_).count();
}

template <typename T>
T Timer<T>::elapsed_microseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1, 1000000> >>(clock_::now() - beg_).count();
}

template <typename T>
T Timer<T>::elapsed_milliseconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1, 1000> >>(clock_::now() - beg_).count();
}

template <typename T>
T Timer<T>::elapsed_seconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1> >>(clock_::now() - beg_).count();
}

template <typename T>
T Timer<T>::elapsed_minutes() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<60> >>(clock_::now() - beg_).count();
}

template<typename T>
std::chrono::time_point<std::chrono::high_resolution_clock> Timer<T>::beg_ = std::chrono::high_resolution_clock::now();