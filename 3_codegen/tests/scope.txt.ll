; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @main() {
func_start:
  %0 = alloca i32
  store i32 4, i32* %0
  %1 = alloca i32
  store i32 5, i32* %1
  %2 = alloca i32
  store i32 6, i32* %2
  %3 = load i32, i32* %0
  call void @__pcl_print(i32 %3)
  %4 = load i32, i32* %1
  call void @__pcl_print(i32 %4)
  ret i32 0
}
