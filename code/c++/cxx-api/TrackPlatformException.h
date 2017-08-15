#ifndef _TRACK_PLATFORM_EXCEPTION_H_
#define _TRACK_PLATFORM_EXCEPTION_H_

#include <exception>
#include <string>

class TrackPlatformException : public std::exception
{
#ifndef _WIN32
    std::string errorText;
#endif /* _WIN32 */

public:
	TrackPlatformException();
	explicit TrackPlatformException(const std::string& errorMessage);

#ifndef _WIN32
    const char* what() const noexcept override;
#endif /* _WIN32 */
};

#endif /* _TRACK_PLATFORM_EXCEPTION_H_ */
