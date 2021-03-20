// Copyright (c) 2021 Inaba

#include "mailboxpool.h"

MailboxPool::MailboxPool() : handlers_() {
}

QueueHandle_t MailboxPool::Create(int id, int length, int size) {
  if (id < 0 || length <= 0 || size <= 0) return nullptr;
  if (handlers_.count(id) != 0) return nullptr;

  handlers_[id] = ::xQueueCreate(length, size);
  return handlers_[id];
}

QueueHandle_t MailboxPool::Find(int id) {
  return (handlers_.count(id) != 0) ? handlers_[id] : nullptr;
}
