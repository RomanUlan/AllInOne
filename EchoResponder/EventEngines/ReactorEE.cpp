#include "ReactorEE.hpp"

ReactorEE::ReactorEE(EventEngines::Reactor::Ptr p_reactor)
  : m_reactor(p_reactor)
{
}

ReactorEE::~ReactorEE()
{
}

void ReactorEE::start()
{
  m_thread.reset(new std::thread(std::bind(&EventEngines::Reactor::eventLoop, m_reactor.get())));
}

void ReactorEE::stop(bool p_immediately)
{
  m_reactor->interrupt(p_immediately);
  m_thread->join();
  m_thread.reset();
}
