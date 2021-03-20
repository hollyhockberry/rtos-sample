// Copyright (c) 2021 Inaba

#include "displaytask.h"
#include "taskid.h"

DisplayTask::DisplayTask(MailboxPool* mailbox,
                         LED_Display* display, int ledCount)
: TaskBase(TID_DISPLAY, mailbox, 10, sizeof(bool)),
display_(display), ledCount_(ledCount), show_(false), h_(0), v_(0) {
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
  h_ = v_ = 0;

  for (int i = 0; i < ledCount_; ++i) {
    display_->drawpix(i, 0);
  }
}

bool DisplayTask::Delay(int milliseconds) {
  bool message;
  int now = ::millis();
  if (!ReceiveMessage(&message, milliseconds)) {
    return false;
  }
  if (show_ == message) {
    int rest = ::millis() - now - milliseconds;
    return (rest > 0) ? Delay(rest) : false;
  }
  show_ = message;
  if (v_ < 0) v_ = 0;
  if (v_ > 255) v_ = 255;
  return true;
}

bool DisplayTask::Loop() {
  if (show_) {
    Transition(false);
  } else if (v_ > 0) {
    Transition(true);
  } else {
    Delay(0);
  }
  return true;
}

void DisplayTask::Transition(bool off, int delta) {
  for (; h_ < 255; ++h_) {
    for (int i = 0; i < ledCount_; ++i) {
      display_->drawpix(i, CRGB(CHSV((h_ + i) % 255, 255, v_)));
    }
    if (Delay(20)) return;
    if (off) {
      v_ -= delta;
      if (v_ < 0) return;
    } else {
      if (v_ < 255) v_ += delta;
    }
  }
  h_ = 0;
}
