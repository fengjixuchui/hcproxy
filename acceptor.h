// Copyright 2018 Roman Perepelitsa
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROMKATV_HCPROXY_ACCEPTOR_H_
#define ROMKATV_HCPROXY_ACCEPTOR_H_

#include <stddef.h>
#include <cstdint>
#include <string>

namespace hcproxy {

class Acceptor {
 public:
  struct Options {
    // Listen for incoming connections on this address.
    std::string listen_addr = "0.0.0.0";
    // Listen for incoming connections on this port.
    std::uint16_t listen_port = 8889;
    // Queue up to this many incoming, not yet accepted, connections.
    // Any extra incoming connections will get rejected.
    size_t accept_queue_size = 64;
  };

  explicit Acceptor(const Options& opt);
  Acceptor(Acceptor&&) = delete;
  ~Acceptor();

  // Blocks until there is an incoming connection and returns it.
  // The result is always a valid socket file description. Must not
  // be called concurrently.
  int Accept();

 private:
  int fd_;
};

}  // namespace hcproxy

#endif  // ROMKATV_HCPROXY_ACCEPTOR_H_
