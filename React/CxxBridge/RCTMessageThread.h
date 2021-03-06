/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <string>

#import <Foundation/Foundation.h>

#import <React/RCTJavaScriptExecutor.h>
#import <cxxreact/MessageQueueThread.h>

namespace facebook {
namespace react {

class RCTMessageThread : public MessageQueueThread {
 public:
  RCTMessageThread(NSRunLoop *runLoop, RCTJavaScriptCompleteBlock errorBlock);
  ~RCTMessageThread() override;
  void runOnQueue(std::function<void()>&&) override;
  void runOnQueueSync(std::function<void()>&&) override;
  void quitSynchronous() override;

 private:
  void tryFunc(const std::function<void()>& func);
  void runAsync(std::function<void()> func);
  void runSync(std::function<void()> func);

  CFRunLoopRef m_cfRunLoop;
  RCTJavaScriptCompleteBlock m_errorBlock;
  std::atomic_bool m_shutdown;
};

}
}
