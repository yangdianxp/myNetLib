#ifndef __CONFIG_SETTINGS_H__
#define __CONFIG_SETTINGS_H__
#include <string>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/set_of.hpp>

using boost::bimaps::bimap;
using boost::bimaps::set_of;

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
	uint32_t get_mid_begin();
	uint32_t get_mid_end();
	std::vector<uint32_t> get_gateway_link_type();

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
	uint32_t m_mid_begin = 0;
	uint32_t m_mid_end = 0;
	/*gateway连接的模块类型*/
	std::vector<uint32_t> m_gateway_link_type;

	bimap<set_of<std::string>, set_of<uint32_t>> m_type_glossary;
	
};

#endif