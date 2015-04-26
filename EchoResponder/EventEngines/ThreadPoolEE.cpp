#include "ThreadPoolEE.hpp"

ThreadPoolEE::ThreadPoolEE(EventEngines::ThreadPool::Ptr p_threadPool)
  : m_threadPool(p_threadPool)
{
}

ThreadPoolEE::~ThreadPoolEE()
{
}

void ThreadPoolEE::start()
{
  m_thread.reset(new std::thread(std::bind(&EventEngines::ThreadPool::eventLoop, m_threadPool.get())));
}

void ThreadPoolEE::stop(bool p_immediately)
{
  m_threadPool->interrupt(p_immediately);
  m_thread->join();
  m_thread.reset();
}
