from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir
import os

class VKAPIConan(ConanFile):
    name = "vkapi"
    version = "0.0.8"
    url = "https://github.com/qucals/VK-API"
    description = "C++ library for working with VK API"
    license = "Apache 2.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True
    }
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("nlohmann_json/3.11.2")
        self.requires("libcurl/8.16.0")

    def source(self):
        get(self, "https://github.com/jetfire-oldsmobile27/VK-API/archive/refs/heads/v0.0.9.zip", strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"
        tc.variables["BUILD_EXAMPLES"] = "OFF"
        tc.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        build_dir = self.build_folder
        lib_name = "libVKAPI.a"
        possible_lib_paths = [
            os.path.join(build_dir, "lib", lib_name),
            os.path.join(build_dir, lib_name),
        ]
        lib_found = False
        for src_lib in possible_lib_paths:
            if os.path.exists(src_lib):
                dst_lib = os.path.join(self.package_folder, "lib", lib_name)
                os.makedirs(os.path.dirname(dst_lib), exist_ok=True)
                copy(self, lib_name, src=os.path.dirname(src_lib), dst=os.path.dirname(dst_lib))
                lib_found = True
                break
        if not lib_found:
            raise Exception("Can't find builded liv VKAPI")

        src_include = os.path.join(self.package_folder, "bin", "include", "vkapi")
        dst_include = os.path.join(self.package_folder, "include", "vkapi")
        if os.path.isdir(src_include):
            copy(self, "*", src=src_include, dst=dst_include)
            rmdir(self, os.path.join(self.package_folder, "bin"))

    def package_info(self):
        self.cpp_info.libs = ["VKAPI"]
        self.cpp_info.includedirs = ["include/vkapi"]
        self.cpp_info.set_property("cmake_file_name", "VKAPI")
        self.cpp_info.set_property("cmake_target_name", "VKAPI::VKAPI")
        self.cpp_info.resdirs = []
