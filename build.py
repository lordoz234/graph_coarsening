import os, sys, subprocess

project_directory = os.getcwd()
compiler = {
    "g++" : ("gcc", "g++"),
    "clang" : ("clang", "clang++"),
    "msvc" : ("msvc", "msvc"),
    "icc" : ("icc", "icpc")
}
build_directories = {}

def create_folders():
    for compiler_name in compiler.keys():
        folder_name = "build_" + compiler_name
        os.chdir("..")
        if not os.path.exists(folder_name):
            os.mkdir(folder_name)
        os.chdir(folder_name)
        build_directories[compiler_name] = os.getcwd()
        os.chdir(project_directory)
    return 0


def lint_walk(subdirectory):
    return_code = 0
    for path, _, files in os.walk(os.path.join(project_directory, subdirectory)):
        for file in files:
            if (file.endswith(".h") or file.endswith(".cpp")):
                print("Checking: " + os.path.join(path, file))
                if not os.path.exists(os.path.join(build_directories[compiler_name], "lint.log")):
                    open(os.path.join(build_directories[compiler_name], "lint.log"), "w").close()
                os.system("cpplint " + os.path.join(path, file) + " 2> " + os.path.join(build_directories[compiler_name], "lint.log"))
                verdict = ""
                ingored_errors = 0
                f = open(os.path.join(build_directories[compiler_name], "lint.log"), "r")
                for line in f:
                    if line.endswith("use a pointer: benchmark::State& state  [runtime/references] [2]\n"):
                        ingored_errors += 1
                    verdict = line
                f.close()
                if (verdict.startswith("Done processing")):
                    print("\033[32mSuccess: " + file + "\033[0m")
                else:
                    real_errors = int(verdict.split()[-1]) - ingored_errors
                    if real_errors == 0:
                        print("\033[32mSuccess: " + file + "\033[0m")
                    else:
                        f = open(os.path.join(build_directories[compiler_name], "lint.log"), "r")
                        for line in f:
                            if (line.startswith("Done processing")):
                                break
                            print(line)
                        f.close()
                        print("\033[31mFailed: "  + file + "\033[0m")
                        return_code = 1
    return return_code

def lint():
    return_code = 0
    if not os.path.exists(build_directories[compiler_name]):
        os.mkdir(build_directories[compiler_name])
    return_code += lint_walk("modules")
    return_code += lint_walk("tests")
    return_code += lint_walk("benchmark")
    return return_code


def build():
    if ((os.name == "posix" and compiler_name == "msvc") or
        (os.name == "nt" and compiler_name == "clang")):
        print("This compiler is not supported by script on this OS")
        exit(1)
    return_code = 0
    if not os.path.exists(build_directories[compiler_name]):
        os.mkdir(build_directories[compiler_name])
    os.chdir(build_directories[compiler_name])
    if os.name == "posix":
        subprocess.call('cmake -D CMAKE_C_COMPILER=' + compiler[compiler_name][0] + ' -D CMAKE_CXX_COMPILER=' + compiler[compiler_name][1]
        + ' CMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ' + project_directory, shell=True)
    elif os.name == "nt":
        if compiler_name == "msvc":
            subprocess.call('cmake -D CMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ' + project_directory, shell=True)
        elif compiler_name == "g++":
            subprocess.call('cmake -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ' + project_directory, shell=True)
        elif compiler_name == "icc":
            subprocess.call('cmake -T "Intel C++ Compiler 19.0" ' + project_directory, shell=True)
    if os.name == "posix":
        subprocess.call("cppcheck -j4 --project=compile_commands.json > log_cppcheck", shell=True)
    elif os.name == "nt":
        subprocess.call("cppcheck --project=compile_commands.json > log_cppcheck", shell=True)
    subprocess.call("python " + os.path.join(project_directory, "scripts/static_analysis.py") + " log_cppcheck", shell=True)
    if os.name == "posix":
        return_code = subprocess.call("make -j4", shell=True)
    elif os.name == "nt":
        if compiler_name == "msvc":
            subprocess.call("msbuild ALL_BUILD.vcxproj", shell=True)
        elif compiler_name == "g++":
            return_code = subprocess.call("mingw32-make", shell=True)
    os.chdir(project_directory)
    return return_code

def run_main(output = None):
    if not os.path.exists(build_directories[compiler_name]):
        return -1
    os.chdir(build_directories[compiler_name])
    if os.name == "posix":
        return_code = subprocess.call("./modules/application/Graph_Partition" + ((" > " + output) if output else ""), shell=True)
    elif os.name == "nt":
        return_code = subprocess.call("modules\\application\\Graph_Partition" + ((" > " + output) if output else ""), shell=True)
    os.chdir(project_directory)
    return return_code

def run_tests():
    if not os.path.exists(build_directories[compiler_name]):
        return -1
    os.chdir(build_directories[compiler_name])
    if os.name == "posix":
        return_code = subprocess.call("./tests/Test_Target", shell=True)
    elif os.name == "nt":
        return_code = subprocess.call("tests\\Test_Target", shell=True)
    os.chdir(project_directory)
    return return_code

def benchmark():
    if not os.path.exists(build_directories[compiler_name]):
        return -1
    os.chdir(build_directories[compiler_name])
    if os.name == "posix":
        return_code = subprocess.call("./benchmark/Benchmark_Target", shell=True)
    elif os.name == "nt":
        return_code = subprocess.call("benchmark\\Benchmark_Target", shell=True)
    os.chdir(project_directory)
    return return_code

def asymp(args):
    if not os.path.exists(os.path.join(build_directories[compiler_name], "asymp.log")):
        run_main(os.path.join(build_directories[compiler_name], "asymp.log"))
    if os.name == "posix":
        script_call_command = ("python3 " + os.path.join(project_directory, "scripts/asymptotics.py")+
                            " " + os.path.join(build_directories[compiler_name], "asymp.log"))
    elif os.name == "nt":
        script_call_command = ("python " + os.path.join(project_directory, "scripts/asymptotics.py")+
                            " " + os.path.join(build_directories[compiler_name], "asymp.log"))
    for arg in args:
        script_call_command += " " + arg
    return_code = subprocess.call(script_call_command, shell=True)
    return return_code

def cmake_graph():
    if not os.path.exists(build_directories[compiler_name]):
        return -1
    os.chdir(build_directories[compiler_name])
    return_code = subprocess.call("cmake --graphviz=graph_project/graph_cmake " + build_directories[compiler_name], shell=True)
    os.chdir(project_directory)
    return return_code

def help():
    print("python3 build.py lint <compiler>             (check code style)")
    print("python3 build.py build <compiler>            (build project)")
    print("python3 build.py run <compiler>              (run main)")
    print("python3 build.py test <compiler>             (run gtests)")
    print("python3 build.py benchmark <compiler>        (run benchmark)")
    print("python3 build.py graph <compiler>            (generate graph project)")
    print("python3 build.py all <compiler>              (check code style, build, run main and tests)")
    print("python3 build.py asymp <compiler> <args>     (make asymptotics figures)")
    print("compilers: g++ (default), clang (Linux, macOS), msvc (Windows)")
    print("Compler choice temporary works only on linux-like OS")
    print("Use python instead of python3 on Windows")
    exit(0)

if __name__ == "__main__":
    try:
        create_folders()
    except Exception:
        print("Folders can't be created")
        exit(1)
    global compiler_name
    compiler_name = sys.argv[2] if len(sys.argv) > 2 else "g++"
    if len(sys.argv) < 2:
        help()
    elif (sys.argv[1] == "all"):
        result = {'lint' : -1,
                'build' : -1,
                'tests' : -1,
                'benchmark' : -1,
                'main' : -1}
        result['lint'] = lint()
        result['build'] = build()
        if result['build'] == 0:
            result['benchmark'] = benchmark()
            result['tests'] = run_tests()
            result['main'] = run_main()
        return_code = 0
        for stage in result:
            if result[stage] != 0:
                return_code = 1
            print("Stage " + stage + " returned exit code " + str(result[stage]))
    elif (sys.argv[1] == "lint"):
        return_code = lint()
    elif (sys.argv[1] == "build"):
        return_code = build()
    elif (sys.argv[1] == "run"):
        if len(sys.argv) > 3:
            return_code = run_main(sys.argv[3])
        else:
            return_code = run_main()
    elif (sys.argv[1] == "benchmark"):
        return_code = benchmark()
    elif (sys.argv[1] == "test"):
        return_code = run_tests()
    elif (sys.argv[1] == "asymp"):
        additional_args = []
        for i in range(3, len(sys.argv)):
            additional_args.append(sys.argv[i])
        return_code = asymp(additional_args)
    elif (sys.argv[1] == "graph"):
        return_code = cmake_graph()
    else:
        help()
    print("Stage " + sys.argv[1] + " returned exit code " + str(return_code))
    exit(return_code)