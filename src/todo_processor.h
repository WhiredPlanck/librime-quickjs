#include <rime/common.h>
#include <rime/context.h>
#include <rime/engine.h>
#include <rime/processor.h>

using namespace rime;

class TodoProcessor : public Processor {
 public:
  explicit TodoProcessor(const Ticket& ticket)
    : Processor(ticket) {
    Context* context = engine_->context();
    update_connection_ = context->update_notifier()
      .connect([this](Context* ctx) { OnUpdate(ctx); });
  }

  virtual ~TodoProcessor() {
    update_connection_.disconnect();
  }

  ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override {
    return kNoop;
  }

 private:
  void OnUpdate(Context* ctx) {}

  connection update_connection_;
};
