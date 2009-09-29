require 'valgrind'

MAKE = 'make'
GCC = 'gcc -o %output% %mode% -Wall -I. %files%'
GXX = 'g++ -o %output% %mode% -Wall -I. %files%'
QMAKE4 = (Valgrind.os == 'Darwin') ? 'qmake -spec macx-g++ -config %mode%' : 'qmake-qt4 -config %mode%'
DEBUG = '-g'
RELEASE = '-O2'

def build_with_gcc(mode)
  cmd = GCC.dup
  cmd['%output%'] = File.basename(Dir.pwd) + '.bin'
  cmd['%mode%']   = (mode == :debug) ? DEBUG : RELEASE
  cmd['%files%']  = Dir.glob('*.c').join(' ')
  sh cmd
end

def build_with_gxx(mode)
  cmd = GXX.dup
  cmd['%output%'] = File.basename(Dir.pwd) + '.bin'
  cmd['%mode%']   = (mode == :debug) ? DEBUG : RELEASE
  cmd['%files%']  = Dir.glob('*.cpp').join(' ')
  sh cmd
end

def build_with_qmake4(mode)
  cmd = QMAKE4.dup
  cmd["%mode%"] = mode.to_s
  sh "#{MAKE} distclean" rescue nil
  sh "#{cmd} && #{MAKE}"
end


def build(mode)
  Dir.glob('??-*/').sort.each do |dir|
    Dir.chdir dir do
      build_with_gcc(mode)    unless Dir.glob('*.c').empty?
      build_with_gxx(mode)    unless Dir.glob('*.cpp').empty?
      build_with_qmake4(mode) unless Dir.glob('*.pro').empty?
    end
  end
end

desc "Build generators in debug mode"
task :build_debug do
  build :debug
end

desc "Build generators in release mode"
task :build_release do
  build :release
end
