// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "url/origin.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

namespace {

TEST(OriginTest, UniqueOriginComparison) {
  url::Origin unique_origin;
  EXPECT_EQ("", unique_origin.scheme());
  EXPECT_EQ("", unique_origin.host());
  EXPECT_EQ(0, unique_origin.port());
  EXPECT_TRUE(unique_origin.unique());
  EXPECT_FALSE(unique_origin.IsSameOriginWith(unique_origin));

  const char* const urls[] = {"data:text/html,Hello!",
                              "javascript:alert(1)",
                              "file://example.com:443/etc/passwd",
                              "yay",
                              "http::///invalid.example.com/"};

  for (const auto& test_url : urls) {
    SCOPED_TRACE(test_url);
    GURL url(test_url);
    url::Origin origin(url);
    EXPECT_EQ("", origin.scheme());
    EXPECT_EQ("", origin.host());
    EXPECT_EQ(0, origin.port());
    EXPECT_TRUE(origin.unique());
    EXPECT_FALSE(origin.IsSameOriginWith(origin));
    EXPECT_FALSE(unique_origin.IsSameOriginWith(origin));
    EXPECT_FALSE(origin.IsSameOriginWith(unique_origin));
  }
}

TEST(OriginTest, ConstructFromGURL) {
  url::Origin different_origin(GURL("https://not-in-the-list.test/"));

  struct TestCases {
    const char* const url;
    const char* const expected_scheme;
    const char* const expected_host;
    const uint16 expected_port;
  } cases[] = {
      // IP Addresses
      {"http://192.168.9.1/", "http", "192.168.9.1", 80},
      {"http://[2001:db8::1]/", "http", "[2001:db8::1]", 80},

      // Punycode
      {"http://☃.net/", "http", "xn--n3h.net", 80},
      {"blob:http://☃.net/", "http", "xn--n3h.net", 80},

      // Generic URLs
      {"http://example.com/", "http", "example.com", 80},
      {"http://example.com:123/", "http", "example.com", 123},
      {"https://example.com/", "https", "example.com", 443},
      {"https://example.com:123/", "https", "example.com", 123},
      {"http://user:pass@example.com/", "http", "example.com", 80},
      {"http://example.com:123/?query", "http", "example.com", 123},
      {"https://example.com/#1234", "https", "example.com", 443},
      {"https://u:p@example.com:123/?query#1234", "https", "example.com", 123},

      // Registered URLs
      {"ftp://example.com/", "ftp", "example.com", 21},
      {"gopher://example.com/", "gopher", "example.com", 70},
      {"ws://example.com/", "ws", "example.com", 80},
      {"wss://example.com/", "wss", "example.com", 443},

      // file: URLs
      {"file:///etc/passwd", "file", "", 0},
      {"file://example.com/etc/passwd", "file", "example.com", 0},

      // Filesystem:
      {"filesystem:http://example.com/type/", "http", "example.com", 80},
      {"filesystem:http://example.com:123/type/", "http", "example.com", 123},
      {"filesystem:https://example.com/type/", "https", "example.com", 443},
      {"filesystem:https://example.com:123/type/", "https", "example.com", 123},

      // Blob:
      {"blob:http://example.com/guid-goes-here", "http", "example.com", 80},
      {"blob:http://example.com:123/guid-goes-here", "http", "example.com", 123},
      {"blob:https://example.com/guid-goes-here", "https", "example.com", 443},
      {"blob:http://u:p@example.com/guid-goes-here", "http", "example.com", 80},
  };

  for (const auto& test_case : cases) {
    SCOPED_TRACE(test_case.url);
    GURL url(test_case.url);
    EXPECT_TRUE(url.is_valid());
    url::Origin origin(url);
    EXPECT_EQ(test_case.expected_scheme, origin.scheme());
    EXPECT_EQ(test_case.expected_host, origin.host());
    EXPECT_EQ(test_case.expected_port, origin.port());
    EXPECT_FALSE(origin.unique());
    EXPECT_TRUE(origin.IsSameOriginWith(origin));
    EXPECT_FALSE(different_origin.IsSameOriginWith(origin));
    EXPECT_FALSE(origin.IsSameOriginWith(different_origin));
  }
}

TEST(OriginTest, Serialization) {
  struct TestCases {
    const char* const url;
    const char* const expected;
  } cases[] = {
      {"http://192.168.9.1/", "http://192.168.9.1"},
      {"http://[2001:db8::1]/", "http://[2001:db8::1]"},
      {"http://☃.net/", "http://xn--n3h.net"},
      {"http://example.com/", "http://example.com"},
      {"http://example.com:123/", "http://example.com:123"},
      {"https://example.com/", "https://example.com"},
      {"https://example.com:123/", "https://example.com:123"},
      {"file:///etc/passwd", "file://"},
      {"file://example.com/etc/passwd", "file://"},
  };

  for (const auto& test_case : cases) {
    SCOPED_TRACE(test_case.url);
    GURL url(test_case.url);
    EXPECT_TRUE(url.is_valid());
    url::Origin origin(url);
    EXPECT_EQ(test_case.expected, origin.Serialize());

    // The '<<' operator should produce the same serialization as Serialize().
    std::stringstream out;
    out << origin;
    EXPECT_EQ(test_case.expected, out.str());
  }
}

TEST(OriginTest, Comparison) {
  // These URLs are arranged in increasing order:
  const char* const urls[] = {
      "data:uniqueness",
      "http://a:80",
      "http://b:80",
      "https://a:80",
      "https://b:80",
      "http://a:81",
      "http://b:81",
      "https://a:81",
      "https://b:81",
  };

  for (size_t i = 0; i < arraysize(urls); i++) {
    GURL current_url(urls[i]);
    url::Origin current(current_url);
    for (size_t j = i; j < arraysize(urls); j++) {
      GURL compare_url(urls[j]);
      url::Origin to_compare(compare_url);
      EXPECT_EQ(i < j, current < to_compare) << i << " < " << j;
      EXPECT_EQ(j < i, to_compare < current) << j << " < " << i;
    }
  }
}

}  // namespace url
