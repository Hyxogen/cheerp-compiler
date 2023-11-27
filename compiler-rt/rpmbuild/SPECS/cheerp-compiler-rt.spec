Name: cheerp-compiler-rt
Version: 3.0
Release:        1%{?dist}
Summary: A C++ compiler for the Web, C++ library implementation

License:  License: Apache-2.0 WITH LLVM-exception OR NCSA
URL: https://leaningtech.com/cheerp
Source0: %{NAME}_%{VERSION}.orig.tar.gz

BuildRequires: cmake make ninja-build cheerp-llvm-clang = %{VERSION} cheerp-utils = %{VERSION} cheerp-musl = %{VERSION} python3
Requires: cheerp-llvm-clang = %{VERSION} cheerp-utils = %{VERSION} cheerp-musl = %{VERSION}

%description
Cheerp is a tool to bring C++ programming to the Web. It can generate a seamless
combination of JavaScript, WebAssembly and Asm.js from a single C++ codebase.

%define debug_package %{nil}

%prep
%autosetup
%setup -T -D

cmake -S compiler-rt -B build_compiler_rt_wasm -C compiler-rt/CheerpCmakeConf.cmake \
	-DCMAKE_BUILD_TYPE=Release -DLLVM_DIR="$PWD/build/lib/cmake/llvm" \
	-DCMAKE_TOOLCHAIN_FILE="/opt/cheerp/share/cmake/Modules/CheerpWasmToolchain.cmake"

%build
make -C build_compiler_rt_wasm

%install
DESTDIR=%{buildroot} INSTALL="/usr/bin/install -p" make -C build_compiler_rt_wasm install

%clean
rm -rf $RPM_BUILD_ROOT

%files
/opt/cheerp/

%changelog
* Fri Mar 03 2023 Yuri Iozzelli <yuri@leaningtech.com>
- Update license
* Tue Dec 10 2019 Yuri Iozzelli <yuri@leaningtech.com>
- First RPM version
