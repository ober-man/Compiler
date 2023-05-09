; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @main() {
func_start:
  call void @__pcl_print(i32 5)
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = load i32, i32* %0
  call void @__pcl_print(i32 %1)
  %2 = alloca i32
  %3 = call i32 @__pcl_scan()
  store i32 %3, i32* %2
  %4 = load i32, i32* %2
  call void @__pcl_print(i32 %4)
  %5 = load i32, i32* %2
  %6 = load i32, i32* %0
  %7 = add i32 %6, %5
  call void @__pcl_print(i32 %7)
  ret i32 0
}
