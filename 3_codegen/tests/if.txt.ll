; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @main() {
func_start:
  %0 = alloca i32
  %1 = call i32 @__pcl_scan()
  store i32 %1, i32* %0
  %2 = load i32, i32* %0
  %3 = srem i32 %2, 2
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %then_branch, label %else_branch

then_branch:                                      ; preds = %func_start
  call void @__pcl_print(i32 0)
  br label %if_end

else_branch:                                      ; preds = %func_start
  call void @__pcl_print(i32 1)
  br label %if_end

if_end:                                           ; preds = %else_branch, %then_branch
  ret i32 0
}
