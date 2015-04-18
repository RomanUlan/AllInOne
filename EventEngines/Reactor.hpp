#ifndef REACTOR_HPP
#define REACTOR_HPP

#include "EventHandler.hpp"
#include "EventDemultiplexer.hpp"

#include <map>
#include <boost/thread/mutex.hpp>

class Reactor
{
public:
  typedef boost::shared_ptr<Reactor> Ptr;

public:
  explicit Reactor(EventDemultiplexer::Ptr);
  ~Reactor();

  void add(EventHandler::Ptr);
  void remove(EventSource::Descriptor);
  void eventLoop();

private:
  Reactor(const Reactor&);
  Reactor& operator=(const Reactor&);

private:
  typedef std::map<EventSource::Descriptor, EventHandler::Ptr> t_handlers;
  typedef std::pair<EventHandler::Ptr, EventSource::EventTypes> t_toHandle;
  typedef std::vector<t_toHandle> t_toHandles;

  boost::mutex m_mutex;
  t_handlers m_handlers;
  EventDemultiplexer::Ptr m_eventDemultiplexer;
};

#endif
