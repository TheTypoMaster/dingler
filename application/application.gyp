{
 'variables': {
 },
 'targets': [
  {
   'target_name': 'application',
   'type': 'static_library',
   'dependencies': [
      '../base/base.gyp:base',
      '../base/base.gyp:base_i18n',
   	  '../ipc/ipc.gyp:ipc',
   	  '../container/container.gyp:container_client',
   	  '../common/common.gyp:common',
   ],
   'sources': [
     'application_client.cc',
     'application_client.h',
     'application_main.cc',
     'application_main.h',
     'application_thread.cc',
     'application_thread.h',
   ],
  }],
 'conditions': [
 ],
}