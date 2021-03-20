// Copyright (c) 2021 Inaba

#ifndef DISPLAYTASK_H_
#define DISPLAYTASK_H_

#include "taskbase.h"
#include "utility/LED_Display.h"

class DisplayTask : public TaskBase {
 public:
  DisplayTask(MailboxPool* mailbox, LED_Display* display, int ledCount);

 protected:
  LED_Display* display_;
  const int ledCount_;
  bool show_;
  void Initialize() override;
  bool Loop() override;
 
 private:
  bool Delay(int milliseconds);
};

#endif  // DISPLAYTASK_H_
