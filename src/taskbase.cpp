// Copyright (c) 2021 Inaba

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "taskbase.h"

TaskBase::TaskBase(int id, MailboxPool* mailbox)
: id_(id), mailbox_(mailbox), mailLength_(0), mailSize_(0) {
}

TaskBase::TaskBase(int id, MailboxPool* mailbox, int mailLength, int mailSize)
: id_(id), mailbox_(mailbox), mailLength_(mailLength), mailSize_(mailSize) {
}

void TaskBase::Run() {
  Initialize();

  while (Loop()) {
    ::vTaskDelay(1);
  }

  ::vTaskDelete(NULL);
}

namespace {
void run(void* param) {
  static_cast<TaskBase*>(param)->Run();
}
}  // namespace

void TaskBase::CreateMailbox() const {
  if (mailbox_ != nullptr) {
    mailbox_->Create(id_, mailLength_, mailSize_);
  }
}

void TaskBase::Create(const TaskInfo& info) {
  info.task->CreateMailbox();

  ::xTaskCreatePinnedToCore(
    run, "",
    info.stackDepth, info.task, info.priority, nullptr, info.core);
}

bool TaskBase::SendMessage(int id, const void* parameter, int tickToWait) {
  QueueHandle_t q = mailbox_->Find(id);
  if (q == nullptr) return false;
  return ::xQueueSend(q, parameter, tickToWait) == pdPASS;
}

bool TaskBase::ReceiveMessage(void* parameter, int tickToWait) {
  QueueHandle_t q = mailbox_->Find(id_);
  if (q == nullptr) return false;
  return ::xQueueReceive(q, parameter, tickToWait) == pdPASS;
}
