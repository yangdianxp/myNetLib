#ifndef __CONFIG_SETTINGS_H__
#define __CONFIG_SETTINGS_H__
#include <string>

class config_settings
{
public:
	static config_settings& instance();
	void load(const std::string &filename);
	void print();
	std::string get_local_ip();
	uint32_t get_local_port();
	std::string get_remote_ip();
	uint32_t get_remote_port();
	std::string get_log_filename();
	uint32_t get_type();
private:
	config_settings();
	uint32_t convert_type(std::string& str_type);

	std::string m_log_filename;
	std::string m_local_ip;
	uint32_t m_local_port = 0;
	std::string m_remote_ip;
	uint32_t m_remote_port = 0;
	uint32_t m_type = 0;
	
};

#endif