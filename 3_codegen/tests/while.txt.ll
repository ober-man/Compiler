; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @main() {
func_start:
  %0 = alloca i32
  store i32 0, i32* %0
  %1 = load i32, i32* %0
  %2 = icmp slt i32 %1, 5
  br i1 %2, label %while_body, label %while_end

while_body:                                       ; preds = %while_body, %func_start
  %3 = load i32, i32* %0
  %4 = add i32 %3, 1
  store i32 %4, i32* %0
  %5 = load i32, i32* %0
  call void @__pcl_print(i32 %5)
  %6 = load i32, i32* %0
  %7 = icmp slt i32 %6, 5
  br i1 %7, label %while_body, label %while_end

while_end:                                        ; preds = %while_body, %func_start
  ret i32 0
}
