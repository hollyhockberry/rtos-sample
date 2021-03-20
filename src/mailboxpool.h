// Copyright (c) 2021 Inaba

#ifndef MAILBOXPOOL_H_
#define MAILBOXPOOL_H_

#include <map>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

class MailboxPool {
 public:
  MailboxPool();

  QueueHandle_t Create(int id, int length, int size);
  QueueHandle_t Find(int id);

 private:
  std::map<int, QueueHandle_t> handlers_;
  MailboxPool(const MailboxPool&);
  void operator=(const MailboxPool&);
};

#endif  // MAILBOXPOOL_H_
