#ifndef __CONFIG_SETTINGS_H__
#define __CONFIG_SETTINGS_H__
#include <string>

class config_settings
{
public:
	static config_settings& instance();
	void load(const std::string &filename);
	void print();
	uint32_t get_local_port();
	std::string get_remote_ip();
	uint32_t get_remote_port();
	std::string get_log_filename();
private:
	config_settings();
	std::string m_log_filename;
	std::string m_local_ip;
	uint32_t m_local_port = 0;
	std::string m_remote_ip;
	uint32_t m_remote_port = 0;
	
};

#endif