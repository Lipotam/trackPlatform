#pragma once

class MainManager
{
	static MainManager* manager_;

	MainManager();
	MainManager(MainManager&);
	~MainManager();

public:
	static MainManager* get_manager();

	void run();

	void stop_all();
	void reset_current_connection();
	void set_current_connection();
	void reset_timer();
	bool is_connected();
};
