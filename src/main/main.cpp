#include <win.hpp>

int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3848);
#endif


 shared::Win::MainProcess(
  [&](const std::string& input, bool& exit) {

   if (input == "q") {
    exit = true;
   }

  });

 return 0;
}