// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is used to define IPC::ParamTraits<> specializations for a number
// of types so that they can be serialized over IPC.  IPC::ParamTraits<>
// specializations for basic types (like int and std::string) and types in the
// 'base' project can be found in ipc/ipc_message_utils.h.  This file contains
// specializations for types that are used by the content code, and which need
// manual serialization code.  This is usually because they're not structs with
// public members, or because the same type is being used in multiple
// *_messages.h headers.

#ifndef COMMON_COMMON_PARAM_TRAITS_H_
#define COMMON_COMMON_PARAM_TRAITS_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "common/common_param_traits_macros.h"
//#include "common/cursors/webcursor.h"
#include "ipc/ipc_message_utils.h"
//#include "ui/gfx/native_widget_types.h"
//#include "ui/surface/transport_dib.h"
#include "url/gurl.h"
#include "url/origin.h"
//#include "third_party/WebKit/public/web/WebInputEvent.h"

//namespace common {
//class PageState;
//}

namespace net {
class HostPortPair;
class IPEndPoint;
}

namespace IPC {

template <>
struct ParamTraits<GURL> {
  typedef GURL param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, base::PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<url::Origin> {
  typedef url::Origin param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, base::PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template<>
struct ParamTraits<net::HostPortPair> {
  typedef net::HostPortPair param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, base::PickleIterator* iter, param_type* r);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<net::IPEndPoint> {
  typedef net::IPEndPoint param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, base::PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

//template <>
//struct ParamTraits<common::PageState> {
// typedef common::PageState param_type;
//  static void Write(Message* m, const param_type& p);
//  static bool Read(const Message* m, base::PickleIterator* iter, param_type* p);
//  static void Log(const param_type& p, std::string* l);
//};

//template <>
//struct ParamTraits<common::WebCursor> {
// typedef common::WebCursor param_type;
// static void Write(Message* m, const param_type& p) {
//  p.Serialize(m);
// }
// static bool Read(const Message* m, base::PickleIterator* iter, param_type* r)  {
//  return r->Deserialize(iter);
// }
// static void Log(const param_type& p, std::string* l) {
//  l->append("<WebCursor>");
// }
//};
//
//typedef const blink::WebInputEvent* WebInputEventPointer;
//template <>
//struct ParamTraits<WebInputEventPointer> {
// typedef WebInputEventPointer param_type;
// static void Write(Message* m, const param_type& p);
// // Note: upon read, the event has the lifetime of the message.
// static bool Read(const Message* m, base::PickleIterator* iter, param_type* r);
// static void Log(const param_type& p, std::string* l);
//};
//
//template <>
//struct ParamTraits<gfx::NativeWindow> {
//  typedef gfx::NativeWindow param_type;
//  static void Write(Message* m, const param_type& p) {
//#if defined(OS_WIN)
//    // HWNDs are always 32 bits on Windows, even on 64 bit systems.
//    m->WriteUInt32(reinterpret_cast<uint32>(p));
//#else
//    m->WriteData(reinterpret_cast<const char*>(&p), sizeof(p));
//#endif
//  }
//  static bool Read(const Message* m, base::PickleIterator* iter, param_type* r) {
//#if defined(OS_WIN)
//    return iter->ReadUInt32(reinterpret_cast<uint32*>(r));
//#else
//    const char *data;
//    int data_size = 0;
//    bool result = iter->ReadData(&data, &data_size);
//    if (result && data_size == sizeof(gfx::NativeWindow)) {
//      memcpy(r, data, sizeof(gfx::NativeWindow));
//    } else {
//      result = false;
//      NOTREACHED();
//    }
//    return result;
//#endif
//  }
//  static void Log(const param_type& p, std::string* l) {
//    l->append("<gfx::NativeWindow>");
//  }
//};
//
//template <>
//struct SimilarTypeTraits<ui::PageTransition> {
// typedef int Type;
//};
//
//template <>
//struct SimilarTypeTraits<WindowOpenDisposition> {
// typedef int Type;
//};

template <>
struct SimilarTypeTraits<net::RequestPriority> {
 typedef int Type;
};

//template <>
//struct SimilarTypeTraits<common::ResourceType> {
// typedef int Type;
//};

//template <>
//struct SimilarTypeTraits<blink::WebReferrerPolicy> {
// typedef int Type;
//};

template <>
struct SimilarTypeTraits<net::NetworkChangeNotifier::ConnectionType> {
 typedef int Type;
};


//template <>
//struct SimilarTypeTraits<blink::WebContentSecurityPolicyType> {
// typedef int Type;
//};
//
//template <>
//struct SimilarTypeTraits<blink::WebInputEvent::Type> {
// typedef int Type;
//};

//template <>
//struct SimilarTypeTraits<blink::WebPageVisibilityState> {
// typedef int Type;
//};
//
//template <>
//struct SimilarTypeTraits<common::RequestContextType> {
// typedef int Type;
//};
//
//template <>
//struct SimilarTypeTraits<common::RequestContextFrameType> {
// typedef int Type;
//};
//
//template <>
//struct SimilarTypeTraits<common::SecurityStyle> {
// typedef int Type;
//};

/*template <>
struct SimilarTypeTraits<net::ct::SCTVerifyStatus> {
 typedef int Type;
};*/

//#if defined(OS_WIN)
//template<>
//struct ParamTraits<TransportDIB::Handle> {
// typedef TransportDIB::Handle param_type;
//  static void Write(Message* m, const param_type& p) {
//    WriteParam(m, p.handle);
//    WriteParam(m, p.sequence_num);
//  }
//  static bool Read(const Message* m, base::PickleIterator* iter, param_type* r) {
//    return (ReadParam(m, iter, &r->handle) &&
//            ReadParam(m, iter, &r->sequence_num));
//  }
//  static void Log(const param_type& p, std::string* l) {
//    l->append("TransportDIB(");
//    LogParam(p.handle, l);
//    l->append(", ");
//    LogParam(p.sequence_num, l);
//    l->append(")");
//  }
//};
//#endif

}  // namespace IPC

#endif  // STRIPES_MODULES_COMMON_COMMON_PARAM_TRAITS_H_
