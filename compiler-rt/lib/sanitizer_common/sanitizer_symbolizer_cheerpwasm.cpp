#include "sanitizer_platform.h"

#if SANITIZER_CHEERPWASM
#  include "sanitizer_symbolizer_internal.h"

namespace __sanitizer {

const char *GetFunctionNameAtPc(uptr pc);

class CheerpSymbolizerTool : public SymbolizerTool {
 public:
  bool SymbolizePC(uptr addr, SymbolizedStack *frame) override {
    const char *func_name = GetFunctionNameAtPc(addr);
    if (!func_name)
      func_name = "<unknown function>";

    frame->info.function = internal_strdup(func_name);

    if (0x80000000 & addr) {
      frame->info.file = internal_strdup("main");
      frame->info.line = 0x80000000 ^ addr;
      frame->info.column = 0;
    }
    return true;
  }

  bool SymbolizeData(uptr addr, DataInfo *info) override { return false; }

  const char *Demangle(const char *name) override { return name; }
};

static void ChooseSymbolizerTools(IntrusiveList<SymbolizerTool> *list,
                                  LowLevelAllocator *allocator) {
  if (!common_flags()->symbolize) {
    VReport(2, "Symbolizer is disabled.\n");
    return;
  }

  list->push_back(new (*allocator) CheerpSymbolizerTool());
}

const char *Symbolizer::PlatformDemangle(const char *name) { return name; }

Symbolizer *Symbolizer::PlatformInit() {
  IntrusiveList<SymbolizerTool> list;
  list.clear();
  ChooseSymbolizerTools(&list, &symbolizer_allocator_);

  return new (symbolizer_allocator_) Symbolizer(list);
}

void Symbolizer::LateInitialize() { Symbolizer::GetOrInit(); }

}  // namespace __sanitizer
#endif  // SANITIZER_CHEERPWASM
