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
    File.dirname(File.expand_path(__FILE__)) + '/Suppressions/'
  end

  # Returns string '--suppressions=<filename1> --suppressions=<filename2> ... ',
  # which contains all generated suppression files.
  def self.suppressions_for_valgrind()
    res = '';
    Dir.glob(suppressions_dir + '*.supp') { |item| res += "--suppressions=#{item} " }
    res
  end

  # Runs program under memcheck
  def self.run_memcheck(program_path, generate_mode)
    cmd = 'valgrind --leak-check=full --error-limit=no --num-callers=24 --show-reachable=yes --gen-suppressions=all '
    cmd += suppressions_for_valgrind
    cmd += '--dsymutil=yes ' if os == 'Darwin'
    cmd += "./#{File.basename(program_path)}"

    # Changed current dir for confidence
    Dir.chdir File.dirname(program_path) do
      if generate_mode
        return `#{cmd} 2>&1`
      else
        system cmd
      end
    end
  end

end
