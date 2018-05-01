//----------------------------------------------------------------------------
/// \file  test_logger.cpp
//----------------------------------------------------------------------------
/// \brief Test cases for the logging framework
//----------------------------------------------------------------------------
// Copyright (c) 2010 Serge Aleynikov <saleyn@gmail.com>
// Created: 2009-11-20
//----------------------------------------------------------------------------
/*
***** BEGIN LICENSE BLOCK *****

This file may be included in different open-source projects

Copyright (C) 2009 Serge Aleynikov <saleyn@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

***** END LICENSE BLOCK *****
*/
#ifndef UTXX_STANDALONE
#include <boost/test/unit_test.hpp>
#endif

#include <iostream>
#include <utxx/logger.hpp>
#include <utxx/logger/logger_impl_console.hpp>
#include <utxx/verbosity.hpp>
#include <utxx/variant_tree.hpp>
#include <signal.h>
#include <string.h>

//#define BOOST_TEST_MAIN

using namespace boost::property_tree;
using namespace utxx;
using namespace std;

namespace {
    struct test {
        struct inner {
            static void log (int i) {
                LOG_DEBUG("This is a %d debug",  i);
            }
            static void clog(int i) { CLOG_DEBUG("Cat5","This is a %d debug",i); }
        };
    };
}

#ifndef UTXX_STANDALONE
BOOST_AUTO_TEST_CASE( test_logger1 )
{
    variant_tree pt;

    BOOST_CHECK_EQUAL(0, (as_int<LEVEL_NONE>()));
    BOOST_CHECK_EQUAL(1, (as_int<LEVEL_ALERT>()));
    BOOST_CHECK_EQUAL(1, (as_int<LEVEL_FATAL>()));
    BOOST_CHECK_EQUAL(1, (as_int<LEVEL_ERROR>()));
    BOOST_CHECK_EQUAL(1, (as_int<LEVEL_WARNING>()));
    BOOST_CHECK_EQUAL(2, (as_int<LEVEL_NOTICE>()));
    BOOST_CHECK_EQUAL(3, (as_int<LEVEL_INFO>()));
    BOOST_CHECK_EQUAL(4, (as_int<LEVEL_DEBUG>()));
    BOOST_CHECK_EQUAL(5, (as_int<LEVEL_TRACE>()));
    BOOST_CHECK_EQUAL(6, (as_int<LEVEL_TRACE1>()));
    BOOST_CHECK_EQUAL(7, (as_int<LEVEL_TRACE2>()));
    BOOST_CHECK_EQUAL(8, (as_int<LEVEL_TRACE3>()));
    BOOST_CHECK_EQUAL(9, (as_int<LEVEL_TRACE4>()));
    BOOST_CHECK_EQUAL(10,(as_int<LEVEL_TRACE5>()));

    BOOST_CHECK_EQUAL(0, (as_int(LEVEL_NONE)));
    BOOST_CHECK_EQUAL(1, (as_int(LEVEL_ALERT)));
    BOOST_CHECK_EQUAL(1, (as_int(LEVEL_FATAL)));
    BOOST_CHECK_EQUAL(1, (as_int(LEVEL_ERROR)));
    BOOST_CHECK_EQUAL(1, (as_int(LEVEL_WARNING)));
    BOOST_CHECK_EQUAL(2, (as_int(LEVEL_NOTICE)));
    BOOST_CHECK_EQUAL(3, (as_int(LEVEL_INFO)));
    BOOST_CHECK_EQUAL(4, (as_int(LEVEL_DEBUG)));
    BOOST_CHECK_EQUAL(5, (as_int(LEVEL_TRACE)));
    BOOST_CHECK_EQUAL(6, (as_int(LEVEL_TRACE1)));
    BOOST_CHECK_EQUAL(7, (as_int(LEVEL_TRACE2)));
    BOOST_CHECK_EQUAL(8, (as_int(LEVEL_TRACE3)));
    BOOST_CHECK_EQUAL(9, (as_int(LEVEL_TRACE4)));
    BOOST_CHECK_EQUAL(10,(as_int(LEVEL_TRACE5)));

    BOOST_CHECK(LEVEL_NONE    == as_log_level(0 ));
    BOOST_CHECK(LEVEL_WARNING == as_log_level(1 ));
    BOOST_CHECK(LEVEL_NOTICE  == as_log_level(2 ));
    BOOST_CHECK(LEVEL_INFO    == as_log_level(3 ));
    BOOST_CHECK(LEVEL_DEBUG   == as_log_level(4 ));
    BOOST_CHECK(LEVEL_TRACE   == as_log_level(5 ));
    BOOST_CHECK(LEVEL_TRACE1  == as_log_level(6 ));
    BOOST_CHECK(LEVEL_TRACE2  == as_log_level(7 ));
    BOOST_CHECK(LEVEL_TRACE3  == as_log_level(8 ));
    BOOST_CHECK(LEVEL_TRACE4  == as_log_level(9 ));
    BOOST_CHECK(LEVEL_TRACE5  == as_log_level(10));

    BOOST_CHECK(LEVEL_TRACE   == parse_log_level("trace"));
    BOOST_CHECK(LEVEL_TRACE5  == parse_log_level("trace5"));
    BOOST_CHECK(LEVEL_TRACE1  == parse_log_level("trace1"));
    BOOST_CHECK(LEVEL_INFO    == parse_log_level("info"));
    BOOST_CHECK(LEVEL_WARNING == parse_log_level("warning"));
    BOOST_CHECK(LEVEL_ERROR   == parse_log_level("error"));
    BOOST_CHECK(LEVEL_WARNING == parse_log_level("1"));
    BOOST_CHECK(LEVEL_NONE    == parse_log_level("none"));
    BOOST_CHECK_EQUAL(int(LEVEL_INFO),  int(parse_log_level("3")));
    BOOST_CHECK_EQUAL(int(LEVEL_DEBUG), int(parse_log_level("4")));
    BOOST_CHECK_EQUAL(int(LEVEL_TRACE), int(parse_log_level("5")));
    BOOST_CHECK_EQUAL(int(LEVEL_TRACE5),int(parse_log_level("11")));
    BOOST_CHECK_EQUAL(int(LEVEL_TRACE5),int(parse_log_level("110")));
    BOOST_CHECK_THROW(logger::parse_log_level("trace6"), std::runtime_error);

    BOOST_CHECK_EQUAL("TRACE5", log_level_to_string(utxx::LEVEL_TRACE5, false));
    BOOST_CHECK_EQUAL("TRACE",  log_level_to_string(utxx::LEVEL_TRACE5));
    BOOST_CHECK_EQUAL("TRACE1", log_level_to_string(utxx::LEVEL_TRACE1, false));
    BOOST_CHECK_EQUAL("TRACE",  log_level_to_string(utxx::LEVEL_TRACE1));
    BOOST_CHECK_EQUAL("TRACE",  log_level_to_string(utxx::LEVEL_TRACE, false));
    BOOST_CHECK_EQUAL("TRACE",  log_level_to_string(utxx::LEVEL_TRACE));
    BOOST_CHECK_EQUAL("DEBUG",  log_level_to_string(utxx::LEVEL_DEBUG, false));
    BOOST_CHECK_EQUAL("DEBUG",  log_level_to_string(utxx::LEVEL_DEBUG));
    BOOST_CHECK_EQUAL("FATAL",  log_level_to_string(utxx::LEVEL_FATAL));
    BOOST_CHECK_EQUAL("ALERT",  log_level_to_string(utxx::LEVEL_ALERT));
    BOOST_CHECK_EQUAL("LOG",    log_level_to_string(utxx::LEVEL_LOG));

    BOOST_CHECK_EQUAL("TRACE5|TRACE|DEBUG", log_levels_to_str(utxx::LEVEL_TRACE5 | utxx::LEVEL_DEBUG));
    BOOST_CHECK_EQUAL("TRACE|DEBUG",        log_levels_to_str(utxx::LEVEL_TRACE  | utxx::LEVEL_DEBUG));
    BOOST_CHECK_EQUAL("DEBUG|INFO",         log_levels_to_str(utxx::LEVEL_INFO   | utxx::LEVEL_DEBUG));

    BOOST_CHECK_EQUAL("T",                  log_level_to_abbrev(utxx::LEVEL_TRACE1));
    BOOST_CHECK_EQUAL("T",                  log_level_to_abbrev(utxx::LEVEL_TRACE5));
    BOOST_CHECK_EQUAL("T",                  log_level_to_abbrev(utxx::LEVEL_TRACE));
    BOOST_CHECK_EQUAL("D",                  log_level_to_abbrev(utxx::LEVEL_DEBUG));

    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_TRACE1));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_TRACE5));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_TRACE));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_DEBUG));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_ERROR));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_FATAL));
    BOOST_CHECK_EQUAL(5u,                   log_level_size(utxx::LEVEL_ALERT));
    BOOST_CHECK_EQUAL(7u,                   log_level_size(utxx::LEVEL_WARNING));
    BOOST_CHECK_EQUAL(3u,                   log_level_size(utxx::LEVEL_LOG));
    BOOST_CHECK_EQUAL(4u,                   log_level_size(utxx::LEVEL_NONE));

    pt.put("logger.timestamp",             variant("time-usec"));
    pt.put("logger.min-level-filter",      variant("debug"));
    pt.put("logger.console.stdout-levels", variant("debug|info|notice|warning|error|fatal|alert"));
    pt.put("logger.show-thread",           true);
    pt.put("logger.show-ident",            true);
    pt.put("logger.ident",                 variant("my-logger"));
    pt.put("logger.fatal-kill-signal",     0);
    pt.put("logger.silent-finish",         true);

    if (utxx::verbosity::level() != utxx::VERBOSE_NONE)
        pt.dump(std::cout, 2, false, true, ' ', 2);

    auto count = pt.count("logger");
    BOOST_REQUIRE_EQUAL(1u, count);
    BOOST_REQUIRE(pt.get_child_optional("logger.console"));

    logger& log = logger::instance();

    if (log.initialized())
        log.finalize();

    log.set_min_level_filter(LEVEL_DEBUG);
    auto ll = log.min_level_filter();
    BOOST_CHECK(ll == LEVEL_DEBUG);
    BOOST_CHECK((log.level_filter() & (int)LEVEL_TRACE ) != (int)LEVEL_TRACE );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_DEBUG ) == (int)LEVEL_DEBUG );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_INFO  ) == (int)LEVEL_INFO  );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_NOTICE) == (int)LEVEL_NOTICE);

    log.set_min_level_filter(LEVEL_TRACE);
    ll = log.min_level_filter();
    BOOST_CHECK(ll == LEVEL_TRACE);
    BOOST_CHECK((log.level_filter() & (int)LEVEL_TRACE2) != (int)LEVEL_TRACE2);
    BOOST_CHECK((log.level_filter() & (int)LEVEL_TRACE1) != (int)LEVEL_TRACE1);
    BOOST_CHECK((log.level_filter() & (int)LEVEL_TRACE ) == (int)LEVEL_TRACE );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_DEBUG ) == (int)LEVEL_DEBUG );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_INFO  ) == (int)LEVEL_INFO  );
    BOOST_CHECK((log.level_filter() & (int)LEVEL_NOTICE) == (int)LEVEL_NOTICE);

    log.init(pt, nullptr, false);

    auto console = static_cast<const logger_impl_console*>(log.get_impl("console"));

    BOOST_REQUIRE(console);

    BOOST_REQUIRE_EQUAL(
        LEVEL_DEBUG | LEVEL_INFO  | LEVEL_NOTICE | LEVEL_WARNING |
        LEVEL_ERROR | LEVEL_FATAL | LEVEL_ALERT,
        console->stdout_levels());

    std::stringstream s;
    s << "test_logger." << getpid();
    log.set_ident(s.str().c_str());

    if (verbosity::level() > VERBOSE_NONE)
        log.dump(std::cout);

    pthread_setname_np(pthread_self(), "log_tester");

    for (int i = 0; i < 2; i++) {
        LOG_ERROR  ("This is a %d %s #%d", i, "error", 123);
        LOG_WARNING("This is a %d %s", i, "warning");
        LOG_FATAL  ("This is a %d %s", i, "fatal error");
        LOG_INFO   ("This is a %d %s", i, "info");
        test::inner::log(i);
    }

    for (int i = 0; i < 2; i++) {
        CLOG_ERROR  ("Cat1", "This is an error %d #%d", i, 456);
        CLOG_WARNING("Cat2", "This is a %d %s", i, "warning");
        CLOG_FATAL  ("Cat3", "This is a %d %s", i, "fatal error");
        CLOG_INFO   ("Cat4", "This is a %d %s", i, "info");
        test::inner::clog(i);
    }

    UTXX_LOG(INFO, "A") << "This is an error #" << 10 << " and bool "
                        << true << ' ' << std::endl;

    UTXX_LOG(ERROR)     << "This is an error #" << 10 << " and bool "
                        << true << ' ' << std::endl;

    UTXX_LOG(INFO)      << std::endl;

    log.finalize();

    BOOST_REQUIRE(true); // to remove run-time warning
}

BOOST_AUTO_TEST_CASE( test_logger_split_file_size )
{
    variant_tree pt;
    const std::string filename_prefix = "logger.file";
    const char* filename = "/tmp/logger.file.log";
    pt.put("logger.timestamp",          variant("none"));
    pt.put("logger.show-ident",         variant(false));
    pt.put("logger.show-location",      variant(false));
    pt.put("logger.silent-finish",      variant(true));
    pt.put("logger.file.stdout-levels", variant("debug|info|warning|error|fatal|alert"));
    pt.put("logger.file.filename",      variant(filename));
    pt.put("logger.file.append",        variant(false));
    pt.put("logger.file.no-header",     variant(true));
    pt.put("logger.file.split-file",    variant(true));
    pt.put("logger.file.split-size",    1000);//size in bytes

    logger& log = logger::instance();
    log.init(pt);

    int countFiles = 0;
    std::set<std::string> file_names_in_dir;
    std::set<std::string> file_names_built;

    for(int i=0; i <100;i++)
    {
        auto temp_data = utxx::to_string("write count: ",i);
        LOG_INFO ("%s",temp_data.c_str());
    }

    log.finalize();

    //retrieve file names created in the directory
    DIR *dir;
    struct dirent *t;
    dir = opendir ("/tmp");
    if (dir != NULL) {
        while ((t = readdir (dir)) != NULL) {
            std::string f_name(t->d_name);
            if(f_name.find(filename_prefix) != std::string::npos) {
                ++countFiles;
                file_names_in_dir.insert(f_name);
            }
        }
        closedir (dir);
    } else {
        perror ("");
    }
    // build file names and compare with files created in directory
    for (int i=1;i <= countFiles; i++) {
        auto name = utxx::to_string(filename_prefix,"_", i,".log");
        file_names_built.insert(name);
    }
    BOOST_CHECK(file_names_in_dir == file_names_built);
    // compare each line in each file with total data supplied
    int line_count = 0;
    for(auto& file: file_names_in_dir) {
        auto f = utxx::to_string("/tmp/",file);
        std::ifstream in(f);
        std::string s, exp;
        while(getline(in, s) && line_count < 100) {
            char buf[128];
            sprintf(buf, "I|log_tester|write count: %d",line_count++); exp = buf;
            BOOST_REQUIRE_EQUAL(exp, s);
        }
        ::unlink(f.c_str());
    }
}

BOOST_AUTO_TEST_CASE( test_logger2 )
{
    variant_tree pt;
    pt.put("logger.timestamp",             variant("time-usec"));
    pt.put("logger.show-thread",           false);
    pt.put("logger.show-ident",            false);
    pt.put("logger.ident",                 variant("my-logger"));
    pt.put("logger.silent-finish",         true);

    logger& log = logger::instance();

    {
        pt.put("logger.min-level-filter",      variant("debug"));
        pt.put("logger.console.stdout-levels", variant("info|notice|warning|error"));
        if (log.initialized())
            log.finalize();

        log.init(pt, nullptr, false);

        BOOST_REQUIRE(log.initialized());
    }

    {
        pt.put("logger.min-level-filter",      variant("debug"));
        pt.put("logger.console.stdout-levels", variant("debug|notice|warning|error"));

        if (log.initialized())
            log.finalize();

        log.init(pt, nullptr, false);
    }

    {
        pt.put("logger.min-level-filter",      variant("debug"));
        pt.put("logger.console.stdout-levels", variant("trace|debug|notice|warning|error"));

        if (log.initialized())
            log.finalize();

        try {
            log.init(pt, nullptr, false);
            BOOST_CHECK(false);
        } catch (utxx::runtime_error& e) {
            auto exp = "Console logger's stdout levels filter "
                       "'TRACE|DEBUG|NOTICE|WARNING|ERROR' is less granular "
                       "than logger's default 'DEBUG'";
            BOOST_CHECK_EQUAL(exp, e.str());
        }
    }

    log.finalize();
}
#endif

#ifdef UTXX_STANDALONE

    void hdl (int sig, siginfo_t *siginfo, void *context)
    {
        printf ("Sending PID: %ld, UID: %ld signal %d\n",
                (long)siginfo->si_pid, (long)siginfo->si_uid, sig);
        if (sig == SIGSEGV) {
            struct sigaction action;
            memset(&action, 0, sizeof(action));
            sigemptyset(&action.sa_mask);
            action.sa_handler = SIG_DFL; // take default action for the signal
            sigaction(sig, &action, NULL);

            std::cout << "Restoring old signal handler" << std::endl;

            kill(getpid(), sig);
            abort(); // should never reach this
        }
    }

    void enable_sig_handler(const std::vector<std::pair<int,std::string>>& sigs) {
        struct sigaction act;

        memset (&act, '\0', sizeof(act));
        sigemptyset(&act.sa_mask);

        /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
        act.sa_flags |= SA_SIGINFO;
        /* Use the sa_sigaction field because the handles has two additional parameters */
        act.sa_sigaction = &hdl;

        for (auto& p : sigs)
            printf("Set %s handler -> %d\n", p.second, sigaction(p.first, &act, NULL));
    }

int main(int argc, char* argv[])
#else
BOOST_AUTO_TEST_CASE( test_logger_crash )
#endif
{
    variant_tree pt;

    pt.put("logger.timestamp",  variant("time-usec"));
    pt.put("logger.console.stdout-levels", variant("debug|notice|info|warning|error|fatal|alert"));
    pt.put("logger.show-ident", false);
    pt.put("logger.handle-crash-signals", true); // This is default behavior

    std::vector<std::pair<int,std::string>> sigs
        {{SIGTERM, "SIGTERM"},
         {SIGABRT, "SIGABRT"},
         {SIGSEGV, "SIGSEGV"},
         {SIGINT,  "SIGINT"}};

#ifdef UTXX_STANDALONE
    enable_sig_handler(sigs);
#endif

    sigset_t mask;
    if (sigprocmask(0, NULL, &mask) < 0)
        perror("sigprocmask");

    for (auto& p : sigs)
        BOOST_TEST_MESSAGE("Process has " << p.second.c_str() << " handler -> "
                           << sigismember(&mask, p.first));

    bool crash = getenv("UTXX_LOGGER_CRASH") && atoi(getenv("UTXX_LOGGER_CRASH"));

    if  (crash) {
        double* p = nullptr;
        kill(getpid(), SIGABRT);
        *p = 10.0;
    }

    #ifndef UTXX_STANDALONE
    BOOST_REQUIRE(true); // Keep the warning off
    #endif
}
