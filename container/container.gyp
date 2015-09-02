{
'variables': {
 },
 'targets': [
  {
   'target_name': 'container_host',
   'type': 'static_library',
   'dependencies': [
      '../base/base.gyp:base',
   ],
   'sources': [
    'host/namespace/blob/blob.h',
    'host/namespace/blob/blob.cc',
    'host/namespace/blob/blob_namespace.h',
    'host/namespace/blob/blob_namespace.cc',
    'host/namespace/container/container_namespace.h',
    'host/namespace/container/container_namespace.cc',
    'host/namespace/container/container_pool_resource.h',
    'host/namespace/container/container_pool_resource.cc',
    'host/namespace/container/container_resource.h',
    'host/namespace/container/container_resource.cc',
    'host/namespace/container/volume_resource.h',
    'host/namespace/container/volume_resource.cc',
    'host/namespace/credential/auth_token.h',
    'host/namespace/credential/auth_token.cc',
    'host/namespace/credential/credential_namespace.h',
    'host/namespace/credential/credential_namespace.cc',
    'host/namespace/credential/keystore.h',
    'host/namespace/credential/keystore.cc',
    'host/namespace/credential/userid.h',
    'host/namespace/credential/userid.cc',
    'host/namespace/device/camera.h',
    'host/namespace/device/camera.cc',
    'host/namespace/device/device_namespace.h',
    'host/namespace/device/device_namespace.cc',
    'host/namespace/index/index_namespace.h',
    'host/namespace/index/index_namespace.cc',
    'host/namespace/io/bt_socket.h',
    'host/namespace/io/bt_socket.cc',
    'host/namespace/io/console.h',
    'host/namespace/io/console.cc',
    'host/namespace/io/http_server_socket.h',
    'host/namespace/io/http_server_socket.cc',
    'host/namespace/io/http_socket.h',
    'host/namespace/io/http_socket.cc',
    'host/namespace/io/https_server_socket.h',
    'host/namespace/io/https_server_socket.cc',
    'host/namespace/io/https_socket.h',
    'host/namespace/io/https_socket.cc',
    'host/namespace/io/io_namespace.h',
    'host/namespace/io/io_namespace.cc',
    'host/namespace/io/io_signal.h',
    'host/namespace/io/io_signal.cc',
    'host/namespace/io/ipc_server_socket.h',
    'host/namespace/io/ipc_server_socket.cc',
    'host/namespace/io/ipc_socket.h',
    'host/namespace/io/ipc_socket.cc',
    'host/namespace/io/dingler_peer.h',
    'host/namespace/io/dingler_peer.cc',
    'host/namespace/io/dingler_socket.h',
    'host/namespace/io/dingler_socket.cc',
    'host/namespace/io/rpc_server_socket.h',
    'host/namespace/io/rpc_server_socket.cc',
    'host/namespace/io/rpc_socket.h',
    'host/namespace/io/rpc_socket.cc',
    'host/namespace/io/runnable_socket.h',
    'host/namespace/io/runnable_socket.cc',
    'host/namespace/io/server_socket.h',
    'host/namespace/io/server_socket.cc',
    'host/namespace/io/socket.h',
    'host/namespace/io/socket.cc',
    'host/namespace/io/stderr.h',
    'host/namespace/io/stderr.cc',
    'host/namespace/io/stdin.h',
    'host/namespace/io/stdin.cc',
    'host/namespace/io/stdout.cc',
    'host/namespace/io/stdout.h',
    'host/namespace/io/tcp_server_socket.cc',
    'host/namespace/io/tcp_server_socket.h',
    'host/namespace/io/tcp_socket.cc',
    'host/namespace/io/tcp_socket.h',
    'host/namespace/io/tor_socket.cc',
    'host/namespace/io/tor_socket.h',
    'host/namespace/io/udp_server_socket.cc',
    'host/namespace/io/udp_server_socket.h',
    'host/namespace/io/udp_socket.cc',
    'host/namespace/io/udp_socket.h',
    'host/namespace/kv/kv_namespace.cc',
    'host/namespace/kv/kv_namespace.h',
    'host/namespace/kv/kv_node.cc',
    'host/namespace/kv/kv_node.h',
    'host/namespace/plugin/plugin_namespace.cc',
    'host/namespace/plugin/plugin_namespace.h',
    'host/namespace/process/process.cc',
    'host/namespace/process/process.h',
    'host/namespace/process/process_namespace.cc',
    'host/namespace/process/process_namespace.h',
    'host/namespace/process/resource_pool.cc',
    'host/namespace/process/resource_pool.h',
    'host/namespace/root/root_namespace.cc',
    'host/namespace/root/root_namespace.h',
    'host/namespace/root/root_node.cc',
    'host/namespace/root/root_node.h',
    'host/namespace/run/run_namespace.cc',
    'host/namespace/run/run_namespace.h',
    'host/namespace/run/runnable.cc',
    'host/namespace/run/runnable.h',
    'host/namespace/service/service_api.cc',
    'host/namespace/service/service_api.h',
    'host/namespace/service/service_channel.cc',
    'host/namespace/service/service_channel.h',
    'host/namespace/service/service_contract.cc',
    'host/namespace/service/service_contract.h',
    'host/namespace/service/service_namespace.cc',
    'host/namespace/service/service_namespace.h',
    'host/namespace/service/service_network.cc',
    'host/namespace/service/service_network.h',
    'host/namespace/service/service_peer.cc',
    'host/namespace/service/service_peer.h',
    'host/namespace/service/service_permission.cc',
    'host/namespace/service/service_permission.h',
    'host/namespace/service/service.cc',
    'host/namespace/service/service.h',
    'host/namespace/service/rpc/rpc_service_api.cc',
    'host/namespace/service/rpc/rpc_service_api.h',
    'host/namespace/service/rpc/rpc_service_channel.cc',
    'host/namespace/service/rpc/rpc_service_channel.h',
    'host/namespace/service/rpc/rpc_service.cc',
    'host/namespace/service/rpc/rpc_service.h',
    'host/namespace/social/social_contact.cc',
    'host/namespace/social/social_contact.h',
    'host/namespace/social/social_namespace.cc',
    'host/namespace/social/social_namespace.h',
    'host/namespace/social/social_net.cc',
    'host/namespace/social/social_net.h',
    'host/namespace/stats/stats_namespace.cc',
    'host/namespace/stats/stats_namespace.h',
    'host/namespace/sys/sys_capabilities.cc',
    'host/namespace/sys/sys_capabilities.h',
    'host/namespace/sys/sys_cpu.cc',
    'host/namespace/sys/sys_cpu.h',
    'host/namespace/sys/sys_host.cc',
    'host/namespace/sys/sys_host.h',
    'host/namespace/sys/sys_memory.cc',
    'host/namespace/sys/sys_memory.h',
    'host/namespace/sys/sys_namespace.cc',
    'host/namespace/sys/sys_namespace.h',
    'host/namespace/uuid/uuid_namespace.cc',
    'host/namespace/uuid/uuid_namespace.h',
    'host/namespace/wallet/wallet.cc',
    'host/namespace/wallet/wallet.h',
    'host/namespace/wallet/wallet_namespace.cc',
    'host/namespace/wallet/wallet_namespace.h',
    'host/namespace/namespace.h',
    'host/namespace/namespace.cc',
    'host/namespace/namespace_index.h',
    'host/namespace/namespace_index.cc',
    'host/namespace/namespace_index_db.h',
    'host/namespace/namespace_index_db.cc',
    'host/namespace/namespace_inode.h',
    'host/namespace/namespace_view.h',
    'host/namespace/namespace_view.cc',
    'host/namespace/resource.h',
    'host/namespace/resource.cc',
    'host/volume/volume_backend.cc',
    'host/volume/volume_backend.h',
    'host/volume/volume_dataset.cc',
    'host/volume/volume_dataset.h',
    'host/volume/volume_drive.cc',
    'host/volume/volume_drive.h',
    'host/volume/volume_mount_table.cc',
    'host/volume/volume_mount_table.h',
    'host/volume/volume_mount.cc',
    'host/volume/volume_mount.h',
    'host/volume/volume_pool.cc',
    'host/volume/volume_pool.h',
    'host/volume/volume.cc',
    'host/volume/volume.h',
    'host/container.h',
    'host/container.cc',
    'host/container_main.h',
    'host/container_main.cc',
    'host/container_process.h',
    'host/container_process.cc',
    'host/container_thread.h',
    'host/container_thread.cc',
   ],
  },
  {
   'target_name': 'container_common',
   'type': 'static_library',
   'dependencies': [
    '../base/base.gyp:base',
   ],
   'sources': [
    'common\constants.cc',
    'common\constants.h',
    'common\container_messages.h',
    'common\p2p_messages.h',
    'common\tor_messages.h',
    'common\uuid.cc',
    'common\uuid.h',
   ],
  },
  {
     'target_name': 'container_client',
     'type': 'static_library',
     'dependencies': [
        '../base/base.gyp:base',
     ],
     'sources': [
       'client\container_client.cc',
       'client\container_client.h',
       'client\container_navigator.cc',
       'client\container_navigator.h',
       'client\result_set.cc',
       'client\result_set.h',
     ],
  },
  ],
 'conditions': [
 ],
}
