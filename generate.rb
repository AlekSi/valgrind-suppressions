#!/usr/bin/env ruby

require "#{File.dirname(File.expand_path(__FILE__))}/valgrind"
require 'fileutils'

# Basic filter for suppression
def filter_suppression(suppression)
  filtered = []
  suppression.each do |line|
    break if line =~ /fun:main$/i
    break if line =~ /valgrind/i
    filtered << line
  end
  suppression = filtered
end

# Runs programs and writes suppressions to file
def generate_suppression(program_path, suppression_path)
  program_base = File.basename(program_path)

  # Rewrite file
  File.unlink suppression_path rescue nil
  f = File.new suppression_path, 'w+'
  f << "# Generated by #{program_base} at #{Time.now}\n"
  f << "# Valgrind version: #{`valgrind --version`.chomp}\n\n"

  print "Running #{program_base} ... "; $stdout.flush
  start = Time.now
  output = Valgrind::run_memcheck(program_path, true)
  puts "Done in #{(Time.now - start).to_i} seconds."

  in_suppression_block = false
  suppression = []
  output.each do |line|
    next if (line =~ /^==\d+==/) || (line =~ /^--\d+--/)  # valgrind's output

    in_suppression_block = true  if line == "{\n"
    in_suppression_block = false if line == "}\n"

    if in_suppression_block
      suppression << line
    elsif not suppression.empty?
      f.puts filter_suppression(suppression), "}\n\n"
      suppression = []
    end
  end

  f.close
end

# Returns array of _absolute_ paths
def list_of_programs(start_dir)
  res = []
  Dir.chdir start_dir do
    Dir.glob('*.bin') { |item| res << Dir.pwd + '/' + item if File.file?(item) && File.executable?(item) }
    Dir.glob('*/')    { |item| res += list_of_programs(item) if File.directory?(item) }
  end
  return res
end


FileUtils.rm( Dir.glob(Valgrind::suppressions_dir + '/??-*.supp') )
programs = list_of_programs( File.dirname(__FILE__) ).sort
programs.each do |program_path|
  suppression_path  = Valgrind::suppressions_dir + File.basename(program_path, '.bin')
  suppression_path += '_' + Valgrind::suppression_file_suffix + '.supp'
  generate_suppression(program_path, suppression_path)
end
