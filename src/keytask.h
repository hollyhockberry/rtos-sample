// Copyright (c) 2021 Inaba

#ifndef KEYTASK_H_
#define KEYTASK_H_

#include "taskbase.h"
#include "utility/Button.h"

class KeyTask : public TaskBase {
 public:
  KeyTask(MailboxPool* mailbox, Button* button);

 protected:
  Button* button_;

  void Initialize() override;
  bool Loop() override;
};

#endif  // KEYTASK_H_
