#include "TrackPlatformException.h"

TrackPlatformException::TrackPlatformException()
{
}

#ifdef _WIN32
TrackPlatformException::TrackPlatformException(const std::string& errorMessage)
	: std::exception(errorMessage.c_str())
{
}

#else /* _WIN32 */
TrackPlatformException::TrackPlatformException(const std::string& errorMessage)
    : errorText(errorMessage)
{
}

const char* TrackPlatformException::what() const noexcept
{
    return errorText.c_str();
}

#endif /* _WIN32 */
