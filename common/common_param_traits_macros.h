// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Singly or Multiply-included shared traits file depending on circumstances.
// This allows the use of IPC serialization macros in more than one IPC message
// file.
#ifndef STRIPES_MODULES_COMMON_COMMON_PARAM_TRAITS_MACROS_H_
#define STRIPES_MODULES_COMMON_COMMON_PARAM_TRAITS_MACROS_H_

//#include "modules/common/console_message_level.h"
//#include "modules/common/referrer.h"
//#include "modules/common/resource_type.h"
//#include "modules/common/request_context_type.h"
//#include "modules/common/request_context_frame_type.h"
//#include "modules/common/security_style.h"
//#include "modules/common/ssl_status.h"
//#include "modules/common/web_preferences.h"
//#include "modules/common/webplugininfo.h"
#include "ipc/ipc_message_macros.h"
#include "net/base/network_change_notifier.h"
#include "net/base/request_priority.h"
//#include "third_party/WebKit/public/platform/WebPageVisibilityState.h"
//#include "third_party/WebKit/public/platform/WebPoint.h"
//#include "third_party/WebKit/public/platform/WebRect.h"
//#include "third_party/WebKit/public/platform/WebReferrerPolicy.h"
//#include "third_party/WebKit/public/platform/WebURLRequest.h"
//#include "third_party/WebKit/public/web/WebInputEvent.h"
//#include "third_party/WebKit/public/web/WebContentSecurityPolicy.h"
//#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
//#include "third_party/WebKit/public/web/WebWindowFeatures.h"
//#include "ui/base/page_transition_types.h"
//#include "ui/base/window_open_disposition.h"
//#include "ui/events/latency_info.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT

//IPC_ENUM_TRAITS_VALIDATE(ui::PageTransition,
//                         ((value &
//                           ui::PageTransition::PAGE_TRANSITION_CORE_MASK) <=
//                          ui::PageTransition::PAGE_TRANSITION_LAST_CORE))
//IPC_ENUM_TRAITS_MAX_VALUE(net::NetworkChangeNotifier::ConnectionType,
//                          net::NetworkChangeNotifier::CONNECTION_LAST)
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(stripes::ConsoleMessageLevel,
//                              stripes::CONSOLE_MESSAGE_LEVEL_DEBUG,
//                              stripes::CONSOLE_MESSAGE_LEVEL_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::SecurityStyle,
//                          stripes::SECURITY_STYLE_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(blink::WebReferrerPolicy,
//                          blink::WebReferrerPolicyLast)
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::EditingBehavior,
//                          stripes::EDITING_BEHAVIOR_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(WindowOpenDisposition,
//                          WINDOW_OPEN_DISPOSITION_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(net::RequestPriority, net::MAXIMUM_PRIORITY)
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::V8CacheOptions,
//                          stripes::V8_CACHE_OPTIONS_LAST)
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(ui::PointerType,
//                              ui::POINTER_TYPE_FIRST,
//                              ui::POINTER_TYPE_LAST)
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(ui::HoverType,
//                              ui::HOVER_TYPE_FIRST,
//                              ui::HOVER_TYPE_LAST)
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(stripes::ImageAnimationPolicy,
//                              stripes::IMAGE_ANIMATION_POLICY_ALLOWED,
//                              stripes::IMAGE_ANIMATION_POLICY_NO_ANIMATION)

//IPC_ENUM_TRAITS_MIN_MAX_VALUE(stripes::RequestContextType,
//                              REQUEST_CONTEXT_TYPE_UNSPECIFIED
//                              REQUEST_CONTEXT_TYPE_LAST)
//
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(stripes::RequestContextFrameType,
//                              REQUEST_CONTEXT_FRAME_TYPE_AUXILIARY,
//                              REQUEST_CONTEXT_FRAME_TYPE_LAST)

//IPC_STRUCT_TRAITS_BEGIN(blink::WebPoint)
//  IPC_STRUCT_TRAITS_MEMBER(x)
//  IPC_STRUCT_TRAITS_MEMBER(y)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(blink::WebRect)
//  IPC_STRUCT_TRAITS_MEMBER(x)
//  IPC_STRUCT_TRAITS_MEMBER(y)
//  IPC_STRUCT_TRAITS_MEMBER(width)
//  IPC_STRUCT_TRAITS_MEMBER(height)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(stripes::Referrer)
//  IPC_STRUCT_TRAITS_MEMBER(url)
//  IPC_STRUCT_TRAITS_MEMBER(policy)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(stripes::SSLStatus)
//  IPC_STRUCT_TRAITS_MEMBER(security_style)
//  IPC_STRUCT_TRAITS_MEMBER(cert_id)
//  IPC_STRUCT_TRAITS_MEMBER(cert_status)
//  IPC_STRUCT_TRAITS_MEMBER(security_bits)
//  IPC_STRUCT_TRAITS_MEMBER(connection_status)
//  IPC_STRUCT_TRAITS_MEMBER(content_status)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(stripes::WebPluginMimeType)
//  IPC_STRUCT_TRAITS_MEMBER(mime_type)
//  IPC_STRUCT_TRAITS_MEMBER(file_extensions)
//  IPC_STRUCT_TRAITS_MEMBER(description)
//  IPC_STRUCT_TRAITS_MEMBER(additional_param_names)
//  IPC_STRUCT_TRAITS_MEMBER(additional_param_values)
//IPC_STRUCT_TRAITS_END()
//
////IPC_STRUCT_TRAITS_BEGIN(stripes::WebPluginInfo)
////  IPC_STRUCT_TRAITS_MEMBER(name)
////  IPC_STRUCT_TRAITS_MEMBER(path)
////  IPC_STRUCT_TRAITS_MEMBER(version)
////  IPC_STRUCT_TRAITS_MEMBER(desc)
////  IPC_STRUCT_TRAITS_MEMBER(mime_types)
////  IPC_STRUCT_TRAITS_MEMBER(type)
////  IPC_STRUCT_TRAITS_MEMBER(pepper_permissions)
////IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(stripes::SignedCertificateTimestampIDAndStatus)
// IPC_STRUCT_TRAITS_MEMBER(id)
// IPC_STRUCT_TRAITS_MEMBER(status)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(stripes::WebPreferences)
//  IPC_STRUCT_TRAITS_MEMBER(standard_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(fixed_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(serif_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(sans_serif_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(cursive_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(fantasy_font_family_map)
//  IPC_STRUCT_TRAITS_MEMBER(default_font_size)
//  IPC_STRUCT_TRAITS_MEMBER(default_fixed_font_size)
//  IPC_STRUCT_TRAITS_MEMBER(minimum_font_size)
//  IPC_STRUCT_TRAITS_MEMBER(minimum_logical_font_size)
//  IPC_STRUCT_TRAITS_MEMBER(default_encoding)
//  IPC_STRUCT_TRAITS_MEMBER(context_menu_on_mouse_up)
//  IPC_STRUCT_TRAITS_MEMBER(javascript_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(web_security_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(javascript_can_open_windows_automatically)
//  IPC_STRUCT_TRAITS_MEMBER(loads_images_automatically)
//  IPC_STRUCT_TRAITS_MEMBER(images_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(plugins_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(dom_paste_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(shrinks_standalone_images_to_fit)
//  IPC_STRUCT_TRAITS_MEMBER(uses_universal_detector)
//  IPC_STRUCT_TRAITS_MEMBER(text_areas_are_resizable)
//  IPC_STRUCT_TRAITS_MEMBER(java_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(allow_scripts_to_close_windows)
//  IPC_STRUCT_TRAITS_MEMBER(remote_fonts_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(javascript_can_access_clipboard)
//  IPC_STRUCT_TRAITS_MEMBER(xslt_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(xss_auditor_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(dns_prefetching_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(local_storage_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(databases_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(application_cache_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(tabs_to_links)
//  IPC_STRUCT_TRAITS_MEMBER(hyperlink_auditing_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(is_online)
//  IPC_STRUCT_TRAITS_MEMBER(connection_type)
//  IPC_STRUCT_TRAITS_MEMBER(allow_universal_access_from_file_urls)
//  IPC_STRUCT_TRAITS_MEMBER(allow_file_access_from_file_urls)
//  IPC_STRUCT_TRAITS_MEMBER(webaudio_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(experimental_webgl_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(pepper_3d_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(pinch_virtual_viewport_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(pinch_overlay_scrollbar_thickness)
//  IPC_STRUCT_TRAITS_MEMBER(use_solid_color_scrollbars)
//  IPC_STRUCT_TRAITS_MEMBER(flash_3d_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(flash_stage3d_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(flash_stage3d_baseline_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(gl_multisampling_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(privileged_webgl_extensions_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(webgl_errors_to_console_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(mock_scrollbars_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(asynchronous_spell_checking_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(unified_textchecker_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(accelerated_2d_canvas_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(minimum_accelerated_2d_canvas_size)
//  IPC_STRUCT_TRAITS_MEMBER(antialiased_2d_canvas_disabled)
//  IPC_STRUCT_TRAITS_MEMBER(antialiased_clips_2d_canvas_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(accelerated_2d_canvas_msaa_sample_count)
//  IPC_STRUCT_TRAITS_MEMBER(accelerated_filters_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(deferred_filters_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(container_culling_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(text_blobs_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(allow_displaying_insecure_content)
//  IPC_STRUCT_TRAITS_MEMBER(allow_running_insecure_content)
//  IPC_STRUCT_TRAITS_MEMBER(disable_reading_from_canvas)
//  IPC_STRUCT_TRAITS_MEMBER(strict_mixed_content_checking)
//  IPC_STRUCT_TRAITS_MEMBER(strict_powerful_feature_restrictions)
//  IPC_STRUCT_TRAITS_MEMBER(enable_scroll_animator)
//  IPC_STRUCT_TRAITS_MEMBER(password_echo_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(should_clear_document_background)
//  IPC_STRUCT_TRAITS_MEMBER(region_based_columns_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(touch_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(device_supports_touch)
//  IPC_STRUCT_TRAITS_MEMBER(device_supports_mouse)
//  IPC_STRUCT_TRAITS_MEMBER(touch_adjustment_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(pointer_events_max_touch_points)
//  IPC_STRUCT_TRAITS_MEMBER(available_pointer_types)
//  IPC_STRUCT_TRAITS_MEMBER(primary_pointer_type)
//  IPC_STRUCT_TRAITS_MEMBER(available_hover_types)
//  IPC_STRUCT_TRAITS_MEMBER(primary_hover_type)
//  IPC_STRUCT_TRAITS_MEMBER(sync_xhr_in_documents_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(deferred_image_decoding_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(image_color_profiles_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(should_respect_image_orientation)
//  IPC_STRUCT_TRAITS_MEMBER(number_of_cpu_cores)
//  IPC_STRUCT_TRAITS_MEMBER(editing_behavior)
//  IPC_STRUCT_TRAITS_MEMBER(supports_multiple_windows)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_meta_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(main_frame_resizes_are_orientation_changes)
//  IPC_STRUCT_TRAITS_MEMBER(initialize_at_minimum_page_scale)
//  IPC_STRUCT_TRAITS_MEMBER(smart_insert_delete_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(cookie_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(navigate_on_drag_drop)
//  IPC_STRUCT_TRAITS_MEMBER(spatial_navigation_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(v8_cache_options)
//  IPC_STRUCT_TRAITS_MEMBER(slimming_paint_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(pepper_accelerated_video_decode_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(animation_policy)
//#if defined(OS_ANDROID)
//  IPC_STRUCT_TRAITS_MEMBER(text_autosizing_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(font_scale_factor)
//  IPC_STRUCT_TRAITS_MEMBER(device_scale_adjustment)
//  IPC_STRUCT_TRAITS_MEMBER(force_enable_zoom)
//  IPC_STRUCT_TRAITS_MEMBER(fullscreen_supported)
//  IPC_STRUCT_TRAITS_MEMBER(double_tap_to_zoom_enabled)
//  IPC_STRUCT_TRAITS_MEMBER(user_gesture_required_for_media_playback)
//  IPC_STRUCT_TRAITS_MEMBER(default_video_poster_url)
//  IPC_STRUCT_TRAITS_MEMBER(support_deprecated_target_density_dpi)
//  IPC_STRUCT_TRAITS_MEMBER(use_legacy_background_size_shorthand_behavior)
//  IPC_STRUCT_TRAITS_MEMBER(wide_viewport_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(use_wide_viewport)
//  IPC_STRUCT_TRAITS_MEMBER(force_zero_layout_height)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_meta_layout_size_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_meta_merge_content_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_meta_non_user_scalable_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(viewport_meta_zero_values_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(clobber_user_agent_initial_scale_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(ignore_main_frame_overflow_hidden_quirk)
//  IPC_STRUCT_TRAITS_MEMBER(report_screen_size_in_physical_pixels_quirk)
//#endif
//  IPC_STRUCT_TRAITS_MEMBER(default_minimum_page_scale_factor)
//  IPC_STRUCT_TRAITS_MEMBER(default_maximum_page_scale_factor)
//IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_BEGIN(blink::WebWindowFeatures)
//  IPC_STRUCT_TRAITS_MEMBER(x)
//  IPC_STRUCT_TRAITS_MEMBER(xSet)
//  IPC_STRUCT_TRAITS_MEMBER(y)
//  IPC_STRUCT_TRAITS_MEMBER(ySet)
//  IPC_STRUCT_TRAITS_MEMBER(width)
//  IPC_STRUCT_TRAITS_MEMBER(widthSet)
//  IPC_STRUCT_TRAITS_MEMBER(height)
//  IPC_STRUCT_TRAITS_MEMBER(heightSet)
//  IPC_STRUCT_TRAITS_MEMBER(menuBarVisible)
//  IPC_STRUCT_TRAITS_MEMBER(statusBarVisible)
//  IPC_STRUCT_TRAITS_MEMBER(toolBarVisible)
//  IPC_STRUCT_TRAITS_MEMBER(locationBarVisible)
//  IPC_STRUCT_TRAITS_MEMBER(scrollbarsVisible)
//  IPC_STRUCT_TRAITS_MEMBER(resizable)
//  IPC_STRUCT_TRAITS_MEMBER(fullscreen)
//  IPC_STRUCT_TRAITS_MEMBER(dialog)
//IPC_STRUCT_TRAITS_END()
//
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::ResourceType,
//                          stripes::RESOURCE_TYPE_LAST_TYPE - 1)
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::RequestContextType,
//                          stripes::REQUEST_CONTEXT_TYPE_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(stripes::RequestContextFrameType,
//                          stripes::REQUEST_CONTEXT_FRAME_TYPE_LAST)
//IPC_ENUM_TRAITS_MAX_VALUE(blink::WebContentSecurityPolicyType,
//                          blink::WebContentSecurityPolicyTypeLast)
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(blink::WebInputEvent::Type,
//                              blink::WebInputEvent::TypeFirst,
//                              blink::WebInputEvent::TypeLast)
//IPC_ENUM_TRAITS_MAX_VALUE(blink::WebPageVisibilityState,
//                          blink::WebPageVisibilityStateLast)
//
//IPC_ENUM_TRAITS_MIN_MAX_VALUE(net::ct::SCTVerifyStatus,
//                          net::ct::SCT_STATUS_NONE,
//                          net::ct::SCT_STATUS_MAX)
//
//IPC_STRUCT_TRAITS_BEGIN(blink::WebCompositionUnderline)
//IPC_STRUCT_TRAITS_MEMBER(startOffset)
//IPC_STRUCT_TRAITS_MEMBER(endOffset)
//IPC_STRUCT_TRAITS_MEMBER(color)
//IPC_STRUCT_TRAITS_MEMBER(thick)
//IPC_STRUCT_TRAITS_MEMBER(backgroundColor)
//IPC_STRUCT_TRAITS_END()
//
////IPC_STRUCT_TRAITS_BEGIN(ui::LatencyInfo)
////IPC_STRUCT_TRAITS_MEMBER(latency_components)
////IPC_STRUCT_TRAITS_MEMBER(input_coordinates_size)
////IPC_STRUCT_TRAITS_MEMBER(input_coordinates)
////IPC_STRUCT_TRAITS_MEMBER(trace_id)
////IPC_STRUCT_TRAITS_MEMBER(terminated)
////IPC_STRUCT_TRAITS_END()
//
//IPC_STRUCT_TRAITS_MEMBER(startOffset)
//IPC_STRUCT_TRAITS_MEMBER(endOffset)
//IPC_STRUCT_TRAITS_MEMBER(color)
//IPC_STRUCT_TRAITS_MEMBER(thick)
//IPC_STRUCT_TRAITS_MEMBER(backgroundColor)
//IPC_STRUCT_TRAITS_END()

#endif  // STRIPES_MODULES_COMMON_COMMON_PARAM_TRAITS_MACROS_H_
