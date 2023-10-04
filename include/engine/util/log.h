#ifndef VIOLET_LOG_H_
#define VIOLET_LOG_H_

#include "engine/thirdparty/log.h"

#ifndef NDEBUG
#define VGE_CORE_LOG_TRACE(...) log_trace(__VA_ARGS__)
#define VGE_CORE_LOG_DEBUG(...) log_debug(__VA_ARGS__)
#define VGE_CORE_LOG_INFO(...)  log_info(__VA_ARGS__)
#define VGE_CORE_LOG_WARN(...)  log_warn(__VA_ARGS__)
#define VGE_CORE_LOG_ERROR(...) log_error(__VA_ARGS__)
#define VGE_CORE_LOG_FATAL(...) log_fatal(__VA_ARGS__)
#else
#define VGE_CORE_LOG_TRACE(...)
#define VGE_CORE_LOG_DEBUG(...)
#define VGE_CORE_LOG_INFO(...)
#define VGE_CORE_LOG_WARN(...)
#define VGE_CORE_LOG_ERROR(...)
#define VGE_CORE_LOG_FATAL(...)

#endif

#define VGE_LOG_TRACE(...) log_trace(__VA_ARGS__)
#define VGE_LOG_DEBUG(...) log_debug(__VA_ARGS__)
#define VGE_LOG_INFO(...)  log_info(__VA_ARGS__)
#define VGE_LOG_WARN(...)  log_warn(__VA_ARGS__)
#define VGE_LOG_ERROR(...) log_error(__VA_ARGS__)
#define VGE_LOG_FATAL(...) log_fatal(__VA_ARGS__)


#endif // LOG_H_
