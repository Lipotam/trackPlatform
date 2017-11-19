#pragma once

class ErrorManager
{
	static ErrorManager manager;

	ErrorManager();
	ErrorManager(ErrorManager &);
	~ErrorManager();

	bool is_error_now = false;

public:
	void set_error();
	void reset_error();
	bool is_error_gotten() const;
};
