# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
  'targets': [
    {
      # GN version: //content/common:mojo_bindings
      'target_name': 'common_mojo_bindings_mojom',
      'type': 'none',
      'variables': {
        'mojom_files': [
          # NOTE: Sources duplicated in //content/common/BUILD.gn:mojo_bindings.
          'modules/common/application_setup.mojom',
          'modules/common/background_sync_service.mojom',
          #'modules/common/geolocation_service.mojom',
          'modules/common/permission_service.mojom',
          #'modules/common/presentation/presentation_service.mojom',
          'modules/common/process_control.mojom',
          'modules/common/render_frame_setup.mojom',
          # NOTE: Sources duplicated in
          # //content/public/common/BUILD.gn:mojo_bindings.
          'modules/common/background_sync.mojom',
          'modules/common/mojo_geoposition.mojom',
          'modules/common/permission_status.mojom',
        ],
      },
      'includes': [ 'third_party/mojo/mojom_bindings_generator_explicit.gypi' ],
    },
    {
      'target_name': 'common_mojo_bindings',
      'type': 'static_library',
      'variables': { 'enable_wexit_time_destructors': 1, },
      'dependencies': [
        'common_mojo_bindings_mojom',
        'mojo/mojo_base.gyp:mojo_application_bindings',
        'mojo/mojo_base.gyp:mojo_environment_chromium',
        'third_party/mojo/mojo_public.gyp:mojo_cpp_bindings',
      ]
    },
  ]
}