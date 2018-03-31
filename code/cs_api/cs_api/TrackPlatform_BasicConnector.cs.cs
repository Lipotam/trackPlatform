public class TrackPlatform_BasicConnector
{
//C++ TO C# CONVERTER WARNING: The original C++ declaration of the following method implementation was not found:
	public void Dispose()
	{
		readWriteAtomicMutex.try_lock();
		readWriteAtomicMutex.unlock();
	}
}