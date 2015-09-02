// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/common_param_traits.h"

#include <string>

#include "common/constants.h"
//#include "common/page_state.h"
//#include "common/referrer.h"
//#include "common/url_utils.h"
//#include "common/input/web_input_event_traits.h"
#include "net/base/host_port_pair.h"
#include "net/base/ip_endpoint.h"
//#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
//#include "third_party/WebKit/public/web/WebFindOptions.h"
//#include "third_party/WebKit/public/web/WebMediaPlayerAction.h"

namespace IPC {

//void ParamTraits<GURL>::Write(Message* m, const GURL& p) {
//  DCHECK(p.possibly_invalid_spec().length() <= common::GetMaxURLChars());
//
//  // Beware of print-parse inconsistency which would change an invalid
//  // URL into a valid one. Ideally, the message would contain this flag
//  // so that the read side could make the check, but performing it here
//  // avoids changing the on-the-wire representation of such a fundamental
//  // type as GURL. See https://crbug.com/166486 for additional work in
//  // this area.
//  if (!p.is_valid()) {
//    m->WriteString(std::string());
//    return;
//  }
//
//  m->WriteString(p.possibly_invalid_spec());
//  // TODO(brettw) bug 684583: Add encoding for query params.
//}
//
//bool ParamTraits<GURL>::Read(const Message* m, base::PickleIterator* iter, GURL* p) {
//  std::string s;
//  if (!iter->ReadString(&s) || s.length() > common::GetMaxURLChars()) {
//    *p = GURL();
//    return false;
//  }
//  *p = GURL(s);
//  if (!s.empty() && !p->is_valid()) {
//    *p = GURL();
//    return false;
//  }
//  return true;
//}
//
//void ParamTraits<GURL>::Log(const GURL& p, std::string* l) {
//  l->append(p.spec());
//}

//void ParamTraits<url::Origin>::Write(Message* m,
//                                          const url::Origin& p) {
//  m->WriteString(p.string());
//}
//
//bool ParamTraits<url::Origin>::Read(const Message* m,
//                                    base::PickleIterator* iter,
//                                    url::Origin* p) {
//  std::string s;
//  if (!iter->ReadString(&s)) {
//    *p = url::Origin();
//    return false;
//  }
//  *p = url::Origin(s);
//  return true;
//}
//
//void ParamTraits<url::Origin>::Log(const url::Origin& p, std::string* l) {
//  l->append(p.string());
//}

void ParamTraits<net::HostPortPair>::Write(Message* m, const param_type& p) {
  WriteParam(m, p.host());
  WriteParam(m, p.port());
}

bool ParamTraits<net::HostPortPair>::Read(const Message* m,
                                          base::PickleIterator* iter,
                                          param_type* r) {
  std::string host;
  uint16 port;
  if (!ReadParam(m, iter, &host) || !ReadParam(m, iter, &port))
    return false;

  r->set_host(host);
  r->set_port(port);
  return true;
}

void ParamTraits<net::HostPortPair>::Log(const param_type& p, std::string* l) {
  l->append(p.ToString());
}

void ParamTraits<net::IPEndPoint>::Write(Message* m, const param_type& p) {
  WriteParam(m, p.address());
  WriteParam(m, p.port());
}

bool ParamTraits<net::IPEndPoint>::Read(const Message* m, base::PickleIterator* iter,
                                        param_type* p) {
  net::IPAddressNumber address;
  uint16 port;
  if (!ReadParam(m, iter, &address) || !ReadParam(m, iter, &port))
    return false;
  if (address.size() &&
      address.size() != net::kIPv4AddressSize &&
      address.size() != net::kIPv6AddressSize) {
    return false;
  }
  *p = net::IPEndPoint(address, port);
  return true;
}

void ParamTraits<net::IPEndPoint>::Log(const param_type& p, std::string* l) {
  LogParam("IPEndPoint:" + p.ToString(), l);
}

//void ParamTraits<common::PageState>::Write(
//    Message* m, const param_type& p) {
//  WriteParam(m, p.ToEncodedData());
//}
//
//bool ParamTraits<common::PageState>::Read(
//    const Message* m, base::PickleIterator* iter, param_type* r) {
//  std::string data;
//  if (!ReadParam(m, iter, &data))
//    return false;
//  *r = common::PageState::CreateFromEncodedData(data);
//  return true;
//}
//
//void ParamTraits<common::PageState>::Log(
//    const param_type& p, std::string* l) {
//  l->append("(");
//  LogParam(p.ToEncodedData(), l);
//  l->append(")");
//}
//
//void ParamTraits<WebInputEventPointer>::Write(Message* m, const param_type& p) {
// m->WriteData(reinterpret_cast<const char*>(p), p->size);
//}
//
//bool ParamTraits<WebInputEventPointer>::Read(const Message* m,
// base::PickleIterator* iter,
// param_type* r) {
// const char* data;
// int data_length;
// if (!iter->ReadData(&data, &data_length)) {
//  NOTREACHED();
//  return false;
// }
// if (data_length < static_cast<int>(sizeof(blink::WebInputEvent))) {
//  NOTREACHED();
//  return false;
// }
// param_type event = reinterpret_cast<param_type>(data);
// // Check that the data size matches that of the event.
// if (data_length != static_cast<int>(event->size)) {
//  NOTREACHED();
//  return false;
// }
// const size_t expected_size_for_type =
//  common::WebInputEventTraits::GetSize(event->type);
// if (data_length != static_cast<int>(expected_size_for_type)) {
//  NOTREACHED();
//  return false;
// }
// *r = event;
// return true;
//}
//
//void ParamTraits<WebInputEventPointer>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p->size, l);
// l->append(", ");
// LogParam(p->type, l);
// l->append(", ");
// LogParam(p->timeStampSeconds, l);
// l->append(")");
//}
//
//void ParamTraits<blink::WebRect>::Write(Message* m, const param_type& p) {
// WriteParam(m, p.x);
// WriteParam(m, p.y);
// WriteParam(m, p.width);
// WriteParam(m, p.height);
//}
//
//bool ParamTraits<blink::WebRect>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->x) &&
//  ReadParam(m, iter, &p->y) &&
//  ReadParam(m, iter, &p->width) &&
//  ReadParam(m, iter, &p->height);
//}
//
//void ParamTraits<blink::WebRect>::Log(const param_type& p, std::string* l) {
// l->append("(");
// LogParam(p.x, l);
// l->append(", ");
// LogParam(p.y, l);
// l->append(", ");
// LogParam(p.width, l);
// l->append(", ");
// LogParam(p.height, l);
// l->append(")");
//}
//
//void ParamTraits<blink::WebCompositionUnderline>::Write(Message* m,
// const param_type& p) {
// WriteParam(m, p.startOffset);
// WriteParam(m, p.endOffset);
// WriteParam(m, p.color);
// WriteParam(m, p.thick);
//}
//
//bool ParamTraits<blink::WebCompositionUnderline>::Read(
// const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->startOffset) &&
//  ReadParam(m, iter, &p->endOffset) &&
//  ReadParam(m, iter, &p->color) &&
//  ReadParam(m, iter, &p->thick);
//}
//
//void ParamTraits<blink::WebCompositionUnderline>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p.startOffset, l);
// l->append(",");
// LogParam(p.endOffset, l);
// l->append(":");
// LogParam(p.color, l);
// l->append(":");
// LogParam(p.thick, l);
// l->append(")");
//}
//
//void ParamTraits<common::Referrer>::Write(Message* m, const param_type& p) {
// WriteParam(m, p.url);
// WriteParam(m, p.policy);
//}
//
//bool ParamTraits<common::Referrer>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->url) &&
//  ReadParam(m, iter, &p->policy);
//}
//
//void ParamTraits<common::Referrer>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p.url, l);
// l->append(",");
// LogParam(p.policy, l);
// l->append(")");
//}
//
//void ParamTraits<common::SSLStatus>::Write(Message* m, const param_type& p) {
// WriteParam(m, p.security_style);
// WriteParam(m, p.cert_id);
// WriteParam(m, p.cert_status);
// WriteParam(m, p.security_bits);
// WriteParam(m, p.connection_status);
// WriteParam(m, p.content_status);
// WriteParam(m, p.signed_certificate_timestamp_ids);
//}
//
//bool ParamTraits<common::SSLStatus>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->security_style) &&
//  ReadParam(m, iter, &p->cert_id) &&
//  ReadParam(m, iter, &p->cert_status) &&
//  ReadParam(m, iter, &p->security_bits) &&
//  ReadParam(m, iter, &p->connection_status) &&
//  ReadParam(m, iter, &p->content_status) &&
//  ReadParam(m, iter, &p->signed_certificate_timestamp_ids);
//}
//
//void ParamTraits<common::SSLStatus>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p.security_style, l);
// l->append(",");
// LogParam(p.cert_id, l);
// l->append(",");
// LogParam(p.cert_status, l);
// l->append(",");
// LogParam(p.security_bits, l);
// l->append(",");
// LogParam(p.connection_status, l);
// l->append(",");
// LogParam(p.content_status, l);
// l->append(",");
// LogParam(p.signed_certificate_timestamp_ids, l);
// l->append(")");
//}
//
//void ParamTraits<common::SignedCertificateTimestampIDAndStatus>::Write(Message* m, const param_type& p) {
// WriteParam(m, p.id);
// WriteParam(m, p.status);
//}
//
//bool ParamTraits<common::SignedCertificateTimestampIDAndStatus>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->id) &&
//  ReadParam(m, iter, &p->status);
//}
//
//void ParamTraits<common::SignedCertificateTimestampIDAndStatus>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p.id, l);
// l->append(",");
// LogParam(p.status, l);
// l->append(")");
//}
//
//void ParamTraits<blink::WebWindowFeatures>::Write(Message* m, const param_type& p) {
// WriteParam(m, p.x);
// WriteParam(m, p.xSet);
// WriteParam(m, p.y);
// WriteParam(m, p.ySet);
// WriteParam(m, p.width);
// WriteParam(m, p.widthSet);
// WriteParam(m, p.height);
// WriteParam(m, p.heightSet);
// WriteParam(m, p.menuBarVisible);
// WriteParam(m, p.statusBarVisible);
// WriteParam(m, p.toolBarVisible);
// WriteParam(m, p.locationBarVisible);
// WriteParam(m, p.scrollbarsVisible);
// WriteParam(m, p.resizable);
// WriteParam(m, p.fullscreen);
// WriteParam(m, p.dialog);
//}
//
//bool ParamTraits<blink::WebWindowFeatures>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return
//  ReadParam(m, iter, &p->x) &&
//  ReadParam(m, iter, &p->xSet) &&
//  ReadParam(m, iter, &p->y) &&
//  ReadParam(m, iter, &p->ySet) &&
//  ReadParam(m, iter, &p->width) &&
//  ReadParam(m, iter, &p->widthSet) &&
//  ReadParam(m, iter, &p->height) &&
//  ReadParam(m, iter, &p->heightSet) &&
//  ReadParam(m, iter, &p->menuBarVisible) &&
//  ReadParam(m, iter, &p->statusBarVisible) &&
//  ReadParam(m, iter, &p->toolBarVisible) &&
//  ReadParam(m, iter, &p->locationBarVisible) &&
//  ReadParam(m, iter, &p->scrollbarsVisible) &&
//  ReadParam(m, iter, &p->resizable) &&
//  ReadParam(m, iter, &p->fullscreen) &&
//  ReadParam(m, iter, &p->dialog);
//}
//
//void ParamTraits<blink::WebWindowFeatures>::Log(const param_type& p,
// std::string* l) {
// l->append("(");
// LogParam(p.x, l);
// l->append(",");
// LogParam(p.xSet, l);
// l->append(",");
// LogParam(p.y, l);
// l->append(",");
// LogParam(p.ySet, l);
// l->append(",");
// LogParam(p.width, l);
// l->append(",");
// LogParam(p.widthSet, l);
// l->append(",");
// LogParam(p.height, l);
// l->append(",");
// LogParam(p.heightSet, l);
// l->append(",");
// LogParam(p.menuBarVisible, l);
// l->append(",");
// LogParam(p.statusBarVisible, l);
// l->append(",");
// LogParam(p.toolBarVisible, l);
// l->append(",");
// LogParam(p.locationBarVisible, l);
// l->append(",");
// LogParam(p.scrollbarsVisible, l);
// l->append(",");
// LogParam(p.resizable, l);
// l->append(",");
// LogParam(p.fullscreen, l);
// l->append(",");
// LogParam(p.dialog, l);
// l->append(")");
//}
//
//void ParamTraits<common::WebPreferences>::Write(Message* m, const param_type& p) {
// /*WriteParam(m, p.url);
// WriteParam(m, p.policy);*/
//}
//
//bool ParamTraits<common::WebPreferences>::Read(const Message* m, base::PickleIterator* iter,
// param_type* p) {
// return false;
//  /*ReadParam(m, iter, &p->url) &&
//  ReadParam(m, iter, &p->policy);*/
//}
//
//void ParamTraits<common::WebPreferences>::Log(const param_type& p,
// std::string* l) {
// /*l->append("(");
// LogParam(p.url, l);
// l->append(",");
// LogParam(p.policy, l);
// l->append(")");*/
//}


}  // namespace IPC

// Generate param traits write methods.
#include "ipc/param_traits_write_macros.h"
namespace IPC {
#undef CONTENT_PUBLIC_COMMON_COMMON_PARAM_TRAITS_MACROS_H_
#include "common/common_param_traits_macros.h"
}  // namespace IPC

// Generate param traits read methods.
#include "ipc/param_traits_read_macros.h"
namespace IPC {
#undef CONTENT_PUBLIC_COMMON_COMMON_PARAM_TRAITS_MACROS_H_
#include "common/common_param_traits_macros.h"
}  // namespace IPC

// Generate param traits log methods.
#include "ipc/param_traits_log_macros.h"
namespace IPC {
#undef CONTENT_PUBLIC_COMMON_COMMON_PARAM_TRAITS_MACROS_H_
#include "common/common_param_traits_macros.h"
}  // namespace IPC
