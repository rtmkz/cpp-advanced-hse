#pragma once

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#undef CHECK
#undef INFO

#ifndef NDEBUG

#include <glog/logging.h>

void CustomPrefix(std::ostream &s, const LogMessageInfo &l, void *) {
    s << "[" << l.severity[0] << ' ' << l.filename << ':' << l.line_number << "]";
}

class LoggerInitializer : public Catch::TestEventListenerBase {
public:
    using Catch::TestEventListenerBase::TestEventListenerBase;

    // NOLINTNEXTLINE
    void testRunStarting(Catch::TestRunInfo const &) override {
        // NOLINTNEXTLINE
        FLAGS_logtostderr = true;

        google::InitGoogleLogging("", CustomPrefix);
        google::InstallFailureSignalHandler();

        DLOG(INFO) << "Hello from logging subsystem!";
    }
};

CATCH_REGISTER_LISTENER(LoggerInitializer)

#endif
