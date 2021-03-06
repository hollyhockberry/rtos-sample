// Copyright (c) 2021 Inaba

#ifndef DISPLAYTASK_H_
#define DISPLAYTASK_H_

#include "taskbase.h"
#include "utility/LED_Display.h"

class DisplayTask : public TaskBase {
 public:
  DisplayTask(MailboxPool* mailbox, LED_Display* display, int ledCount);

 protected:
  void Initialize() override;
  bool Loop() override;

 private:
  LED_Display* display_;
  const int ledCount_;
  bool show_;
  int h_, v_;

  bool Delay(int milliseconds);
  void Transition(bool off, int delta = 5);
};

#endif  // DISPLAYTASK_H_
