// Copyright (c) 2021 Inaba

#ifndef TASKBASE_H_
#define TASKBASE_H_

#include "mailboxpool.h"

class TaskBase {
 public:
  void Run();

  struct TaskInfo {
    TaskBase* task;
    int stackDepth;
    int priority;
    int core;
  };
  static void Create(const TaskInfo& info);

 protected:
  TaskBase(int id, MailboxPool* mailbox, int mailLength, int mailSize);
  TaskBase(int id, MailboxPool* mailbox);

  bool SendMessage(int id, const void* parameter, int tickToWait);
  bool ReceiveMessage(void* parameter, int tickToWait);

  virtual void Initialize() = 0;
  virtual bool Loop() = 0;

 private:
  const int id_;
  MailboxPool* mailbox_;
  const int mailLength_, mailSize_;
  void CreateMailbox() const;

  TaskBase(const TaskBase&);
  void operator=(const TaskBase&);
};

#endif  // TASKBASE_H_
