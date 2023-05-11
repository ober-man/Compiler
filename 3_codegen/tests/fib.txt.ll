; ModuleID = 'main'
source_filename = "main"

declare void @__pcl_print(i32)

declare i32 @__pcl_scan()

define i32 @fib(i32 %0) {
func_start:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = alloca i32
  %3 = load i32, i32* %1
  %4 = icmp sle i32 %3, 1
  br i1 %4, label %5, label %6

5:                                                ; preds = %func_start
  store i32 1, i32* %2
  br label %14

6:                                                ; preds = %func_start
  %7 = load i32, i32* %1
  %8 = sub i32 %7, 2
  %9 = call i32 @fib(i32 %8)
  %10 = load i32, i32* %1
  %11 = sub i32 %10, 1
  %12 = call i32 @fib(i32 %11)
  %13 = add i32 %12, %9
  store i32 %13, i32* %2
  br label %14

14:                                               ; preds = %6, %5
  %15 = load i32, i32* %2
  ret i32 %15
}

define i32 @main() {
func_start:
  %0 = alloca i32
  store i32 0, i32* %0
  %1 = alloca i32
  store i32 0, i32* %1
  %2 = call i32 @__pcl_scan()
  store i32 %2, i32* %1
  %3 = load i32, i32* %1
  %4 = load i32, i32* %0
  %5 = icmp sle i32 %4, %3
  br i1 %5, label %while_body, label %while_end

while_body:                                       ; preds = %while_body, %func_start
  %6 = load i32, i32* %0
  %7 = call i32 @fib(i32 %6)
  call void @__pcl_print(i32 %7)
  %8 = load i32, i32* %0
  %9 = add i32 %8, 1
  store i32 %9, i32* %0
  %10 = load i32, i32* %1
  %11 = load i32, i32* %0
  %12 = icmp sle i32 %11, %10
  br i1 %12, label %while_body, label %while_end

while_end:                                        ; preds = %while_body, %func_start
  ret i32 0
}
