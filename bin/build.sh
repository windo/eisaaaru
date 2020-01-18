#!/bin/sh

c++ extract.cc -g -DBOOST_LOG_DYN_LINK -l tag -l boost_program_options -l boost_thread -l boost_system -l boost_log -l pthread -o extract
