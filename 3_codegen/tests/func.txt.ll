; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @sqr(i32 %0) {
func_start:
  store i32 %0, i32 (i32)* @sqr
  %1 = alloca i32
  %2 = load i32, i32* %1
  %3 = load i32, i32* %1
  %4 = mul i32 %3, %2
  ret i32 %4
}

define i32 @main() {
func_start:
  %0 = alloca i32
  store i32 0, i32* %0
  %1 = load i32, i32* %0
  %2 = icmp sle i32 %1, 10
  br i1 %2, label %while_body, label %while_end

while_body:                                       ; preds = %while_body, %func_start
  %3 = load i32, i32* %0
  %4 = call i32 @sqr(i32 %3)
  call void @__pcl_print(i32 %4)
  %5 = load i32, i32* %0
  %6 = add i32 %5, 1
  store i32 %6, i32* %0
  %7 = load i32, i32* %0
  %8 = icmp sle i32 %7, 10
  br i1 %8, label %while_body, label %while_end

while_end:                                        ; preds = %while_body, %func_start
  ret i32 0
}
