#include <iostream>
#include <stdexcept>
#include "ConfigParser.hpp"
#include "EventEngineFactory.hpp"

int main(int argc, char** argv)
{
  try
  {
    ConfigParser cp(argc, argv);
    Config c = cp.get();
    EventEngine::Ptr ee = EventEngineFactory::create(c);
    if (ee) {
      ee->start();
      std::string s;
      while (s != "exit") {
        std::cout << "Type \'exit\' to quit" << std::endl;
        ee->stop(true);
        std::cin >> s;
      }
    }
  }
  catch (const std::runtime_error& rte)
  {
    std::cout << "Runtime exception: " << rte.what() << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "STD exception: " << e.what() << std::endl;
  }

  return 0;
}
