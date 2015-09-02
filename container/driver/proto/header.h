// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTAINER_DRIVER_PROTO_INPUT_HEADER_H__
#define CONTAINER_DRIVER_PROTO_INPUT_HEADER_H__

#include "base/basictypes.h"

namespace container {

enum class RequestCode {
 REQ_NOP         = 000,

 REQ_ACK         = 001, // hello handshake
                   // introduce yourself (with public key)
 // P2P NEGOTIATION
 REQ_GETMANIFEST = 004,

 // CONTAINER 
 REQ_CREATE = 100, // create a new container
 REQ_DROP = 101, // drop a container
 REQ_CLONE = 102, // clone a container from a given remote peer
 REQ_MOUNT = 103,
 REQ_UMOUNT = 104,
 REQ_PUSH = 105, // push a container to a remote peer
 REQ_PULL = 106, // pull the container from a remote peer
 REQ_CATALOG = 107, // list containers

 REQ_STATUS = 202,
 REQ_START = 204,
 REQ_STOP = 205,
 REQ_PAUSE = 206, // ??
 REQ_SHUTDOWN = 207,
 REQ_RUN = 208, // run process
 REQ_KILL = 209, // kill process
 REQ_QUERY = 210, // perform a read ro write query, return cursor
};

enum class ResponseCode {
 RESP_NOP        = 000,
 RESP_HELLOACK = 001, // answer to a hello
 RESP_HEADERACK = 002, // answer to a hello
 RESP_GOODBYE = 003, // if the host was rejected, after a hello
 RESP_CONNECTED = 004, // sent after a sucessfull ENTER signal has ben sent
 // errors
 RESP_REJECTED = 100,
 RESP_BAD = 101,
 RESP_FORBIDDEN = 102,
 RESP_NOMEM = 103,
};

class Header {
public:
 const uint8_t* signature() const { return signature_; }
 const uint8_t* proto_version() const { return proto_version_; }
private:
 uint8_t signature_[4]; // "pkt1"
 uint8_t proto_version_[4]; // 0103
};

class RequestHeader : public Header {
public:
 RequestCode input_code() const { return input_code_; }

private:

 RequestCode input_code_;
};

class ResponseHeader : public Header {
public:
 
 ResponseCode output_code() const { return output_code_; }

private:

 ResponseCode output_code_;
};

}

#endif