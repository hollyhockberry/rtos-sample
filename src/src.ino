// Sample sketch of task communication in FreeRTOS
// Copyright (c) 2021 Inaba

#include <M5Atom.h>
#include "keytask.h"
#include "displaytask.h"

namespace {
MailboxPool mailboxpool;
TaskBase::TaskInfo tasks[] = {
  { new KeyTask(&mailboxpool, &M5.Btn), 1024, 10, 1 },
  { new DisplayTask(&mailboxpool, &M5.dis, 25), 1024, 10, 1, },
};
}  // namespace

void setup() {
  M5.begin(true, true, true);

  // kick tasks
  for (const auto& t : tasks) {
    TaskBase::Create(t);
  }
}

void loop() {
  M5.update();
  ::delay(1);
}
