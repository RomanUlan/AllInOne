#ifndef KEYBOARD_EH_HPP
#define KEYBOARD_EH_HPP

#include "EventEngines/ThreadPool.hpp"
#include "KeyboardES.hpp"
#include <fstream>

class KeyboardReactorEH : public EventHandler
{
public:
  KeyboardReactorEH(const std::string&, KeyboardES::Ptr);
  virtual ~KeyboardReactorEH();

public:
  virtual void handle(const EventSource::EventTypes&);

private:
  std::ofstream m_file;
};

#endif
