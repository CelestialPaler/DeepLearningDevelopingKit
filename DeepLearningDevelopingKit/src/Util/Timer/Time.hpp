/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	               Time     	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <iostream>
#include <chrono>
#include <queue>
#include <string>

/***************************************************************************************************/
// Namespace : Util
/// Providing various tools.
namespace Util
{
	/***************************************************************************************************/
	// Class : Timer
	/// Providing time quantization.
	class Timer
	{
		enum class Precision {
			microsecond,
			second,
			minute
		};

		typedef std::chrono::milliseconds::period Millisec;
		typedef std::chrono::duration<int, Millisec> Duration;
		typedef std::chrono::time_point<std::chrono::steady_clock, Duration> TimePoint;
		typedef std::pair<std::string, TimePoint> TimeCheckPoint;

	public: // Constructors

		// Default constructor
		/// Take no parameters.
		Timer(void);

	public:

		void Start(void);
		void Reset(void);

	public:

		void AddTimeCheckPoint(void);
		void AddTimeCheckPoint(const std::string _checkPointTag);
		void PrintTimeCheckPoint(void);

	public:

		inline const double GetTime() const {
			return std::chrono::duration_cast<Duration>(std::chrono::steady_clock::now() - _timeBase).count();
		}

	private:

		TimePoint _timeBase;
		std::queue<TimeCheckPoint> _timeCheckPoint;
	};
}

namespace Util
{
	inline Timer::Timer()
	{

	}

	inline void Timer::Start(void)
	{
		_timeBase = std::chrono::time_point_cast<Duration>(std::chrono::steady_clock::now());
	}

	inline void Timer::Reset(void)
	{
		_timeBase = std::chrono::time_point_cast<Duration>(std::chrono::steady_clock::now());
	}

	inline void Timer::AddTimeCheckPoint(void)
	{
		TimeCheckPoint temp;
		temp.first = "Default Check Point";
		temp.second = std::chrono::time_point_cast<Duration>(std::chrono::steady_clock::now());
		_timeCheckPoint.push(temp);
	}

	inline void Timer::AddTimeCheckPoint(const std::string _checkPointTag)
	{
		TimeCheckPoint temp;
		temp.first = _checkPointTag;
		temp.second = std::chrono::time_point_cast<Duration>(std::chrono::steady_clock::now());
		_timeCheckPoint.push(temp);
	}

	inline void Timer::PrintTimeCheckPoint(void)
	{
		TimeCheckPoint temp;
		std::cout << "Util::Timer check points : " << std::endl;
		while (!_timeCheckPoint.empty())
		{
			temp = _timeCheckPoint.front();
			std::cout << "Tag : " << temp.first << " | ";
			std::cout << "Time : " << std::chrono::duration_cast<Duration>(temp.second - _timeBase).count() << " ms " << std::endl;
			_timeCheckPoint.pop();
		}
	}
}

