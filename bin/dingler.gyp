{
 'variables': {
 },
 'targets': [
  {
   'target_name': 'dingler',
   'type': 'executable',
   'dependencies': [
      '../application/application.gyp:application',
      '../base/base.gyp:base',
      '../base/base.gyp:base_i18n',
      '../base/base.gyp:base_prefs',
      '../base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
   	  '../ipc/ipc.gyp:ipc',
      '../crypto/crypto.gyp:crypto',
      '../terminal/terminal.gyp:terminal',
   	  #'../container/container.gyp:container',
   	  '../common/common.gyp:common',
   	  '../kernel/kernel.gyp:kernel',
      '../net/net.gyp:net',
      '../sdch/sdch.gyp:sdch',
      '../sql/sql.gyp:sql',
      '../third_party/icu/icu.gyp:icuuc',
      '../third_party/libxml/libxml.gyp:*',
      '../third_party/sqlite/sqlite.gyp:*',
      '../third_party/zlib/zlib.gyp:zlib',
      '../url/url.gyp:url_lib',
   ],
   'sources': [
     'dingler/dingler.cc',
     'dingler/dingler_main.h',
     'dingler/dingler_main.cc',
     'dingler/dingler_main_runner.h',
     'dingler/dingler_main_runner.cc',
   ],
  }],
 'conditions': [
 ],
}