#pragma once

#include <glog/logging.h>

#ifdef NDEBUG

constexpr auto init_logging = [] {
    google::InitGoogleLogging("");
    google::InstallFailureSignalHandler();

    DLOG(INFO) << "Hello from logging subsystem";

    return true;
}();

#endif
