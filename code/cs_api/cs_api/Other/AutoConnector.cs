using System;

public class Data
{
	public Action callback;
	public std::atomic_bool pIsRepeat;
	public uint32_t frequency = new uint32_t();
}

public class AutoConnector : System.IDisposable
{
	private std::thread pConnectingThread;
	private Action callback;
	private std::atomic_bool isRepeat = new std::atomic_bool();
	private uint32_t frequency = new uint32_t();

	/**
	 * @param c Callback to run by timer
	 * @param f Time to wait before next callback call in milliseconds
	 */
	public AutoConnector(Action c, uint32_t f)
	{
		this.pConnectingThread = null;
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: this.callback = c;
		this.callback.CopyFrom(c);
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: this.frequency = f;
		this.frequency.CopyFrom(f);
		isRepeat.store(false);
	}
	public void Dispose()
	{
		stop();
	}
	public void start()
	{
		if (!isRepeat.load() && pConnectingThread == null)
		{
			Data d = new Data();
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: d.callback = callback;
			d.callback.CopyFrom(callback);
			d.pIsRepeat = isRepeat;
//C++ TO C# CONVERTER TODO TASK: The following line was determined to be a copy assignment (rather than a reference assignment) - this should be verified and a 'CopyFrom' method should be created:
//ORIGINAL LINE: d.frequency = frequency;
			d.frequency.CopyFrom(frequency);
			isRepeat.store(true);
//C++ TO C# CONVERTER TODO TASK: Only lambda expressions having all locals passed by reference can be converted to C#:
//ORIGINAL LINE: pConnectingThread = new std::thread([d]()
			pConnectingThread = new std::thread(() =>
			{
				while (d.pIsRepeat.load())
				{
					d.callback();
					std::this_thread.sleep_for(std::chrono.milliseconds(d.frequency));
				}
			});
		}
	}
	public void stop()
	{
		if (isRepeat.load() && pConnectingThread != null)
		{
			isRepeat.store(false);
			pConnectingThread.join();
			pConnectingThread = null;
			pConnectingThread = null;
		}
	}
	public bool isConnecting()
	{
		return isRepeat.load();
	}
}