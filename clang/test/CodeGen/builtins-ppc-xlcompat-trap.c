// RUN: %clang_cc1 -O2 -triple powerpc64-unknown-unknown \
// RUN:   -emit-llvm %s -o - -target-cpu pwr9 | \
// RUN:  FileCheck %s --check-prefixes=CHECK64,CHECK
// RUN: %clang_cc1 -O2 -triple powerpc64le-unknown-unknown \
// RUN:   -emit-llvm %s -o - -target-cpu pwr9 | \
// RUN:  FileCheck %s --check-prefixes=CHECK64,CHECK
// RUN: %clang_cc1 -O2 -triple powerpc-unknown-aix \
// RUN:   -emit-llvm %s -o - -target-cpu pwr9 | \
// RUN:  FileCheck %s -check-prefixes=CHECK
// RUN: %clang_cc1 -O2 -triple powerpc64-unknown-aix \
// RUN:   -emit-llvm %s -o - -target-cpu pwr9 | \
// RUN:  FileCheck %s --check-prefixes=CHECK64,CHECK

long long lla, llb;
double da;
int ia, ib;

#ifdef __ppc64__
// tdw
void test_xl_tdw(void) {
// CHECK64: void @llvm.ppc.tdw(i64 %0, i64 %1, i32 1)

  __tdw(lla, llb, 1);
}

void test_tdw(void) {
// CHECK64: void @llvm.ppc.tdw(i64 %0, i64 %1, i32 13)

  __builtin_ppc_tdw(lla, llb, 13);
}
#endif

// td
void test_tw(void) {
// CHECK: void @llvm.ppc.tw(i32 %0, i32 %1, i32 1)

  __builtin_ppc_tw(ia, ib, 1);
}

void test_xl_tw(void) {
// CHECK: void @llvm.ppc.tw(i32 %0, i32 %1, i32 1)

  __tw(ia, ib, 1);
}

// trap
void test_trap(void) {
// CHECK: void @llvm.ppc.trap(i32 %0)
  __builtin_ppc_trap(ia);
}

void test_xl_trap(void) {
// CHECK: void @llvm.ppc.trap(i32 %0)
  __trap(ia);
}

#ifdef __PPC64__
// trapd
void test_trapd(void) {
// CHECK64: void @llvm.ppc.trapd(i64 %conv)
  __builtin_ppc_trapd(da);
}

void test_xl_trapd(void) {
// CHECK64: void @llvm.ppc.trapd(i64 %conv)
  __trapd(da);
}
#endif
