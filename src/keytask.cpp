// Copyright (c) 2021 Inaba

#include "keytask.h"
#include "taskid.h"

KeyTask::KeyTask(MailboxPool* mailbox, Button* button)
: TaskBase(TID_KEY, mailbox), button_(button) {
}

void KeyTask::Initialize() {
}

bool KeyTask::Loop() {
  if (button_->wasPressed()) {
    bool message = true;
    SendMessage(TID_DISPLAY, &message, 0);
  }
  if (button_->wasReleased()) {
    bool message = false;
    SendMessage(TID_DISPLAY, &message, 0);
  }
  return true;
}
