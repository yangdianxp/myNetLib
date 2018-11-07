#ifndef __BALANCE_ROUTE_H__
#define __BALANCE_ROUTE_H__
#include <map>
#include "route.h"

class balance_route : public route
{
	using m_size_t = std::map<std::shared_ptr<common_client>, std::size_t>;
public:
	virtual void add_module(std::shared_ptr<common_client> client, uint32_t type, uint32_t mid);
	virtual void delete_client(std::shared_ptr<common_client> client);
	virtual void delete_module(std::shared_ptr<common_client> client);

	std::shared_ptr<common_client> get_first_media(std::size_t type);
	std::size_t for_each_ref(std::function<void(std::shared_ptr<common_client> client, const std::size_t)>);
private:
	/*media模块上通道数记录*/
	m_size_t m_ref;
};

#endif
