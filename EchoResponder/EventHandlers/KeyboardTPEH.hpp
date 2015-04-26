#ifndef KEYBOARDTP_EH_HPP
#define KEYBOARDTP_EH_HPP

#include "EventEngines/ThreadPool.hpp"
#include "KeyboardES.hpp"
#include <fstream>

class KeyboardTPEH : public EventHandler
{
public:
  KeyboardTPEH(const std::string&, KeyboardES::Ptr, EventEngines::ThreadPool&);
  virtual ~KeyboardTPEH();

public:
  virtual void handle(const EventSource::EventTypes&);

private:
  std::ofstream m_file;
  EventEngines::ThreadPool& m_threadPool;
};

#endif
