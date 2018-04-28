/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Timer     	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <iostream>
#include <chrono>

namespace Util
{
	/***************************************************************************************************/
	// Class : Timer
	/// Providing time quantization.
	template<typename T>
	class Timer
	{
		typedef std::chrono::duration<double, typename T::period> Duration;
		typedef std::chrono::time_point<std::chrono::steady_clock, Duration> TimePoint;

	public:

		Timer();

	public:

		inline double gettime() const { return std::chrono::duration_cast<Duration>(std::chrono::steady_clock::now() - timeBase).count(); }
	
	private:
	
		TimePoint timeBase;
	};

	template<typename T>
	inline Timer<T>::Timer()
	{
		timeBase = std::chrono::time_point_cast<Duration>(std::chrono::steady_clock::now());
	}
}

