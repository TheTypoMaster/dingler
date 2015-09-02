{
'variables': {
 },
 'targets': [
  {
   'target_name': 'terminal',
   'type': 'static_library',
   'dependencies': [
      '../base/base.gyp:base',
      '../base/base.gyp:base_i18n',
   	  '../ipc/ipc.gyp:ipc',
   	  '../container/container.gyp:container_client',
   	  '../common/common.gyp:common',
   ],
   'sources': [
     'tools/build/build_tool.cc',
     'tools/build/build_tool.h',
     'tools/clone/clone_tool.cc',
     'tools/clone/clone_tool.h',
     'tools/create/create_tool.cc',
     'tools/create/create_tool.h',
     'tools/debug/debug_tool.cc',
     'tools/debug/debug_tool.h',
     'tools/drop/drop_tool.cc',
     'tools/drop/drop_tool.h',
     'tools/help/help_tool.cc',
     'tools/help/help_tool.h',
     'tools/kill/kill_tool.cc',
     'tools/kill/kill_tool.h',
     'tools/mount/mount_tool.cc',
     'tools/mount/mount_tool.h',
     'tools/net/net_tool.cc',
     'tools/net/net_tool.h',
     'tools/peer/peer_tool.cc',
     'tools/peer/peer_tool.h',
     'tools/pull/pull_tool.cc',
     'tools/pull/pull_tool.h',
     'tools/push/push_tool.cc',
     'tools/push/push_tool.h',
     'tools/query/query_tool.cc',
     'tools/query/query_tool.h',
     'tools/repl/repl_tool.cc',
     'tools/repl/repl_tool.h',
     'tools/run/run_tool.cc',
     'tools/run/run_tool.h',
     'tools/shutdown/shutdown_tool.cc',
     'tools/shutdown/shutdown_tool.h',
     'tools/start/start_tool.cc',
     'tools/start/start_tool.h',
     'tools/status/status_tool.cc',
     'tools/status/status_tool.h',
     'tools/stop/stop_tool.cc',
     'tools/stop/stop_tool.h',
     'tools/umount/umount_tool.cc',
     'tools/umount/umount_tool.h',
     'color.h',
     'command_ast.h',
     'command_executor.h',
     'command_executor.cc',
     'command_history.cc',
     'command_history.h',
     'command_parser.cc',
     'command_parser.h',
     'command_tool.h',
     'connection.cc',
     'connection.h',
     'constants.cc',
     'constants.h',
     'cursor.h',
     'key.h',
     'screen.cc',
     'screen.h',
     'screen_buffer.h',
     'screen_driver.h',
     'screen_driver_win.cc',
     'script_host.cc',
     'script_host.h',
     'session.cc',
     'session.h',
     'size.h',
     'status.h',
     'terminal.cc',
     'terminal.h',
     'terminal_main.cc',
     'terminal_main.h',
     'terminal_thread.cc',
     'terminal_thread.h',
     'thread_safe_sender.cc',
     'thread_safe_sender.h',
     'tool_command.cc',
     'tool_command.h',
   ],
  }],
 'conditions': [
 ],
}