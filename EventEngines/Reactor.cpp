#include "Reactor.hpp"
#include <stdexcept>

Reactor::Reactor(EventDemultiplexer::Ptr p_eventDemultiplexer)
  : m_eventDemultiplexer(p_eventDemultiplexer)
{
}

Reactor::~Reactor()
{
}

void Reactor::add(EventHandler::Ptr p_eventHandler)
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_eventDemultiplexer->add(p_eventHandler->getEventSource());
  m_handlers.insert(std::make_pair(p_eventHandler->getEventSource()->getDescriptor(), p_eventHandler));
}

void Reactor::remove(EventSource::Descriptor p_descriptor)
{
  boost::mutex::scoped_lock lock(m_mutex);
  t_handlers::iterator i = m_handlers.find(p_descriptor);
  if (i != m_handlers.end())
  {
    m_handlers.erase(i);
    m_eventDemultiplexer->remove(p_descriptor);
  }
}

void Reactor::eventLoop()
{
  while (1)
  {
    EventDemultiplexer::Events events;
    m_eventDemultiplexer->wait(events);

    t_toHandles toHandles;
    {//scope of m_mutex lock begin
      boost::mutex::scoped_lock lock(m_mutex);
      for (EventDemultiplexer::Events::iterator i = events.begin(); i < events.end(); ++i)
      {
        t_handlers::const_iterator ih = m_handlers.find(i->descriptor);
        if (ih != m_handlers.end())
        {
          toHandles.push_back(t_toHandle(ih->second, i->eventTypes));
        }
        else
        {
          throw std::runtime_error("EventDemultiplexer returned event for \
                                      unfounded handler");
        }
      }
    }//scope of m_mutex lock end

    for (t_toHandles::iterator i = toHandles.begin(); i != toHandles.end(); ++i)
    {
      i->first->handle(i->second);
    }
  } //while (1)
}
