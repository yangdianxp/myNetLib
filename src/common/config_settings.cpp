#include <set>
#include <exception>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include"common.h"
namespace pt = boost::property_tree;

config_settings& config_settings::instance()
{
	static config_settings instance;
	return instance;
}

config_settings::config_settings()
{

}

void config_settings::load(const std::string &filename)
{
	// Create empty property tree object
	pt::ptree tree;

	// Parse the XML into the property tree.
	pt::read_xml(filename, tree);

	// Use the throwing version of get to find the debug filename.
	// If the path cannot be resolved, an exception is thrown.
	m_log_filename = tree.get<std::string>("conf.log_filename", "common.log");
	m_local_ip = tree.get("conf.local_ip", "127.0.0.1");
	m_local_port = tree.get("conf.local_port", 0);
	m_remote_ip = tree.get("conf.remote_ip", "127.0.0.1");
	m_remote_port = tree.get("conf.remote_port", 0);
	std::string type = tree.get("conf.type", "none");
	m_type = convert_type(type);

	// Use the default-value version of get to find the debug level.
	// Note that the default value is used to deduce the target type.
	//m_level = tree.get("debug.level", 0);

	// Use get_child to find the node containing the modules, and iterate over
	// its children. If the path cannot be resolved, get_child throws.
	// A C++11 for-range loop would also work.
	//BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("debug.modules")) {
		// The data function is used to access the data stored in a node.
	//	m_modules.insert(v.second.data());
	//}
}

void config_settings::print()
{
	SLOG_INFO << "m_log_filename:" << m_log_filename << std::endl
		<< "m_local_ip:" << m_local_ip << std::endl
		<< "m_local_port:" << m_local_port << std::endl
		<< "m_remote_ip:" << m_remote_ip << std::endl
		<< "m_remote_port:" << m_remote_port;
}

std::string config_settings::get_local_ip()
{
	return m_local_ip;
}

uint32_t config_settings::get_local_port()
{
	return m_local_port;
}

std::string config_settings::get_remote_ip()
{
	return m_remote_ip;
}

uint32_t config_settings::get_remote_port()
{
	return m_remote_port;
}

std::string config_settings::get_log_filename()
{
	return m_log_filename;
}

uint32_t config_settings::get_type()
{
	return m_type;
}

uint32_t config_settings::convert_type(std::string& str_type)
{
	static std::map<std::string, uint32_t> type_glossary = {
		{"none", module_none_type},	{"gateway", module_gateway_type}, {"login", module_login_type},
		{"central", module_central_type}, {"media", module_media_type}
	};
	return type_glossary[str_type];
}