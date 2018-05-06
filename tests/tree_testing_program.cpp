#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "tree_tests.hpp"

int main(int argc, char* argv[]) {
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(suite);
  runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
  return runner.run() ? 0 : 1;
}
