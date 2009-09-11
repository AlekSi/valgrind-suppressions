#!/usr/bin/env ruby

require "#{File.dirname(File.expand_path(__FILE__))}/valgrind"

Valgrind::run_memcheck($*.join(' '), false)
