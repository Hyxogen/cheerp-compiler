; ModuleID = 'libasan.bc'
source_filename = "llvm-link"
target datalayout = "b-e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i24:8:8-i32:32:32-i64:64:64-f32:32:32-f64:64:64-a:0:32-f16:16:16-f32:32:32-f64:64:64-n8:16:32-S64"
target triple = "cheerp-leaningtech-webbrowser-wasm"

%struct._Z8_IO_FILE = type asmjs { i8 }

@__asan_option_detect_stack_use_after_return = global i32 0, section "asmjs", align 4
@_ZN6__asan11asan_initedE = global i32 0, section "asmjs", align 4
@.str = private unnamed_addr constant [68 x i8] c"max_shadow_address <= kLowShadowEnd && \22shadow region is too small\22\00", section "asmjs", align 1
@.str.1 = private unnamed_addr constant [29 x i8] c"asan_new/asan_cheerpwasm.cpp\00", section "asmjs", align 1
@__func__._ZN6__asan22InitializeShadowMemoryEv = private unnamed_addr constant [23 x i8] c"InitializeShadowMemory\00", section "asmjs", align 1
@stderr = external constant %struct._Z8_IO_FILE*, align 4
@.str.5 = private unnamed_addr constant [36 x i8] c"error at %p, is_write: %d, size: %u\00", section "asmjs", align 1

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load1(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 1, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_load1(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 1, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load1_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 1, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load2(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 2, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_load2(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 2, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load2_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 2, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load4(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 4, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_load4(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 4, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load4_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 4, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load8(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 8, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_load8(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 8, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load8_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 8, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load16(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 16, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_load16(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 16, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_load16_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext false, i32 noundef 16, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store1(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 1, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_store1(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 1, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store1_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 1, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store2(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 2, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_store2(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 2, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store2_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 2, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store4(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 4, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_store4(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 4, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store4_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 4, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store8(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 8, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_store8(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 8, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store8_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 8, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store16(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 16, i32 noundef 0, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_exp_store16(i32 noundef %addr, i32 noundef %exp) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 16, i32 noundef %exp, i1 noundef zeroext true)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @__asan_report_store16_noabort(i32 noundef %addr) #0 section "asmjs" {
entry:
  call void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %addr, i1 noundef zeroext true, i32 noundef 16, i32 noundef 0, i1 noundef zeroext false)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @_Z11__asan_initv() #0 section "asmjs" {
entry:
  call void @_ZN6__asanL16AsanInitInternalEv()
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define internal void @_ZN6__asanL16AsanInitInternalEv() #0 section "asmjs" {
entry:
  %0 = load i32, i32* @_ZN6__asan11asan_initedE, align 4
  %tobool = icmp ne i32 %0, 0
  %lnot = xor i1 %tobool, true
  %lnot1 = xor i1 %lnot, true
  br i1 %lnot1, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  br label %return

if.end:                                           ; preds = %entry
  store i32 0, i32* @__asan_option_detect_stack_use_after_return, align 4
  call void @_ZN6__asan22InitializeShadowMemoryEv()
  store i32 1, i32* @_ZN6__asan11asan_initedE, align 4
  br label %return

return:                                           ; preds = %if.end, %if.then
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @_Z29__asan_version_mismatch_checkv() #0 section "asmjs" {
entry:
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @_ZN6__asan22InitializeShadowMemoryEv() #0 section "asmjs" {
entry:
  call void @llvm.memset.p0i8.i32(i8* elementtype(i8) align 1 null, i8 -1, i32 67108863, i1 false)
  %0 = call i32 @llvm.cheerp.grow.memory(i32 0)
  %conv = sext i32 %0 to i64
  %mul = mul i64 %conv, 65536
  %sub = sub i64 %mul, 1
  %conv1 = trunc i64 %sub to i32
  %shr = lshr i32 %conv1, 3
  %cmp = icmp ule i32 %shr, 536870911
  br i1 %cmp, label %lor.end, label %lor.rhs

lor.rhs:                                          ; preds = %entry
  call void @__assert_fail(i8* noundef getelementptr inbounds ([68 x i8], [68 x i8]* @.str, i32 0, i32 0), i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.1, i32 0, i32 0), i32 noundef 28, i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @__func__._ZN6__asan22InitializeShadowMemoryEv, i32 0, i32 0)) #5
  unreachable

1:                                                ; No predecessors!
  br label %lor.end

lor.end:                                          ; preds = %1, %entry
  %2 = phi i1 [ true, %entry ], [ false, %1 ]
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0i8.i32(i8* nocapture writeonly, i8, i32, i1 immarg) #1

; Function Attrs: nounwind
declare i32 @llvm.cheerp.grow.memory(i32) #2

; Function Attrs: noreturn
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #3

; Function Attrs: mustprogress noinline nounwind optnone
define void @_ZN6__asan18ReportGenericErrorEmmmmbmjb(i32 noundef %pc, i32 noundef %bp, i32 noundef %sp, i32 noundef %addr, i1 noundef zeroext %is_write, i32 noundef %access_size, i32 noundef %exp, i1 noundef zeroext %fatal) #0 section "asmjs" {
entry:
  %frombool = zext i1 %is_write to i8
  %frombool1 = zext i1 %fatal to i8
  %0 = load %struct._Z8_IO_FILE*, %struct._Z8_IO_FILE** @stderr, align 4
  %1 = inttoptr i32 %addr to i8*
  %tobool = trunc i8 %frombool to i1
  %conv = zext i1 %tobool to i32
  %call = call i32 (%struct._Z8_IO_FILE*, i8*, ...) @fprintf(%struct._Z8_IO_FILE* noundef %0, i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i32 0, i32 0), i8* noundef %1, i32 noundef %conv, i32 noundef %access_size)
  %tobool2 = trunc i8 %frombool1 to i1
  br i1 %tobool2, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  call void @abort() #5
  unreachable

if.end:                                           ; preds = %entry
  ret void
}

declare i32 @fprintf(%struct._Z8_IO_FILE* noundef, i8* noundef, ...) #4

; Function Attrs: noreturn
declare void @abort() #3

; Function Attrs: mustprogress noinline nounwind optnone
define void @_ZN6__asan23__asan_register_globalsEPvm(i8* noundef %globals, i32 noundef %n) #0 section "asmjs" {
entry:
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone
define void @_ZN6__asan25__asan_unregister_globalsEPvm(i8* noundef %globals, i32 noundef %n) #0 section "asmjs" {
entry:
  ret void
}

attributes #0 = { mustprogress noinline nounwind optnone "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #2 = { nounwind }
attributes #3 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #4 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #5 = { noreturn }

!llvm.ident = !{!0, !0, !0, !0}
!llvm.module.flags = !{!1}

!0 = !{!"clang version 16.0.0 (git@github.com:Hyxogen/cheerp-compiler.git a1eb25ae00c4657908d36e4f08c05e6d74c2e7ea)"}
!1 = !{i32 7, !"frame-pointer", i32 2}
