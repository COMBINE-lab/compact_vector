AM_CXXFLAGS = -Wall -Werror -std=c++11 -I$(top_srcdir)/include -I$(top_srcdir)/tests

pkginclude_HEADERS = include/compact_iterator.hpp		\
                     include/compact_vector.hpp			\
                     include/const_iterator_traits.hpp		\
                     include/parallel_iterator_traits.hpp	\
                     include/prefetch_iterator_traits.hpp
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = compact_vector.pc

##############################
# Unit tests
##############################
TESTS = all_tests
check_PROGRAMS = all_tests bit_vector_speed

all_tests_CXXFLAGS = $(AM_CXXFLAGS) -I$(top_srcdir)/unittests
all_tests_LDADD = -lpthread
all_tests_SOURCES = unittests/gtest/gtest-all.cc unittests/gtest/gtest_main.cc unittests/gtest/gtest.h
all_tests_SOURCES += unittests/test_compact_vector.cc

bit_vector_speed_SOURCES = tests/bit_vector_speed.cc tests/misc.hpp
