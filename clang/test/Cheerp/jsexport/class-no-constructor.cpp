// RUN: not %clang_cc1 -triple cheerp-leaningtech-webbrowser-wasm %s 2>&1 | FileCheck %s --check-prefix=CHECK
// RUN: not %clang_cc1 -triple cheerp-leaningtech-webbrowser-genericjs %s 2>&1 | FileCheck %s --check-prefix=CHECK
// CHECK: error: Cheerp: A {{\[\[}}cheerp::jsexport{{\]\]}}-ed class/struct needs at least a public non-static member


class [[cheerp::jsexport]] A
{
	int y;
public:
};

int main()
{
	A a;
}
