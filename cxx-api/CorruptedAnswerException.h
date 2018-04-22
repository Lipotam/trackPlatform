#ifndef _CORRUPTED_ANSWER_EXCEPTION_H_
#define _CORRUPTED_ANSWER_EXCEPTION_H_
#include "TrackPlatformException.h"

class CorruptedAnswerException : public TrackPlatformException
{
public:
	explicit CorruptedAnswerException() : TrackPlatformException()
	{
	}
};

#endif /* _CORRUPTED_ANSWER_EXCEPTION_H_ */
