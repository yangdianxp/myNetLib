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
	init();
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
	m_mid_begin = tree.get("conf.mid_range.begin", 1);
	m_mid_end = tree.get("conf.mid_range.end", 1);
	m_type = convert_type(type);

	BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("conf.link_type.gateway"))
	{
		m_gateway_link_type.push_back(convert_type(v.second.data()));
	}

	

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
		<< "m_remote_port:" << m_remote_port << std::endl
		<< "m_type:" << m_type << " " << get_module_name(m_type) << std::endl
		<< "m_mid_begin:" << m_mid_begin << " " << "m_mid_end:" << m_mid_end;
	auto it_end = m_gateway_link_type.end();
	for (auto it = m_gateway_link_type.begin(); it != it_end; ++it)
	{
		SLOG_INFO << "gateway link type:" << *it;
	}
}

void config_settings::init()
{
	m_type_glossary.left.insert(std::make_pair("none", module_none_type));
	m_type_glossary.left.insert(std::make_pair("gateway", module_gateway_type));
	m_type_glossary.left.insert(std::make_pair("login", module_login_type));
	m_type_glossary.left.insert(std::make_pair("central", module_central_type));
	m_type_glossary.left.insert(std::make_pair("media", module_media_type));
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

uint32_t config_settings::get_mid_begin()
{
	return m_mid_begin;
}

uint32_t config_settings::get_mid_end()
{
	return m_mid_end;
}

std::string config_settings::get_module_name(uint32_t type)
{
	try
	{
		return m_type_glossary.right.at(type);
	}
	catch (std::exception& e)
	{
		SLOG_ERROR << "Exception: " << e.what();
	}
	return std::string();
}

uint32_t config_settings::convert_type(std::string& str_type)
{
	try
	{
		return m_type_glossary.left.at(str_type);
	}
	catch (std::exception& e)
	{
		SLOG_ERROR << "Exception: " << e.what();
	}
	return module_none_type;
}