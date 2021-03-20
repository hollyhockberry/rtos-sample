// Copyright (c) 2021 Inaba

#include "displaytask.h"
#include "taskid.h"

DisplayTask::DisplayTask(MailboxPool* mailbox,
                         LED_Display* display, int ledCount)
: TaskBase(TID_DISPLAY, mailbox, 10, sizeof(bool)),
display_(display), ledCount_(ledCount), show_(false) {
}

namespace {
void show(LED_Display* display, int count, CRGB color) {
  for (int i = 0; i < count; ++i) {
    display->drawpix(i, color);
  }
}
}  // namespace

void DisplayTask::Initialize() {
  show_ = false;
  show(display_, ledCount_, 0);
}

bool DisplayTask::Delay(int milliseconds) {
  if (!ReceiveMessage(&show_, milliseconds)) {
    return false;
  }
  return true;
}

bool DisplayTask::Loop() {
  if (!show_) {
    show(display_, ledCount_, 0);
    Delay(20);
  } else {
    for (int h = 0; h < 255; ++h) {
      for (int i = 0; i < ledCount_; ++i) {
        display_->drawpix(i, CRGB(CHSV((h + i) % 255, 255,255)));
      }
      if (Delay(20)) return true;
    }
  }

  return true;
}
