#include "sanitizer_platform.h"

#if SANITIZER_CHEERPWASM
#include "sanitizer_symbolizer_internal.h"

namespace __sanitizer {

class CheerpSymbolizerTool : public SymbolizerTool {
 public:
  bool SymbolizePC(uptr addr, SymbolizedStack *frame) override {
    if (0x80000000 & addr) {
      frame->info.function = internal_strdup("<javascript function>");
      frame->info.function_offset = 0x80000000 ^ addr;
    } else {
      frame->info.function = internal_strdup("<wasm function>");
      frame->info.function_offset = addr;
    }
    return true;
  }

  bool SymbolizeData(uptr addr, DataInfo *info) override {
    return false;
  }
  const char *Demangle(const char *name) override {
    return name;
  }
};

static void ChooseSymbolizerTools(IntrusiveList<SymbolizerTool> *list,
                                  LowLevelAllocator *allocator) {
  if (!common_flags()->symbolize) {
    VReport(2, "Symbolizer is disabled.\n");
    return;
  }

  list->push_back(new(*allocator) CheerpSymbolizerTool());
}

const char *Symbolizer::PlatformDemangle(const char *name) {
  return name;
}

Symbolizer *Symbolizer::PlatformInit() {
  IntrusiveList<SymbolizerTool> list;
  list.clear();
  ChooseSymbolizerTools(&list, &symbolizer_allocator_);

  return new(symbolizer_allocator_) Symbolizer(list);
}

void Symbolizer::LateInitialize() {
  Symbolizer::GetOrInit();
}

} // namespace __sanitizer
#endif // SANITIZER_CHEERPWASM
