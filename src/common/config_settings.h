#ifndef __CONFIG_SETTINGS_H__
#define __CONFIG_SETTINGS_H__
#include <string>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

class config_settings
{
public:
	static config_settings& instance();
	void load(const std::string &filename);
	void print();
	void init();
	std::string get_local_ip();
	uint32_t get_local_port();
	std::string get_remote_ip();
	uint32_t get_remote_port();
	std::string get_log_filename();
	uint32_t get_type();

	std::string get_module_name(uint32_t type);
private:
	config_settings();
	uint32_t convert_type(std::string& str_type);

	std::string m_log_filename;
	std::string m_local_ip;
	uint32_t m_local_port = 0;
	std::string m_remote_ip;
	uint32_t m_remote_port = 0;
	uint32_t m_type = 0;

	boost::bimaps::bimap<boost::bimaps::unordered_set_of<std::string>, boost::bimaps::unordered_set_of<uint32_t>> m_type_glossary;
	
};

#endif