# Common things.

module Valgrind

  # Returns OS id.
  def self.os()
    `uname -s`.chomp
  end

  # Returns suffix for suppression file
  def self.suppression_file_suffix()
    # TODO lsb_release for GNU/Linux
    [os, `uname -m`, `uname -r`].join("_").delete("\n")
  end

  # Returns dir where generated suppressions are stored
  def self.suppressions_dir()
    File.dirname(__FILE__) + '/Suppressions/'
  end

  # Runs program under memcheck
  def self.run_memcheck(memcheck_params, program_path)
    cmd = 'valgrind --leak-check=full --error-limit=no --num-callers=30 --show-reachable=yes '
    cmd += '--dsymutil=yes ' if os == 'Darwin'
    cmd += memcheck_params

    # Changed current dir for confidence
    Dir.chdir File.dirname(program_path) do
      return `#{cmd + ' ./'+File.basename(program_path)} 2>&1`
    end
  end
end
