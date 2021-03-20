// Copyright (c) 2021 Inaba

#include "displaytask.h"
#include "taskid.h"

DisplayTask::DisplayTask(MailboxPool* mailbox,
                         LED_Display* display, int ledCount)
: TaskBase(TID_DISPLAY, mailbox, 10, sizeof(bool)),
display_(display), ledCount_(ledCount) {
}

namespace {
void show(LED_Display* display, int count, CRGB color) {
  for (int i = 0; i < count; ++i) {
    display->drawpix(i, color);
  }
}
}  // namespace

void DisplayTask::Initialize() {
  show(display_, ledCount_, 0);
}

bool DisplayTask::Loop() {
  bool mes;
  if (ReceiveMessage(&mes, 0)) {
    show(display_, ledCount_, mes ? 0xffffff : 0);
  }
  return true;
}
